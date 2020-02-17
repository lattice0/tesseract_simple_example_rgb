// KFDemoDecodeH264AndStream.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include <sys/timeb.h>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "CTMedia.h"
#include "CTStream.h"
#include "DecodeH264AndStream.h"
//#include "../include/RSMediaRender.h"


#define MAX_IMAGE_WIDTH		8000
#define MAX_IMAGE_HEIGHT	8000

#define CT_MEDIA_SYNC

typedef struct
{
	UINT32	frame_count;
	UINT32	tick_begin;
	void*   pointer_net_video_stream;
	void*	pointer_render;
	UINT32	is_render_inited;
}MainContext;

UINT32 run_flag = 0;

int decoder_thread()
{
	int ret;
	MainContext main_context;
	MediaDecoderParams decoder_params;
	void * pointer_net_video_stream_receiver = nullptr;
	void * pointer_decoder = nullptr;
	void * handle_render = nullptr;
    std::cout << "Roseek connection " << std::endl;
    pointer_net_video_stream_receiver = Roseek_NetReceiver_Create("rtsp://127.0.0.1:8557/stream", 0);
	if (pointer_net_video_stream_receiver)
    {
        std::cout << "pointer_net_video_stream_receiver" << std::endl;
		Roseek_NetReceiver_SetBuffParams(pointer_net_video_stream_receiver, 10, 2 * 1024 * 1024);
		Roseek_NetReceiver_Run(pointer_net_video_stream_receiver);
	}

	//handle_render = ROSEEK_MRCreateOne(2);

	memset(&main_context, 0, sizeof(main_context));
	main_context.pointer_net_video_stream = pointer_net_video_stream_receiver;
	//main_context.pointer_render = handle_render;
	//main_context.is_render_inited = 0;

	run_flag = 1;
	Roseek_MediaDecoder_InitParams(&decoder_params);
	decoder_params.HWOrSW = CT_USE_AUTO;
	decoder_params.SourceCodecID = CT_CODEC_H264;

#ifdef CT_MEDIA_SYNC
#else
	decoder_params.FuncReader = My_ReadBitstream;
#endif
	decoder_params.pTokenReader = &main_context;
#ifdef CT_MEDIA_SYNC
#else
	decoder_params.FuncWriter = My_WriteRawData;
#endif
	decoder_params.pTokenWriter = &main_context;
	Roseek_MediaDecoder_Create(&pointer_decoder, &decoder_params);

	if (pointer_decoder)
	{
        std::cout << "decoder created" << std::endl;
#ifdef CT_MEDIA_SYNC
		CT_IMAGE_FRAME frame;
		unsigned char	*pointer_buffer_render;
		int number_pitch;
		//MSG     mesage;
		UINT32 data_format, width, height;
		UINT8 * pointer_image_data[4];

		pointer_image_data[0] = (UINT8*)malloc(MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT);
		pointer_image_data[1] = (UINT8*)malloc(MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT);
		pointer_image_data[2] = (UINT8*)malloc(MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT);
		pointer_image_data[3] = NULL;

		while (1)
        {
            std::cout << "while" << std::endl;
			while (Roseek_NetReceiver_GetFrame(pointer_net_video_stream_receiver, 0, &frame) != 0 && run_flag)
			{
				//Sleep(100);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
            std::cout << "got" << std::endl;
			ret = Roseek_MediaDecoder_DecodeFrameSync(pointer_decoder, (UINT8*)(frame.pDataBuff), frame.DataSize, pointer_image_data, &data_format, &width, &height);

			Roseek_NetReceiver_ReleaseFrame(pointer_net_video_stream_receiver, 0, &frame);

			if (ret != 0)
			{
				continue;
			}

			if (data_format == CT_FOURCC_NV12)
			{
				printf("Decode success, width is %d, height is %d, format is CT_FOURCC_NV12\n", width, height);
			}
			else
			{
				printf("Decode success, width is %d, height is %d, format is 0x%X\n", width, height, data_format);
			}
			/*
			if (!main_context.is_render_inited)
			{
				ROSEEK_MRSetVideoFormat(main_context.pointer_render, 3, width, height);
				ROSEEK_MRActiveVideoRender(main_context.pointer_render);
				main_context.is_render_inited= 1;
			}
			*/

			pointer_buffer_render = NULL;
			/*
			ROSEEK_MRLockVideoBuffer(main_context.pointer_render, (void**)&pointer_buffer_render, &number_pitch);
			if (pointer_buffer_render)
			{
				Yuv420SPToYV12((unsigned char *)(pointer_image_data[0]), (unsigned char *)(pointer_image_data[1]), pointer_buffer_render, width, height, number_pitch);
			}
			ROSEEK_MRUnlockVideoBuffer(main_context.pointer_render);
			ROSEEK_MRDisplayVideo(main_context.pointer_render);

			while (PeekMessage(&mesage, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&mesage);
				DispatchMessage(&mesage);
			}
			*/
		}
#else
		Roseek_MediaDecoder_Run(hDecoder, &run_flag);
#endif

		main_context.pointer_net_video_stream = NULL;

		Roseek_MediaDecoder_Close(pointer_decoder);
	}

	if (pointer_net_video_stream_receiver)
	{
		Roseek_NetReceiver_Close(pointer_net_video_stream_receiver);
	}

	return 0;
}

static int Yuv420SPToYV12(unsigned char * pSrcY, unsigned char * pSrcUV, unsigned char * pDest, unsigned int width, unsigned int height, int pitch)
{
	unsigned int i, j;

	for (i = 0; i < height; ++i)
	{
		memcpy(pDest + i*pitch, pSrcY + i*width, width);
	}

	unsigned char *pDestU, *pDestV;
	pDestV = pDest + pitch * height;
	pDestU = pDest + pitch * height + (pitch / 2) * (height / 2);

	for (i = 0; i < height; i += 2)
	{
		for (j = 0; j < width; j += 2)
		{
			pDestU[j / 2] = pSrcUV[j + 0];
			pDestV[j / 2] = pSrcUV[j + 1];
		}
		pDestU += pitch / 2;
		pDestV += pitch / 2;
		pSrcUV += width;
	}

	return 0;
}
