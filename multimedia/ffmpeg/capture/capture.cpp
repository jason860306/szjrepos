#if 1
// tutorial01.c
//
// This tutorial was written by Stephen Dranger (dranger@gmail.com).
//
// Code based on a tutorial by Martin Bohme (boehme@inb.uni-luebeckREMOVETHIS.de)
// Tested on Gentoo, CVS version 5/01/07 compiled with GCC 4.1.1

// A small sample program that shows how to use libavformat and libavcodec to
// read video from a file.
//
// Use the Makefile to build all examples.
//
// Run using
//
// tutorial01 myvideofile.mpg
//
// to write the first five frames from "myvideofile.mpg" to disk in PPM
// format.

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
}
#endif
#include <stdio.h>

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
	FILE *pFile;
	char szFilename[32];
	int  y;

	// Open file
	sprintf(szFilename, "frame%d.ppm", iFrame);
	pFile=fopen(szFilename, "wb");
	if(pFile==NULL)
		return;

	// Write header
	fprintf(pFile, "P6\n%d %d\n255\n", width, height);

	// Write pixel data
	for(y=0; y<height; y++)
		fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

	// Close file
	fclose(pFile);
}

int main(int argc, char *argv[]) {
	AVFormatContext *pFormatCtx = NULL;
	int             i, videoStream;
	AVCodecContext  *pCodecCtx = NULL;
	AVCodec         *pCodec = NULL;
	AVFrame         *pFrame = NULL; 
	AVFrame         *pFrameRGB = NULL;
	AVPacket        packet;
	int             frameFinished;
	int             numBytes;
	uint8_t         *buffer = NULL;

	AVDictionary    *optionsDict = NULL;
	struct SwsContext      *sws_ctx = NULL;

	if(argc < 2) {
		printf("Please provide a movie file\n");
		return -1;
	}
	// Register all formats and codecs
	av_register_all();

	// Open video file
	if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
		return -1; // Couldn't open file

	// Retrieve stream information
	if(avformat_find_stream_info(pFormatCtx, NULL)<0)
		return -1; // Couldn't find stream information

	// Dump information about file onto standard error
	av_dump_format(pFormatCtx, 0, argv[1], 0);

	// Find the first video stream
	videoStream=-1;
	for(i=0; i<(int)pFormatCtx->nb_streams; i++)
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
			videoStream=i;
			break;
		}
		if(videoStream==-1)
			return -1; // Didn't find a video stream

		// Get a pointer to the codec context for the video stream
		pCodecCtx=pFormatCtx->streams[videoStream]->codec;

		// Find the decoder for the video stream
		pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
		if(pCodec==NULL) {
			fprintf(stderr, "Unsupported codec!\n");
			return -1; // Codec not found
		}
		// Open codec
		if(avcodec_open2(pCodecCtx, pCodec, &optionsDict)<0)
			return -1; // Could not open codec

		// Allocate video frame
		pFrame=av_frame_alloc();

		// Allocate an AVFrame structure
		pFrameRGB=av_frame_alloc();
		if(pFrameRGB==NULL)
			return -1;

		// Determine required buffer size and allocate buffer
		numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
			pCodecCtx->height);
		buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

		sws_ctx =
			sws_getContext
			(
			pCodecCtx->width,
			pCodecCtx->height,
			pCodecCtx->pix_fmt,
			pCodecCtx->width,
			pCodecCtx->height,
			PIX_FMT_RGB24,
			SWS_BILINEAR,
			NULL,
			NULL,
			NULL
			);

		// Assign appropriate parts of buffer to image planes in pFrameRGB
		// Note that pFrameRGB is an AVFrame, but AVFrame is a superset
		// of AVPicture
		avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
			pCodecCtx->width, pCodecCtx->height);

		// Read frames and save first five frames to disk
		i=0;
		while(av_read_frame(pFormatCtx, &packet)>=0) {
			// Is this a packet from the video stream?
			if(packet.stream_index==videoStream) {
				// Decode video frame
				avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, 
					&packet);

				// Did we get a video frame?
				if(frameFinished) {
					// Convert the image from its native format to RGB
					sws_scale
						(
						sws_ctx,
						(uint8_t const * const *)pFrame->data,
						pFrame->linesize,
						0,
						pCodecCtx->height,
						pFrameRGB->data,
						pFrameRGB->linesize
						);

					// Save the frame to disk
					if(++i<=5)
						SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, 
						i);
				}
			}

			// Free the packet that was allocated by av_read_frame
			av_free_packet(&packet);
		}

		// Free the RGB image
		av_free(buffer);
		av_free(pFrameRGB);

		// Free the YUV frame
		av_free(pFrame);

		// Close the codec
		avcodec_close(pCodecCtx);

		// Close the video file
		avformat_close_input(&pFormatCtx);

		return 0;
}

#else
// capture.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdarg.h>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
}
#endif

static void format_string_v(std::string& result, const char *format, va_list arg_list);
static std::string format_string(const char *format, ...);
static std::string get_loctime_str(time_t t = time(NULL));
static void save_frame(AVFrame *pFrame, int width, int height, int iFrmae);

#define LOG(fmt, ...)	    							\
	do                                              	\
	{                                               	\
		fprintf(stdout, "[%s] >> %s[%d]: " fmt "\n",	\
			get_loctime_str().c_str(), __FUNCTION__,	\
			__LINE__, ##__VA_ARGS__);					\
	} while (0)

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		LOG("usage: %s file");
		return 0;
	}
	const char *pFile = argv[1];

	AVDictionary *pDict;
	AVFormatContext *pFmtCtx;

	/**
	* @brief 1. 打开文件
	*/

	av_register_all();

	///< open video file
	if (avformat_open_input(&pFmtCtx, pFile, NULL, &pDict) != 0)
	{
		LOG("cann't open file %s");
		return -1;
	}

	///< retrieve stream information 
	if (avformat_find_stream_info(pFmtCtx, &pDict) < 0)
	{
		LOG("couldn't find stream information");
		return -1;
	}

	///< dump information about file onto standard error
	av_dump_format(pFmtCtx, 0, pFile, 0);

	int videoStrm = -1;
	AVCodecContext *pCodecCtx;

	///< find the first video stream
	for (unsigned int i = 0; i < pFmtCtx->nb_streams; ++i)
	{
		if (AVMEDIA_TYPE_VIDEO == pFmtCtx->streams[i]->codec->codec_type)
		{
			videoStrm = i;
			break;
		}
	}
	if (-1 == videoStrm)
	{
		LOG("didn't find a video stream");
		return -1;
	}

	///< get a pointer to the codec context for the video stream
	pCodecCtx = pFmtCtx->streams[videoStrm]->codec;

	AVCodec *pCodec;

	///< find the decoder for the video stream
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (NULL == pCodec)
	{
		LOG("unsupported codec");
		return -1;
	}

	///< open codec
	if (avcodec_open2(pCodecCtx, pCodec, &pDict) < 0)
	{
		LOG("could not open codec");
		return -1;
	}

	/**
	* @brief 2. 保存数据
	*/

	AVFrame *pFrame, *pFrameRGB;

	///< allocate video frame
	pFrame = av_frame_alloc();
	if (NULL == pFrame)
	{
		LOG("alloc frame failed");
		return -1;
	}

	///< allocate an AVFrame structure
	pFrameRGB = av_frame_alloc();
	if (NULL == pFrameRGB)
	{
		LOG("alloc frame failed");
		return -1;
	}

	uint8_t *buffer;
	int nBytes;

	///< determine required buffer size and allocate buffer
	nBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
		pCodecCtx->height);
	buffer = (uint8_t *)av_malloc(nBytes * sizeof(uint8_t));

	///< assign appropriate parts of buffer to image planes in pFrameRGB
	///< note that pFrameRGB is an AVFrame, but AVFrame is a superset of AVPicture
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
		pCodecCtx->width, pCodecCtx->height);

	/**
	* @brief 3. 读取数据
	*/

	int frameFinished;
	AVPacket packet;

	int i = 0;
	while (av_read_frame(pFmtCtx, &packet) >= 0)
	{
		///< is this a packet from the video stream ?
		if (packet.stream_index == videoStrm)
		{
			///< decode video frame
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

			///< did we get a video frame ?
			if (frameFinished)
			{
				///< convert the image fraom its native format to RGB
				struct SwsContext *pSwsCtx;
				pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
					pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
					PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

				///< 反转图像，否则生成的图像是上下颠倒的
				pFrame->data[0] += pFrame->linesize[0] * (pCodecCtx->height - 1);
				pFrame->linesize[0] *= -1;
				pFrame->data[1] += pFrame->linesize[1] * (pCodecCtx->height / 2 - 1);
				pFrame->linesize[1] *= -1;
				pFrame->data[2] += pFrame->linesize[2] * (pCodecCtx->height / 2 - 1);
				pFrame->linesize[2] *= -1;

				///< 转换图像格式，将解压出来的YUV420P的图像转换为RGB24的图像
				sws_scale(pSwsCtx, pFrame->data, pFrame->linesize, 0,
					pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

				// 				img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24,
				// 					(AVPicture *)pFrame, pCodecCtx->pix_fmt,
				// 					pCodecCtx->width, pCodecCtx->height);

				///< save the frame to disk
				if (++i <= 5)
				{
					save_frame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
				}
			}
		}

		///< free the packet that was allocated by av_read_frame
		av_free_packet(&packet);
	}

	///< free the RGB image
	av_free(buffer);
	av_free(pFrameRGB);

	///< free the YUV frame
	av_free(pFrame);

	///< close the codec
	avcodec_close(pCodecCtx);

	///< close the video file
	avformat_close_input(&pFmtCtx);

	return 0;
}

void save_frame(AVFrame *pFrame, int width, int height, int iFrmae)
{
	FILE *pFile;
	char szFileName[32];

	///< open file
	sprintf(szFileName, "frame%d.ppm", iFrmae);
	pFile = fopen(szFileName, "wb");
	if (pFile == NULL)
	{
		return;
	}

	///< write header
	fprintf(pFile, "P6\n%d %d\n255\n", width, height);

	/// write pixel data
	for (int y = 0; y < height; ++y)
	{
		fwrite(pFrame->data[0] + y * pFrame->linesize[0],
			1, width * 3, pFile);
	}

	///< close file
	fclose(pFile);
	pFile = NULL;
}

void format_string_v(std::string& result, const char *format,
	va_list arg_list)
{
	result.clear();
	int size = _vscprintf(format, arg_list);
	char *buffer = (char *)malloc(size + 1);
	if (NULL != buffer)
	{
		vsprintf(buffer, format, arg_list);
		result = buffer;
		free(buffer);
	}
}

std::string format_string(const char *format, ...)
{
	std::string result;

	va_list arg_list;
	va_start(arg_list, format);
	format_string_v(result, format, arg_list);
	va_end(arg_list);

	return result;
}

std::string get_loctime_str(time_t t)
{
	int32_t year, month, day, hour, minute, second;
	struct tm tm;
	localtime_s(&tm, &t);
	year = tm.tm_year + 1900;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;
	hour = tm.tm_hour;
	minute = tm.tm_min;
	second = tm.tm_sec;
	return format_string("%04d-%02d-%02d %02d:%02d:%02d",
		year, month, day, hour, minute, second);
}

#endif