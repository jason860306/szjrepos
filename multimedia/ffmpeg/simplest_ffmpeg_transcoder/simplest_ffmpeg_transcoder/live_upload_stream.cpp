#include "stdafx.h"
#include "liveupstrm.h"
#include "libasynccore/classes.h"
#include "libasynccore/async_core.h"
#include "libasynccore/timer.h"
#include "live_upload_stream.h"
#include "avfile_decoder.h"

namespace lme = live_media_encoder;

live_upload_stream::object_creator live_upload_stream::_create_obj;

live_upload_stream::live_upload_stream()
	: _upload_host()
	, _upload_port(0)
	, _channel_id()
	, _media_file()
	, _avfile_decoder()
	, _sem()
	, _timer_id(-1)
	, _is_stoped(true)
{
}

live_upload_stream::~live_upload_stream()
{
	stop();
	_avfile_decoder.reset();
	_sem.reset();
}

live_upload_stream::live_upload_stream(const live_upload_stream& upstrm)
	: _upload_host(upstrm._upload_host)
	, _upload_port(upstrm._upload_port)
	, _channel_id(upstrm._channel_id)
	, _media_file(upstrm._media_file)
	, _avfile_decoder(upstrm._avfile_decoder)
	, _timer_id(upstrm._timer_id)
	, _is_stoped(upstrm._is_stoped)
{

}

live_upload_stream& live_upload_stream::operator=(const live_upload_stream& trans)
{
	return *this;
}

live_upload_stream *live_upload_stream::instance()
{
	static std::tr1::shared_ptr<live_upload_stream> obj(new live_upload_stream());
	//do_nothing 是必要的，do_nothing的作用有点意思，
	//如果不加_create_obj.do_nothing();这句话，在main函数前面
	//create_object_的构造函数都不会被调用，instance当然也不会被调用，
	//我的估计是模版的延迟实现的特效导致，如果没有这句话，编译器也不会实现
	// live_upload_stream::object_creator,所以就会导致这个问题
	_create_obj.do_nothing();
	return obj.get();
}

int32_t live_upload_stream::init(const std::string &channel_id,
	const std::string &upload_host, uint16_t upload_port,
	const std::string &media_file)
{
	_channel_id.assign(channel_id);
	_upload_host.assign(upload_host);
	_upload_port = upload_port;
	_media_file.assign(media_file);
	return init_inner();
}

int32_t live_upload_stream::init_inner()
{
	_is_stoped = false;

	_sem.reset(new lme::semaphore());
	if (!_sem)
	{
		return -1;
	}
	_avfile_decoder.reset(new avfile_decoder(_channel_id));
	if (!_avfile_decoder)
	{
		return -1;
	}
	if (0 != _avfile_decoder->init(_media_file))
	{
		return -1;
	}
	LUS init(_channel_id.c_str(), _upload_host.c_str(), _upload_host.size(),
		_upload_port, &live_upload_stream::status_cb, shared_from_this().get());

	return 0;
}

int32_t live_upload_stream::wait()
{
	if (!_sem)
	{
		return -1;
	}
	_sem->wait();
	return 0;
}

int32_t live_upload_stream::increase()
{
	if (!_sem)
	{
		return -1;
	}
	_sem->increase();
	return 0;
}

/**
 * @brief 状态机运转
 */
int32_t live_upload_stream::status_cb(LUS STATUS_TYPE status,
	const char *errmsg, void *arg)
{
	int32_t ret = 0;
	live_upload_stream *upstrm = static_cast<live_upload_stream *>(arg);
	if (NULL == upstrm)
	{
		return -1;
	}
	switch (status)
	{
	case LUS ST_LUS_ESTABLISHED: ///< 申请上传地址成功，可以打开通道了
		ret = upstrm->on_lus_established();
		break;
	case LUS ST_LUS_STRMCH_OPENED: ///< 通道打开成功，可以开始上传数据了
		ret = upstrm->on_lus_open();
		break;
	case LUS ST_LUS_CLOSE: ///< 关闭成功，程序可以退出了
		ret = upstrm->on_lus_close();
		break;
	case LUS ST_ERR_UPLOADMGR_DISCONN:
	case LUS ST_ERR_UPLOADSRV_DISCONN:
		upstrm->uninit();
		ret = upstrm->init_inner();
		break;
	case LUS ST_ERR_OPEN_STRMCH:
	case LUS ST_ERR_TRANSDATA:
	case LUS ST_ERR_CLOSE_STRMCH: ///< 异常情况，程序退出
		break;
	default: ///< 其它情况，关闭通道再行退出程序
		//ret = upstrm->close();
		break;
	}
	return ret;
}

int32_t live_upload_stream::on_lus_established()
{
	if (!_avfile_decoder)
	{
		return -1;
	}
	const avfile_decoder::av_metadata_vec_t &av_mdata_vec(
		_avfile_decoder->metadata_vec());
	if (av_mdata_vec.empty())
	{
		return -1;
	}
	for (size_t i = 0; i < av_mdata_vec.size(); ++i)
	{
		if (NULL != av_mdata_vec[i]._audio_metadata)
		{
			LUS open_audio(*av_mdata_vec[i]._audio_metadata);
		}
		if (NULL != av_mdata_vec[i]._video_metadata)
		{
			LUS open_video(*av_mdata_vec[i]._video_metadata);
		}
	}
	return 0;
}

int32_t live_upload_stream::on_lus_open()
{
	if (-1 == _timer_id)
	{
		_timer_id = lme::timer_manager::instance().add_timer(
			TIMER_INTERVAL, true, std::tr1::bind(
			&live_upload_stream::trans_updata, shared_from_this()));

		start();
	}
	return 0;
}

int32_t live_upload_stream::on_lus_close()
{
	stop();
	return 0;
}

int32_t live_upload_stream::close()
{
	// 	LUS close_audio();
	// 	LUS close_video();
	LUS close();
	lme::timer_manager::instance().delete_timer(_timer_id);
	lme::timer_manager::instance().delete_all_timers();
	return 0;
}

int32_t live_upload_stream::uninit()
{
	LUS uninit();
	return 0;
}

void live_upload_stream::trans_updata()
{
	if (!_avfile_decoder)
	{
		return;
	}
	static int32_t s_pre_dts = 0;
	avfile_decoder::transdata_t updata;
	do
	{
		if (0 != _avfile_decoder->transdata(updata))
		{
			return;
		}
		if (LUS ST_VIDEO == (updata._strmCH_id & STREAM_MASK))
		{
			LUS write(static_cast<LUS FRAME_TYPE>(updata._frame_type),
				updata._dts, updata._pts, const_cast<char *>(updata._data.c_str()),
				updata._data.size());
		}
		else if (LUS ST_AUDIO == (updata._strmCH_id & STREAM_MASK))
		{
			LUS write(updata._dts, updata._data.c_str(), updata._data.size());
		}
	} while (updata._dts - s_pre_dts <= TRANS_DTS_INTERVAL);
	s_pre_dts = updata._dts;
}

void live_upload_stream::start()
{
	lme::async_core::instance().start();
}

void live_upload_stream::stop()
{
	uninit();

	if (!_is_stoped)
	{
		/* then call WSACleanup when done using the Winsock dll */
		WSACleanup();
		lme::timer_manager::instance().delete_timer(_timer_id);
		lme::timer_manager::instance().delete_all_timers();
		lme::async_core::instance().stop();
		lme::async_core::instance().destroy_instance();

		if (_sem)
		{
			_sem->increase();
		}

		_is_stoped = true;
	}
}
