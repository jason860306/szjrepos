#pragma once

#ifdef WIN32
#include <memory>
#else
#include <tr1/memory>
#endif
#include <libasynccore/timer.h>
#include <socket_address.h>

class avfile_decoder;
namespace live_media_encoder
{
	class semaphore;
}

class live_upload_stream
	: public std::tr1::enable_shared_from_this<live_upload_stream>
{
	struct object_creator
	{
		object_creator() { live_upload_stream::instance(); }
		inline void do_nothing() const {}
	};

	static object_creator _create_obj;

	enum { TIMER_INTERVAL = 1 * 1000, TRANS_DTS_INTERVAL = 1100, /* ms */ };

	typedef std::tr1::shared_ptr<avfile_decoder> avfile_encoder_sptr_t;
	typedef std::tr1::shared_ptr<live_media_encoder::semaphore> semaphore_sptr_t;

protected:
	live_upload_stream();

private:  // emphasize the following members are private
	explicit live_upload_stream(const live_upload_stream& trans);
	live_upload_stream& operator=(const live_upload_stream& trans);

public:
	static live_upload_stream *instance();
	virtual ~live_upload_stream();

public:
	int32_t init(const std::string &channel_id, const std::string &upload_host,
		uint16_t upload_port, const std::string &media_file);
	int32_t wait();
	int32_t increase();
	int32_t close();
	int32_t uninit();

	void status(LUS STATUS_TYPE st);
	LUS STATUS_TYPE status() const;

private:
	static int32_t LIVEUPSTRM_API status_cb(LUS STATUS_TYPE status,
		const char *errmsg, void *arg);
	friend int32_t LIVEUPSTRM_API status_cb(LUS STATUS_TYPE status,
		const char *errmsg, void *arg);

private:
	int32_t on_lus_established();
	int32_t on_lus_open();
	int32_t on_lus_close();

private:
	int32_t init_inner();
	void trans_updata();

	void start();
	void stop();

private:
	std::string _upload_host;
	uint16_t _upload_port;
	std::string _channel_id;
	std::string _media_file;
	avfile_encoder_sptr_t _avfile_decoder;
	semaphore_sptr_t _sem;
	TIMER_ID _timer_id;
	bool _is_stoped;
};
