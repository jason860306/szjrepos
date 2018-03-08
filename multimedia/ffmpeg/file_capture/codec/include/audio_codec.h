///=============================================================================
/// @file :		audio_codec.h
///	@brief :	��Ƶ��������ӿ�ͷ�ļ�
/// @version :	1.0
/// @author :	letion
/// @date :		2014-10-29
///=============================================================================
#ifndef __MATRIX_AUDIO_CODEC_H__
#define __MATRIX_AUDIO_CODEC_H__

#include <cstdint>

//==============================================================================
#ifdef __cplusplus
extern "C"
{
#endif

//==============================================================================
// �������Լ��
#ifdef _WIN32
#if defined(BUILDING_AUDIO_CODEC_SHARED) || defined(USING_AUDIO_CODEC_SHARED)
#define AUDIO_CODEC_API __stdcall
#else
#define AUDIO_CODEC_API
#endif
#else
#define AUDIO_CODEC_API
#endif

//==============================================================================
// ���嵼����ʽ
#ifdef _WIN32
/* Windows - set up dll import/export decorators. */
# if defined(BUILDING_AUDIO_CODEC_SHARED)
/* Building shared library. */
#   define AUDIO_CODEC_EXTERN	__declspec(dllexport) 
# elif defined(USING_AUDIO_CODEC_SHARED)
/* Using shared library. */
#   define AUDIO_CODEC_EXTERN	__declspec(dllimport) 
# else
/* Building static library. */
#   define AUDIO_CODEC_EXTERN /* nothing */
# endif
#else //_WIN32
#   define AUDIO_CODEC_EXTERN /* nothing */
#endif 

//==============================================================================
/// ��Ƶ����������
typedef uint32_t audio_encoder_t;
/// ��Ƶ����������
typedef uint32_t audio_decoder_t;
/// ������Ч��ý����
const int32_t INVALID_AUDIO_CODEC = 0;

//==============================================================================
/// ��Ƶ�����������
typedef enum AUDIO_CODEC_TYPE
{
	AUDIO_CODEC_AAC,			///< AAC�������
	AUDIO_CODEC_MP3,			///< MP3�������,only decoder
}audio_codec_type_t;

//==============================================================================
/// @brief: ������Ƶ������
/// @param: uint32_t codec_type ����
/// @param: uint16_t sample_rate ����Ƶ��
/// @param: uint16_t channel Ƶ������
/// @param: uint16_t sample_size ��������
/// @param: uint16_t bitrate ����
/// @return:��Ƶ���������
///=============================================================================
AUDIO_CODEC_EXTERN audio_encoder_t AUDIO_CODEC_API 
	create_audio_encoder(audio_codec_type_t codec_type, uint16_t sample_rate, 
	uint16_t channel, uint16_t sample_size, uint16_t bitrate);

//==============================================================================
/// @brief: ������Ƶ������
/// @param: audio_encoder_t handle ��Ƶ���������
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
AUDIO_CODEC_EXTERN int32_t AUDIO_CODEC_API 
	destroy_audio_encoder(audio_encoder_t handle);

//==============================================================================
/// @brief: �����չ���ݳ���
/// @param: audio_encoder_t handle ��Ƶ���������
/// @return:��չ���ݳ���
///=============================================================================
AUDIO_CODEC_EXTERN uint32_t AUDIO_CODEC_API 
	audio_encoder_extradata_size(audio_encoder_t handle);

//==============================================================================
/// @brief: �����չ����
/// @param: video_encoder_t handle ��Ƶ���������
/// @param: uint8_t* extradata ��չ����ָ��
/// @param: uint32_t extradata_size ��չ���ݳ���
/// @return:��չ���ݳ���
///=============================================================================
AUDIO_CODEC_EXTERN uint32_t AUDIO_CODEC_API 
	audio_encoder_extradata(audio_encoder_t handle, 
	uint8_t* extradata, uint32_t extradata_size);

//==============================================================================
/// @brief: ��Ƶ����
/// @param: audio_encoder_t handle ��Ƶ���������
/// @param: const uint8_t* in �����������
/// @param: uint32_t in_size ����������ݳ���
/// @param: uint8_t* out ���������ݻ�����
/// @param: uint32_t out_size ���������ݻ���������
/// @return:��������ݳ���
///=============================================================================
AUDIO_CODEC_EXTERN uint32_t AUDIO_CODEC_API 
	audio_encoder_encode(audio_encoder_t handle, 
	const uint8_t* in, uint32_t in_size, uint8_t* out, uint32_t out_size);

//==============================================================================
/// @brief: ������Ƶ������
/// @param: uint32_t codec_type ����
/// @param: uint16_t sample_rate ����Ƶ��
/// @param: uint16_t channel Ƶ������
/// @param: uint16_t sample_size ��������
/// @return:��Ƶ���������
///=============================================================================
AUDIO_CODEC_EXTERN audio_decoder_t AUDIO_CODEC_API 
	create_audio_decoder(audio_codec_type_t codec_type, uint16_t sample_rate, 
	uint16_t channel, uint16_t sample_size);

//==============================================================================
/// @brief: ������Ƶ������
/// @param: audio_encoder_t handle ��Ƶ���������
/// @return:0-�ɹ� other-ʧ��
///=============================================================================
AUDIO_CODEC_EXTERN int32_t AUDIO_CODEC_API 
	destroy_audio_decoder(audio_decoder_t handle);

//==============================================================================
/// @brief: ��Ƶ����
/// @param: audio_decoder_t handle ��Ƶ���������
/// @param: const uint8_t* in �����������
/// @param: uint32_t in_size ����������ݳ���
/// @param: uint8_t* out ���������ݻ�����
/// @param: uint32_t out_size ���������ݻ���������
/// @return:��������ݳ���
///=============================================================================
AUDIO_CODEC_EXTERN uint32_t AUDIO_CODEC_API 
	audio_decoder_decode(audio_decoder_t handle, 
	const uint8_t* in, uint32_t in_size, uint8_t* out, uint32_t out_size);

#ifdef __cplusplus
};
#endif

#endif //__MATRIX_AUDIO_CODEC_H__
