///=============================================================================
/// @file :		file_capture.h
///	@brief :	�ļ��ɼ��ӿ�ͷ�ļ�
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
// �������Լ��
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
// ���嵼����ʽ
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
/// �ļ��ɼ��������
typedef uint32_t file_capture_t;
/// ������Ч��ý����
const int32_t INVALID_FILE_CAPTURE = -1;

//==============================================================================
/// @brief: �ļ��ɼ����ݻص�����
/// @param: file_capture_t capture �ļ��ɼ����
/// @param: const char* data	    �ļ�֡����ָ��
/// @param: uint32_t size		    �ļ�֡���ݳ���
/// @param: uint64_t pts		    �ļ�֡����ʱ��� ��λ(us)
/// @return:�ļ��ɼ��豸���
///=============================================================================
typedef void (FILE_CAPTURE_API *file_capture_cb)(file_capture_t capture, 
	const char* data, uint32_t size, uint64_t pts);

//==============================================================================
/// @brief: �򿪲ɼ��ļ�
/// @param: const char* file_name �ļ�����
/// @param: uint32_t width ָ�������Ƶ���
/// @param: uint32_t height ָ�������Ƶ�߶�
/// @param: uint8_t  framerate ָ�������Ƶ֡��
/// @param: uint32_t sample_rate ��Ƶ�ز���Ƶ��
/// @param: uint16_t channel	 ��Ƶ����������
/// @param:	uint16_t sample_size ��Ƶ�ز�������
/// @return:�ļ��ɼ��豸���
///=============================================================================
FILE_CAPTURE_EXTERN file_capture_t FILE_CAPTURE_API 
	open_capture_file(const char* file_name, 
	uint32_t width, uint32_t height, uint8_t framerate,
	uint32_t sample_rate, uint16_t channels, uint16_t sample_size);

//==============================================================================
/// @brief: �رղɼ��ļ�
/// @param: file_capture_t handle �ļ��ɼ��豸���
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API 
	close_capture_file(file_capture_t handle);

//==============================================================================
/// @brief: ��ʼ�ļ����ݲɼ�
/// @param: file_capture_t handle �ļ��ɼ��豸���
/// @param: file_capture_cb vidio_capture_cb ��Ƶ���ݻص�����
/// @param: file_capture_cb audio_capture_cb ��Ƶ���ݻص�����
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	start_file_capture(file_capture_t handle, 
	file_capture_cb vidio_capture_cb, file_capture_cb audio_capture_cb);

//==============================================================================
/// @brief: ��ͣ�ļ����ݲɼ�
/// @param: file_capture_t handle �ļ��ɼ��豸���
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	pause_file_capture(file_capture_t handle);

//==============================================================================
/// @brief: ֹͣ�ļ����ݲɼ�
/// @param: file_capture_t handle �ļ��ɼ��豸���
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
FILE_CAPTURE_EXTERN int32_t FILE_CAPTURE_API
	stop_file_capture(file_capture_t handle);

//==============================================================================
/// @brief: �����û�����
/// @param: video_capture_t handle ��Ƶ�ɼ��豸���
/// @param: void* user_data �û����� 
///=============================================================================
FILE_CAPTURE_EXTERN void FILE_CAPTURE_API 
	set_file_capture_data(file_capture_t handle, void* user_data);

//==============================================================================
/// @brief: ����û�����
/// @param: video_capture_t handle ��Ƶ�ɼ��豸���
/// @return:�û����� 
///=============================================================================
FILE_CAPTURE_EXTERN void* FILE_CAPTURE_API 
	get_file_capture_data(file_capture_t handle);

#ifdef __cplusplus
};
#endif

#endif //__MATRIX_FILE_CAPTURE_H__
