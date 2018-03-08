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
 * @author  暴风云视频
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

// 定义调用约定
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
	ST_DEFAULT				= -1,		///< 默认状态，没有具体意义

	/**
	 * @brief 状态机
	 */
	ST_LUS_ESTABLISHED		= 00001,	///< 上传服务器连接成功，可以打开通道进行上传
	ST_LUS_STRMCH_OPENED	= 00002,	///< 通道打开成功，可以开始上传数据
	ST_LUS_CLOSE			= 00003,	///< 关闭状态，如果需要继续上传，
										///< 则可以继续打开通道进行上传，
										///< 继续打开通道时不用再初始化，否则程序退出

	/**
	 * @brief 常规错误
	 */
	ST_ERR_OUT_OF_MEMORY	= 10001,	///< 经典的OOM错误，视内存情况选择退出或不予理睬
	ST_ERR_INVALID_OBJECT	= 10002,	///< 指针无效,应用需要处理，可以重发信令
	ST_ERR_SET_CALLBACK		= 10003,	///< 设置回调失败，重新设置回调，或者不用回调
	ST_ERR_UPLOADMGR_INIT	= 10004,	///< 初始化uploadmgr失败，uploadmgr的
										///< 地址无法连接，退出或者重新选择可
										///< 用uploadmgr的地址
	ST_ERR_APPLY_ADDR		= 10005,	///< 发送申请上传地址信令失败，重发
	ST_ERR_UPLOADMGR_DISCONN= 10006,	///< 未申请到uploadsrv上传uploadmgr却异常断开了，需要重新init
	ST_ERR_UPLOADSRV_INIT	= 10007,	///< 使用申请到的uploadsrv地址初始化
										///< uploadsrv失败，重新申请即重新init或退出
	ST_ERR_UPLOADSRV_DISCONN= 10008,	///< uploadsrv连接断开，可以重新打开通道继续上传
	ST_ERR_OPEN_STRMCH		= 10009,	///< 打开通道失败，程序退出，检查通道打开的原因
	ST_ERR_TRANSDATA		= 10010,	///< 上传数据失败，可以继续上传
	ST_ERR_CLOSE_STRMCH		= 10011,	///< 关闭通道失败，程序退出
	ST_ERR_UPLOAD_DISCONN	= 10012,	///< upload服务器连接断开，可以重新打开通道继续上传

	/**
	 * @brief 信令错误,应用需要处理，可以重发信令
	 */
	ST_CMD_INVALID_PKT		= 20002,	///< 非法信令包
	ST_CMD_INVALID_RESULT	= 20003,	///< 服务器返回结果错误
	ST_CMD_PEAK_BUFFER		= 20004,	///< 提取socket数据错误，只是提取但不从socket缓冲区中删除
	ST_CMD_READ_BUFFER		= 20005,	///< 读socket数据错误，读出来的数据会从socket缓冲区中删除
	ST_CMD_PROC_FAILED		= 20006,	///< 信令处理失败
};

/**
 * @brief 帧类型
 */
enum FRAME_TYPE
{
	NON_KEY_FRAME	= 0,	///< 非关键帧
	KEY_FRAME		= 1,	///< 关键帧
};

/**
 * @brief 音频编码格式
 */
enum AUDIO_CODECID_TYPE
{
	ACT_MPEG_AAC	= 0,	///< 音频AAC编码格式
	ACT_MP3			= 1,	///< 音频MP3编码格式
};

/**
 * @brief 视频编码格式
 */
enum VIDEO_CODECID_TYPE
{
	VCT_H264		= 0,	///< 视频H264编码格式
};

/**
 * @brief 音频元数据
 */
typedef struct __audio_metadata
{
	 AUDIO_CODECID_TYPE _codec_id;	///< 音频编码格式 type: char
	 int32_t _sample_rate;			///< 音频采样率
	 int32_t _data_rate;			///< 音频码率
	 int16_t _strmCH_cnt;			///< 通道个数
	 char _sample_size;				///< 音频采样大小
	 char *_reserve_data;			///< 扩展字段，只有当_codec_id为AAC，
									///< 才有扩展数据，需要分配空间，
									///< libliveupstrm将直接拥有该块内存的所有权，
									///< 但不进行释放
	 int16_t _reserve_size;			///< 扩展字段长度
} audio_metadata_t, *audio_metadata_ptr_t;

/**
 * @brief 视频元数据
 */
typedef struct __video_metadata
{
	 VIDEO_CODECID_TYPE _codec_id;	///< 视频编码格式 type: char
	 int16_t _width;				///< 视频宽度
	 int16_t _height;				///< 视频高度
	 int16_t _frame_rate;			///< 视频帧率
	 int32_t _data_rate;			///< 视频码率
 	 char *_reserve_data;			///< 扩展字段，只有当_codec_id为H264，
									///< 才有扩展数据，需要分配空间，
									///< libliveupstrm将直接拥有该块内存的所有权，
									///< 但不进行释放
 	 int16_t _reserve_size;			///< 扩展字段长度
} video_metadata_t, *video_metadata_ptr_t;

/**
 * @brief 状态回调事件，状态机和错误码均使用该回调向上层反馈
 */
typedef int32_t (LIVEUPSTRM_API * status_cb_ptr_t)(STATUS_TYPE status,
	const char *errmsg, void *arg);

/**
 * @brief 接口定义，由于接口全部是用的非阻塞调用，因此没有返回值，
 *		  所有的状态都通过状态回调函数向外反馈
 */

/**
 * @brief 初始化，开始申请上传地址，同一频道的上传在多次上传时，可以不用重新初始化
 * @param[in] channel_id	频道id
 * @param[in] upload_host	调度服务器地址，可以为域名
 * @param[in] upload_port	调度服务器端口
 * @param[in] status_cb		状态回调
 * @param[in] arg			传给status_cb的参数
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API init(const char channel_id[CHANNEL_ID_LEN],
 	const char *upload_host, size_t host_size, uint16_t upload_port,
 	status_cb_ptr_t status_cb, void *arg = NULL);
/**
 * @brief 打开音频通道，暴风云视频系统可以没有音频数据，因此也可以不打开音频通道
 * @param[in] amdata		音频元数据
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API open_audio(const audio_metadata_t &amdata);
/**
 * @brief 打开视频通道，暴风云视频系统必须要有视频通道，并上传视频数据
 * @param[in]				视频元数据
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API open_video(const video_metadata_t &vmdata);
/**
 * @brief 上传音频数据
 * @param[in] dts			解码时间戳，单位：ms
 * @param[in] data			音频数据，需要分配内存空间，libliveupstrm将直接
 *							拥有该块数据的所有权，但不进行释放
 * @param[in] size			音频数据大小
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API write(int32_t dts, const char *data,
	size_t size);
/**
 * @brief 上传视频数据
 * @param[in] frame_type	视频帧格式，即是否为关键帧
 * @param[in] dts			解码时间戳，单位：ms
 * @param[in] pts			播放时间戳，单位：ms
 * @param[in] data			视频数据，需要分配内存空间，libliveupstrm将直接
 *							拥有该块数据的所有权，但不进行释放
 * @param[in] size			视频数据大小
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API write(FRAME_TYPE frame_type, int32_t dts,
	int32_t pts, const char *data, size_t size);
/**
 * @brief 关闭通道及释放，但不会反初始化，即可以继续调用open而不需要重新初始化
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API close();
/**
 * @brief 反初始化，释放上传模块
 */
LIVEUPSTRM_EXTERN void LIVEUPSTRM_API uninit();

LUS_END

#endif /* __BFP2P_CLIENT_LIVEUPSTRM_INCLUDE_LIVEUPSTRM_H__ */
