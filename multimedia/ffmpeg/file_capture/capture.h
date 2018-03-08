#pragma once

#include <list>
#include <classes.h>
#include "file_capture.h"

class capture
{
public:
	capture(void);
	virtual ~capture(void);

public:
	// �����ɼ�Դ
	virtual bool create();
	// ���ٲɼ�Դ
	virtual void destroy(void) = 0;
	// ��ʼ�ɼ�
	virtual bool start(void) = 0;
	// ֹͣ�ɼ�
	virtual bool stop(void) = 0;
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_video_capture(void) const = 0;
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_audio_capture(void) const = 0;
};

class video_capture : virtual public capture
{
public:
	video_capture(void);
	virtual ~video_capture(void);

public:
	// �����ɼ�Դ
	virtual bool create();
	// ���ٲɼ�Դ
	virtual void destroy(void);
	// ��ʼ�ɼ�
	virtual bool start(void) = 0;
	// ֹͣ�ɼ�
	virtual bool stop(void) = 0;
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_video_capture(void) const	{ return true;  }
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_audio_capture(void) const	{ return false; }

protected:
	// �ɼ���Ƶ����
	virtual void on_capture_video_data(const uint8_t* data, uint32_t size);

protected:
	AVPicture m_capture_image;
	bool	  m_capture_image_created;
	bool	  m_has_capture_image;
	mutable mutex m_video_lock; 
	SwsContext*		 m_convert_context;		///< ת�����
};

//==============================================================================
class audio_capture : virtual public capture
{
	class audio_data
	{
	public:
		audio_data(const uint8_t* data, uint32_t size, uint64_t pts);
		~audio_data();

	public:
		const uint8_t* data(void) const		{ return m_data; }
		uint32_t size(void) const			{ return m_size; }
		uint64_t pts(void) const			{ return m_pts;  }

	private:
		uint8_t* m_data;
		uint32_t m_size;
		uint64_t m_pts;
	};

public:
	audio_capture(void);
	virtual ~audio_capture(void);

public:
	// �����ɼ�Դ
	virtual bool create();
	// ���ٲɼ�Դ
	virtual void destroy(void);
	// ��ʼ�ɼ�
	virtual bool start(void) = 0;
	// ֹͣ�ɼ�
	virtual bool stop(void) = 0;
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_video_capture(void) const	{ return false;  }
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_audio_capture(void) const	{ return true;   }

protected:
	// �ɼ���Ƶ����
	virtual void on_capture_audio_data(
		const uint8_t* data, uint32_t size, int64_t pts, uint32_t volume);

protected:
	mutable std::<audio_data *> m_audio_data_list;
	mutable mutex m_audio_data_list_lock;
};

//==============================================================================
class file_capture : public video_capture, public audio_capture
{
	friend void FILE_CAPTURE_API file_video_callback(file_capture_t capture, 
		const char* data, uint32_t size, uint64_t pts);
	friend void FILE_CAPTURE_API file_audio_callback(file_capture_t capture, 
		const char* data, uint32_t size, uint64_t pts);

public:
	file_capture(void);
	~file_capture(void);

public:
	// �����ɼ�Դ
	virtual bool create();
	// ���ٲɼ�Դ
	virtual void destroy(void);
	// ��ʼ�ɼ�
	virtual bool start(void);
	// ֹͣ�ɼ�
	virtual bool stop(void);
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_video_capture(void) const	{ return true;  }
	// �Ƿ���Ƶ�ɼ�
	virtual bool is_audio_capture(void) const	{ return true;  }

private:
	file_capture_t m_capture;
};
