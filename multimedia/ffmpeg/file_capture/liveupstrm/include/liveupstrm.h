/**
 * ============================================================================
 * @file	liveupstrm.h
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date	May 19, 2015 3:42:36 PM
 *
 * @author  ��������Ƶ
 * ============================================================================
 */

#ifndef __BFP2P_CLIENT_LIVEUPSTRM_INCLUDE_LIVEUPSTRM_H__
#define __BFP2P_CLIENT_LIVEUPSTRM_INCLUDE_LIVEUPSTRM_H__
#include <stdint.h>

#ifdef LUS_USING
	#define LUS_BEGIN	namespace lus {
	#define LUS_END	}
	#define LUS	::lus::
#else /* _STD_USING */
	#define LUS_BEGIN
	#define LUS_END
	#define LUS	::
#endif /* _STD_USING */

#ifdef WIN32
	#ifdef LIVEUPSTRM_SHARED
		#ifdef LIVEUPSTRM_EXPORTS
			#define LIVEUPSTRM_EXTERN __declspec(dllexport)
		#else
			#define LIVEUPSTRM_EXTERN __declspec(dllimport)
		#endif
	#elif defined(LIVEUPSTRM_STATIC)
		#define LIVEUPSTRM_EXTERN
	#endif
#elif defined(__GNUC__)
	#define LIVEUPSTRM_EXTERN
#endif

#ifndef LIVEUPSTRM_EXTERN
	#define LIVEUPSTRM_EXTERN
#endif

// �������Լ��
#ifdef WIN32
	#if defined(LIVEUPSTRM_SHARED)
		#define LIVEUPSTRM_API __stdcall
	#else
		#define LIVEUPSTRM_API
	#endif
#else
	#define LIVEUPSTRM_API
#endif

LUS_BEGIN

#define CHANNEL_ID_LEN 32

enum STATUS_TYPE
{
	ST_DEFAULT				= -1,		///< Ĭ��״̬��û�о�������

	/**
	 * @brief ״̬��
	 */
	ST_LUS_ESTABLISHED		= 00001,	///< �ϴ����������ӳɹ������Դ�ͨ�������ϴ�
	ST_LUS_STRMCH_OPENED	= 00002,	///< ͨ���򿪳ɹ������Կ�ʼ�ϴ�����
	ST_LUS_CLOSE			= 00003,	///< �ر�״̬�������Ҫ�����ϴ���
										///< ����Լ�����ͨ�������ϴ���
										///< ������ͨ��ʱ�����ٳ�ʼ������������˳�

	/**
	 * @brief �������
	 */
	ST_ERR_OUT_OF_MEMORY	= 10001,	///< �����OOM�������ڴ����ѡ���˳��������
	ST_ERR_INVALID_OBJECT	= 10002,	///< ָ����Ч,Ӧ����Ҫ���������ط�����
	ST_ERR_SET_CALLBACK		= 10003,	///< ���ûص�ʧ�ܣ��������ûص������߲��ûص�
	ST_ERR_UPLOADMGR_INIT	= 10004,	///< ��ʼ��uploadmgrʧ�ܣ�uploadmgr��
										///< ��ַ�޷����ӣ��˳���������ѡ���
										///< ��uploadmgr�ĵ�ַ
	ST_ERR_APPLY_ADDR		= 10005,	///< ���������ϴ���ַ����ʧ�ܣ��ط�
	ST_ERR_UPLOADMGR_DISCONN= 10006,	///< δ���뵽uploadsrv�ϴ�uploadmgrȴ�쳣�Ͽ��ˣ���Ҫ����init
	ST_ERR_UPLOADSRV_INIT	= 10007,	///< ʹ�����뵽��uploadsrv��ַ��ʼ��
										///< uploadsrvʧ�ܣ��������뼴����init���˳�
	ST_ERR_UPLOADSRV_DISCONN= 10008,	///< uploadsrv���ӶϿ����������´�ͨ�������ϴ�
	ST_ERR_OPEN_STRMCH		= 10009,	///< ��ͨ��ʧ�ܣ������˳������ͨ���򿪵�ԭ��
	ST_ERR_TRANSDATA		= 10010,	///< �ϴ�����ʧ�ܣ����Լ����ϴ�
	ST_ERR_CLOSE_STRMCH		= 10011,	///< �ر�ͨ��ʧ�ܣ������˳�
	ST_ERR_UPLOAD_DISCONN	= 10012,	///< upload���������ӶϿ����������´�ͨ�������ϴ�

	/**
	 * @brief �������,Ӧ����Ҫ���������ط�����
	 */
	ST_CMD_INVALID_PKT		= 20002,	///< �Ƿ������
	ST_CMD_INVALID_RESULT	= 20003,	///< ���������ؽ������
	ST_CMD_PEAK_BUFFER		= 20004,	///< ��ȡsocket���ݴ���ֻ����ȡ������socket��������ɾ��
	ST_CMD_READ_BUFFER		= 20005,	///< ��socket���ݴ��󣬶����������ݻ��socket��������ɾ��
	ST_CMD_PROC_FAILED		= 20006,	///< �����ʧ��
};

/**
 * @brief ֡����
 */
enum FRAME_TYPE
{
	NON_KEY_FRAME	= 0,	///< �ǹؼ�֡
	KEY_FRAME		= 1,	///< �ؼ�֡
};

/**
 * @brief ��Ƶ�����ʽ
 */
enum AUDIO_CODECID_TYPE
{
	ACT_MPEG_AAC	= 0,	///< ��ƵAAC�����ʽ
	ACT_MP3			= 1,	///< ��ƵMP3�����ʽ
};

/**
 * @brief ��Ƶ�����ʽ
 */
enum VIDEO_CODECID_TYPE
{
	VCT_H264		= 0,	///< ��ƵH264�����ʽ
};

/**
 * @brief ��ƵԪ����
 */
typedef struct __audio_metadata
{
	 AUDIO_CODECID_TYPE _codec_id;	///< ��Ƶ�����ʽ type: char
	 int32_t _sample_rate;			///< ��Ƶ������
	 int32_t _data_rate;			///< ��Ƶ����
	 int16_t _strmCH_cnt;			///< ͨ������
	 char _sample_size;				///< ��Ƶ������С
	 char *_reserve_data;			///< ��չ�ֶΣ�ֻ�е�_codec_idΪAAC��
									///< ������չ���ݣ���Ҫ����ռ䣬
									///< libliveupstrm��ֱ��ӵ�иÿ��ڴ������Ȩ��
									///< ���������ͷ�
	 int16_t _reserve_size;			///< ��չ�ֶγ���
} audio_metadata_t, *audio_metadata_ptr_t;

/**
 * @brief ��ƵԪ����
 */
typedef struct __video_metadata
{
	 VIDEO_CODECID_TYPE _codec_id;	///< ��Ƶ�����ʽ type: char
	 int16_t _width;				///< ��Ƶ���
	 int16_t _height;				///< ��Ƶ�߶�
	 int16_t _frame_rate;			///< ��Ƶ֡��
	 int32_t _data_rate;			///< ��Ƶ����
 	 char *_reserve_data;			///< ��չ�ֶΣ�ֻ�е�_codec_idΪH264��
									///< ������չ���ݣ���Ҫ����ռ䣬
									///< libliveupstrm��ֱ��ӵ�иÿ��ڴ������Ȩ��
									///< ���������ͷ�
 	 int16_t _reserve_size;			///< ��չ�ֶγ���
} video_metadata_t, *video_metadata_ptr_t;

/**
 * @brief ״̬�ص��¼���״̬���ʹ������ʹ�øûص����ϲ㷴��
 */
typedef int32_t (LIVEUPSTRM_API * status_cb_ptr_t)(STATUS_TYPE status,
	const char *errmsg, void *arg);

/**
 * @brief �ӿڶ��壬���ڽӿ�ȫ�����õķ��������ã����û�з���ֵ��
 *		  ���е�״̬��ͨ��״̬�ص��������ⷴ��
 */

/**
 * @brief ��ʼ������ʼ�����ϴ���ַ��ͬһƵ�����ϴ��ڶ���ϴ�ʱ�����Բ������³�ʼ��
 * @param[in] channel_id	Ƶ��id
 * @param[in] upload_host	���ȷ�������ַ������Ϊ����
 * @param[in] upload_port	���ȷ������˿�
 * @param[in] status_cb		״̬�ص�
 * @param[in] arg			����status_cb�Ĳ���
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API init(const char channel_id[CHANNEL_ID_LEN],
 	const char *upload_host, size_t host_size, uint16_t upload_port,
 	status_cb_ptr_t status_cb, void *arg = NULL);
/**
 * @brief ����Ƶͨ������������Ƶϵͳ����û����Ƶ���ݣ����Ҳ���Բ�����Ƶͨ��
 * @param[in] amdata		��ƵԪ����
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API open_audio(const audio_metadata_t &amdata);
/**
 * @brief ����Ƶͨ������������Ƶϵͳ����Ҫ����Ƶͨ�������ϴ���Ƶ����
 * @param[in]				��ƵԪ����
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API open_video(const video_metadata_t &vmdata);
/**
 * @brief �ϴ���Ƶ����
 * @param[in] dts			����ʱ�������λ��ms
 * @param[in] data			��Ƶ���ݣ���Ҫ�����ڴ�ռ䣬libliveupstrm��ֱ��
 *							ӵ�иÿ����ݵ�����Ȩ�����������ͷ�
 * @param[in] size			��Ƶ���ݴ�С
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API write(int32_t dts, const char *data,
	size_t size);
/**
 * @brief �ϴ���Ƶ����
 * @param[in] frame_type	��Ƶ֡��ʽ�����Ƿ�Ϊ�ؼ�֡
 * @param[in] dts			����ʱ�������λ��ms
 * @param[in] pts			����ʱ�������λ��ms
 * @param[in] data			��Ƶ���ݣ���Ҫ�����ڴ�ռ䣬libliveupstrm��ֱ��
 *							ӵ�иÿ����ݵ�����Ȩ�����������ͷ�
 * @param[in] size			��Ƶ���ݴ�С
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API write(FRAME_TYPE frame_type, int32_t dts,
	int32_t pts, const char *data, size_t size);
/**
 * @brief �ر�ͨ�����ͷţ������ᷴ��ʼ���������Լ�������open������Ҫ���³�ʼ��
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API close();
/**
 * @brief ����ʼ�����ͷ��ϴ�ģ��
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API uninit();

LUS_END

#endif /* __BFP2P_CLIENT_LIVEUPSTRM_INCLUDE_LIVEUPSTRM_H__ */
