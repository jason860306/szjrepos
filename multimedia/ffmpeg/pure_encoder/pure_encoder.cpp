/**
 * ============================================================================
 * @file	pure_encoder.cpp
 *
 * @brief   一个“纯净”的编码器
 * @details	它仅仅通过调用libavcodec将YUV数据编码为H.264/HEVC等格式的压缩视频码流。
 *
 * @version 1.0  
 * @date	2015/09/07 11:48
 *
 * @author  志杰, shizhijie@baofeng.com
 * ============================================================================
 */

#include "stdafx.h"
#include <stdio.h>

extern "C"
{
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavcodec/avcodec.h"
}

///< test different codec
#define TEST_H264 0
#define TEST_HEVC 0

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		printf("usage: %s in_file out_file\n", argv[0]);
		return -1;
	}

	AVCodec *p_codec = NULL;
	AVCodecContext *p_codec_ctx = NULL;
	int i = 0, ret = 0, got_output = 0, y_size = 0, frame_cnt = 0;
	FILE *p_fin = NULL, *p_fout = NULL;
	AVFrame *p_frame = NULL;
	AVPacket pkt;

	const char *p_in_fpath = argv[1], *p_out_fpath = argv[2];
	AVCodecID codec_id = AV_CODEC_ID_NONE;

#if TEST_HEVC
	codec_id = AV_CODEC_ID_HEVC;
#elif TEST_H264
	codec_id = AV_CODEC_ID_H264;
#else
    codec_id = AV_CODEC_ID_MPEG4;
#endif

	int in_w = 480, in_h = 272;
	int frame_num = 100;

	avcodec_register_all();

	if (NULL == (p_codec = avcodec_find_encoder(codec_id)))
	{
		printf("Codec not found\n");
		return -1;
	}
	if (NULL == (p_codec_ctx = avcodec_alloc_context3(p_codec)))
	{
		printf("Could not allocate video codec context\n");
		return -1;
	}
	p_codec_ctx->bit_rate = 40000;
	p_codec_ctx->width = in_w;
	p_codec_ctx->height = in_h;
	p_codec_ctx->time_base.num = 1;
	p_codec_ctx->time_base.den = 25;
	p_codec_ctx->gop_size = 10;
	p_codec_ctx->max_b_frames = 1;
	p_codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

	if (AV_CODEC_ID_H264 == codec_id)
	{
		av_opt_set(p_codec_ctx->priv_data, "preset", "slow", 0);
	}

	if (avcodec_open2(p_codec_ctx, p_codec, NULL) < 0)
	{
		printf("Could not open codec\n");
		return -1;
	}

	if (NULL == (p_frame == av_frame_alloc()))
	{
		printf("Could not allocate video frame\n");
		return -1;
	}
	p_frame->format = p_codec_ctx->pix_fmt;
	p_frame->width = p_codec_ctx->width;
	p_frame->height = p_codec_ctx->height;

	if ((ret = av_image_alloc(p_frame->data, p_frame->linesize, p_codec_ctx->width, p_codec_ctx->height, p_codec_ctx->pix_fmt, 16)) < 0)
	{
		printf("Could not allocate raw picture buffer\n");
		return -1;
	}

	///< Input raw data
	if (NULL == (p_fin = fopen(p_in_fpath, "rb")))
	{
		printf("Could not open %s\n", p_in_fpath);
		return -1;
	}
	///< Output bitstream
	if (NULL == (p_fout = fopen(p_out_fpath, "wb")))
	{
		printf("Could not open %s\n");
		return -1;
	}

	y_size = p_codec_ctx->width * p_codec_ctx->height;

	///< Encode
	for (i = 0; i < frame_num; ++i)
	{
		av_init_packet(&pkt);
		pkt.data = NULL; ///< packet data will be allocate by encoder
		pkt.size = 0;
		///< read raw yuv data
		if (fread(p_frame->data[0], 1, y_size, p_fin) <= 0 || ///< Y
			fread(p_frame->data[1], 1, y_size / 4, p_fin) <= 0 || ///< U
			fread(p_frame->data[2], 1, y_size / 4, p_fin) <= 0) ///< V
		{
			return -1;
		}
		else if (feof(p_fin))
		{
			break;
		}

		p_frame->pts = i;
		
		///< encode the image
		if ((ret = avcodec_encode_video2(p_codec_ctx, &pkt, p_frame, &got_output) < 0))
		{
			printf("Error encoding frame\n");
			return -1;
		}
		if (got_output)
		{
			printf("Succeed to encode frame: %5d\tsize: %5d\n", frame_cnt, pkt.size);
			++frame_cnt;
			fwrite(pkt.data, 1, pkt.size, p_fout);
			av_free_packet(&pkt);
		}
	}

	///< Flush Encoder
	for (got_output = 1; got_output; ++i)
	{
		if ((ret = avcodec_encode_video2(p_codec_ctx, &pkt, NULL, &got_output)) < 0)
		{
			printf("Error encoding frame\n");
			return -1;
		}
		if (got_output)
		{
			printf("Flush encoder: Succeed to encode 1 frame!\tsize: %5d\n", pkt.size);
			fwrite(pkt.data, 1, pkt.size, p_fout);
			av_free_packet(&pkt);
		}
	}

	fclose(p_fout);
	avcodec_close(p_codec_ctx);
	av_free(p_codec_ctx);
	av_freep(&p_frame->data[0]);
	av_frame_free(&p_frame);

	return 0;
}
