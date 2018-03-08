///=============================================================================
/// @file :		file_capture.h
///	@brief :	文件采集接口头文件
/// @version :	1.0
/// @author :	letion
/// @date :		2014-10-29
///=============================================================================
#ifndef __MATRIX_FILE_CAPTURE_H__
#define __MATRIX_FILE_CAPTURE_H__

#include <cstdint>

//==============================================================================
#ifdef __cplusplus
extern "C"
{
#endif

//==============================================================================
// 定义调用约定
#ifdef _WIN32
#if defined(BUILDING_FILE_CAPTURE_SHARED) || defined(USING_FILE_CAPTURE_SHARED)
#define FILE_CAPTURE_API __stdcall
#else
#define FILE_CAPTURE_API
#endif
#else
#define FILE_CAPTURE_API
#endif

//==============================================================================
// 定义导出方式
#ifdef _WIN32
/* Windows - set up dll import/export decorators. */
# if defined(BUILDING_FILE_CAPTURE_SHARED)
/* Building shared library. */
#   define FILE_CAPTURE_EXTERN	__declspec(dllexport) 
# elif defined(USING_FILE_CAPTURE_SHARED)
/* Using shared library. */
#   define FILE_CAPTURE_EXTERN	__declspec(dllimport) 
# else
/* Building static library. */
#   define FILE_CAPTURE_EXTERN /* nothing */
# endif
# elif __GNUC__ >= 4
#	define FILE_CAPTURE_EXTERN __attribute__((visibility("default")))
# else
#	define FILE_CAPTURE_EXTERN /* nothing */
#endif  //_WIN32

//==============================================================================
/// 文件采集句柄定义
typedef uint32_t file_capture_t;
/// 定义无效的媒体句柄
const int32_t INVALID_FILE_CAPTURE = -1;

//==============================================================================
/// @brief: 文件采集数据回调函数
/// @param: file_capture_t capture 文件采集句柄
/// @param: const char* data	    文件帧数据指针
/// @param: uint32_t size		    文件帧数据长度
/// @param: uint64_t pts		    文件帧播放时间戳 单位(us)
/// @return:文件采集设备句柄
///=============================================================================
typedef void (FILE_CAPTURE_API *file_capture_cb)(file_capture_t capture, 
	const char* data, uint32_t size, uint64_t pts);

//==============================================================================
/// @brief: 打开采集文件
/// @param: const char* file_name 文件名称
/// @param: uint32_t width 指定输出视频宽度
/// @param: uint32_t height 指定输出视频高度
/// @param: uint8_t  framerate 指定输出视频帧率
/// @param: uint32_t sample_rate 音频重采样频率
/// @param: uint16_t channel	 音频重声道数量
/// @param:	uint16_t sample_size 音频重采样精度
/// @return:文件采集设备句柄
///=============================================================================
FILE_CAPTURE_EXTERN file_capture_t FILE_CAPTURE_API 
	open_capture_file(const char* file_name, 
	uint32_t width, uint32_t height, uint8_t framerate,
	uint32_t sample_rate, uint16_t channels, uint16_t sample_size);

//==============================================================================
/// @brief: 关闭采集文件
/// @param: file_capture_t handle 文件采集设备句柄
/// @return:0-成功 other-失败
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API 
	close_capture_file(file_capture_t handle);

//==============================================================================
/// @brief: 开始文件数据采集
/// @param: file_capture_t handle 文件采集设备句柄
/// @param: file_capture_cb vidio_capture_cb 视频数据回调函数
/// @param: file_capture_cb audio_capture_cb 音频数据回调函数
/// @return:0-成功 other-失败
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	start_file_capture(file_capture_t handle, 
	file_capture_cb vidio_capture_cb, file_capture_cb audio_capture_cb);

//==============================================================================
/// @brief: 暂停文件数据采集
/// @param: file_capture_t handle 文件采集设备句柄
/// @return:0-成功 other-失败
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	pause_file_capture(file_capture_t handle);

//==============================================================================
/// @brief: 停止文件数据采集
/// @param: file_capture_t handle 文件采集设备句柄
/// @return:0-成功 other-失败
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	stop_file_capture(file_capture_t handle);

//==============================================================================
/// @brief: 设置用户数据
/// @param: video_capture_t handle 视频采集设备句柄
/// @param: void* user_data 用户数据 
///=============================================================================
FILE_CAPTURE_EXTERN void FILE_CAPTURE_API 
	set_file_capture_data(file_capture_t handle, void* user_data);

//==============================================================================
/// @brief: 获得用户数据
/// @param: video_capture_t handle 视频采集设备句柄
/// @return:用户数据 
///=============================================================================
FILE_CAPTURE_EXTERN void* FILE_CAPTURE_API 
	get_file_capture_data(file_capture_t handle);

#ifdef __cplusplus
};
#endif

#endif //__MATRIX_FILE_CAPTURE_H__
