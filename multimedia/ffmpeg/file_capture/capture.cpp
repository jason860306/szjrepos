#include "capture.h"


//==============================================================================
capture::capture(void)
{
}

capture::~capture(void)
{
}

bool capture::create(const capture_info_t& info)
{
	m_capture_info = info;
	return true;
}

//==============================================================================
video_capture::video_capture(void)
	: m_video_lock(QMutex::Recursive)
	, m_has_capture_image(false)
	, m_capture_image_created(false)
	, m_convert_context(NULL)
{
}

video_capture::~video_capture(void)
{
}

bool video_capture::create()
{
	// 分配图片内存
	avpicture_alloc(&m_capture_image, AV_PIX_FMT_YUV420P, 
		info.render.width, info.render.height);

	if(info.render.width != info.video.width 
		|| info.render.height != info.video.height)
	{
		// 创建转换句柄
		m_convert_context = 
			sws_getContext(info.video.width, 
			info.video.height, 
			AV_PIX_FMT_YUV420P, 
			info.render.width, 
			info.render.height, 
			AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);   
	}

	m_capture_image_created = true;
	return true;
}

// 销毁采集源
void video_capture::destroy(void)
{
	QMutexLocker locker(&m_video_lock);
	if(m_capture_image_created)
	{
		avpicture_free(&m_capture_image);
		m_capture_image_created = false;
		m_has_capture_image = false;
	}

	if(NULL != m_convert_context)
	{
		sws_freeContext(m_convert_context);
		m_convert_context= NULL;
	}
}

void video_capture::on_capture_video_data(const uint8_t* data, uint32_t size)
{
	QMutexLocker locker(&m_video_lock);

	AVPicture image;
	if(m_capture_image_created
		&& avpicture_fill(&image, data, AV_PIX_FMT_YUV420P, 
		m_capture_info.video.width, m_capture_info.video.height) > 0)
	{
		if(NULL == m_convert_context)
		{
			av_picture_copy(&m_capture_image, &image, AV_PIX_FMT_YUV420P, 
				m_capture_info.video.width, m_capture_info.video.height);
		}
		else
		{
			sws_scale(m_convert_context, 
				image.data, image.linesize,  0, m_capture_info.video.height, 
				m_capture_image.data, m_capture_image.linesize);
		}
		m_has_capture_image = true;
	}
}

//==============================================================================
audio_data::audio_data(const uint8_t* data, uint32_t size, uint64_t pts)
	: m_data(NULL)
	, m_size(size)
	, m_pts(pts)
{
	m_data = (uint8_t*)malloc(size);
	assert(m_data);
	if(NULL != m_data)
		memcpy(m_data, data, size);
}

audio_data::~audio_data()
{
	if(NULL != m_data)
	{
		free(m_data);
		m_data = NULL;
	}
}

//==============================================================================
audio_capture::audio_capture(void)
	: m_audio_data_list_lock(QMutex::Recursive)
{
}

audio_capture::~audio_capture(void)
{
	try
	{
		destroy();
	}
	catch (...)
	{

	}
}

// 创建采集源
bool audio_capture::create()
{
	return capture::create();
}

// 销毁采集源
void audio_capture::destroy(void)
{
	QMutexLocker locker(&m_audio_data_list_lock);

	QList<audio_data*>::Iterator iter = m_audio_data_list.begin();
	for(; iter != m_audio_data_list.end(); ++iter)
	{
		audio_data* data_ptr = *iter;
		if(NULL != data_ptr)
		{
			delete data_ptr;
			data_ptr = NULL;
		}
	}
	m_audio_data_list.clear();
}

// 采集视频数据
void audio_capture::on_capture_audio_data(
	const uint8_t* data, uint32_t size, int64_t pts, uint32_t volume)
{
	audio_data* data_ptr = new audio_data(data, size, pts);
	if(NULL != data_ptr && NULL != data_ptr->data())
	{
		data_ptr->set_volume(volume);

		QMutexLocker locker(&m_audio_data_list_lock);
		m_audio_data_list.push_back(data_ptr);
	}
}

//==============================================================================
void FILE_CAPTURE_API file_video_callback(file_capture_t handle, 
	const char* data, uint32_t size, uint64_t pts)
{
	int64_t temp = pts;
	file_capture* capture = (file_capture*)get_file_capture_data(handle);
	if(NULL != capture)
	{
		capture->on_capture_video_data((uint8_t*)data, size);
	}
}

void FILE_CAPTURE_API file_audio_callback(file_capture_t handle, 
	const char* data, uint32_t size, uint64_t pts)
{
	file_capture* capture = (file_capture*)get_file_capture_data(handle);
	if(NULL != capture)
	{
		uint32_t volume = setting::get_instance()->get_sound_volume();
		capture->on_capture_audio_data((uint8_t*)data, size, pts, volume);
	}
}

file_capture::file_capture(void)
	: m_capture(INVALID_FILE_CAPTURE)
{
}

file_capture::~file_capture(void)
{
	try
	{
		destroy();
	}
	catch (...)
	{	
	}
}

// 创建采集源
bool file_capture::create(const capture_info_t& info)
{
	if(!video_capture::create(info))
		return false;

	if(!audio_capture::create(info))
		return false;

	bool result = false;
	do 
	{
		QByteArray byte_array = info.device.toUtf8();    
		const char* file_name = byte_array.data();

		m_capture = open_capture_file(file_name, 
			info.video.width, info.video.height, info.video.framerate,
			info.audio.frequency, info.audio.channels, info.audio.samplerate);
		if(INVALID_FILE_CAPTURE == m_capture)
			break;

		set_file_capture_data(m_capture, this);
		result = true;
	} while (false);

	if(!result)
	{
		destroy();
	}
	return result;
}

// 销毁采集源
void file_capture::destroy(void)
{
	video_capture::destroy();

	if(INVALID_FILE_CAPTURE != m_capture)
	{
		stop_file_capture(m_capture);
		close_capture_file(m_capture);
		m_capture = INVALID_FILE_CAPTURE;
	}
}

// 开始采集
bool file_capture::start(void)
{
	bool result = false;
	if(INVALID_FILE_CAPTURE != m_capture)
	{
		int ret = start_file_capture(m_capture, 
			file_video_callback, file_audio_callback);
		result = (0 == ret);
	}
	return result;
}

// 停止采集
bool file_capture::stop(void)
{
	bool result = false;
	if(INVALID_FILE_CAPTURE != m_capture)
	{
		int ret = stop_file_capture(m_capture);
		result = (0 == ret);
	}
	return result;
}
