#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include <sys/timeb.h>
#include <iostream>

#include "include/WPMainCore.h"
#include "include/CTMedia.h"
#include "include/CTStream.h"
#include "yuv2rgb.h"
#include "ImageStream.h"
static unsigned __stdcall ThreadMainLoop(void *pParam);
static int util_getTimeOfDay(struct timeval *ptv);

typedef struct _MainContext
{
	int m_ThreadWatch;
	void *pEncoder;
	void *pStreamer;
}MainContext_t;


int main2(int argc, char *argv[])
{
	int ret;
	MainContext_t MainCT;
	HANDLE hThreadMainLoop = NULL;
	UINT32 nWidth, nHeight;
	float FrameRate;
	MediaEncoderParamsV1 EncoderParams;

	do
	{
		memset(&MainCT, 0, sizeof(MainCT));

		ret = Roseek_MainCore_Init(0);
		if (ret != 0)
		{
			break;
		}

		ret = Roseek_ImageAcquisition_Start();
		if (ret != 0)
		{
			break;
		}

		Roseek_ImageAcquisition_GetResolution(NULL, NULL, NULL, &nWidth, &nHeight);
		Roseek_ImageAcquisition_GetFrameRate(&FrameRate);

		Roseek_MediaEncoder_InitParamsV1(&EncoderParams);
		EncoderParams.HWOrSW = CT_USE_AUTO;
		EncoderParams.SourceFormat = CT_FOURCC_NV12;
		EncoderParams.SourceWidth = nWidth;
		EncoderParams.SourceHeight = nHeight;
		EncoderParams.SourceFrameRate = FrameRate;
		EncoderParams.DestCodecID = CT_CODEC_H264;
		EncoderParams.DestWidth = nWidth;
		EncoderParams.DestHeight = nHeight;
		EncoderParams.DestFrameRate = 25.0f;
		EncoderParams.BitRate = 8000;
		ret = Roseek_MediaEncoder_CreateV1(&MainCT.pEncoder, &EncoderParams);
		printf("Roseek_MediaEncoder_CreateV1 -> handle is %p, ret is %d\n", MainCT.pEncoder, ret);
        /*
		MainCT.pStreamer = Roseek_NetStreamer_Create(CT_STREAM_BY_RTSP);
		if (MainCT.pStreamer)
		{
			ret = Roseek_NetStreamer_SetStreamName(MainCT.pStreamer, "stream");
			ret = Roseek_NetStreamer_SetBuffParams(MainCT.pStreamer, 10, 500 * 1024);

			ret = Roseek_NetStreamer_Listen(MainCT.pStreamer, 0, 8557);
		}
        */
		MainCT.m_ThreadWatch = 1;
        /*
		hThreadMainLoop = (HANDLE)_beginthreadex(NULL, 0, ThreadMainLoop, (void*)&MainCT, 0, NULL);
		if (hThreadMainLoop == NULL)
		{
			break;
		}

		while (1)
		{
			Sleep(1000);
		}
        */

	} while (0);

	MainCT.m_ThreadWatch = 0;

	if (hThreadMainLoop)
	{
		if (WaitForSingleObject(hThreadMainLoop, 3000) == WAIT_TIMEOUT)
		{
			TerminateThread(hThreadMainLoop, 0);
		}
		CloseHandle(hThreadMainLoop);
		hThreadMainLoop = NULL;
	}

	if (MainCT.pEncoder)
	{
		Roseek_MediaEncoder_Close(MainCT.pEncoder);
		MainCT.pEncoder = NULL;
	}

	if (MainCT.pStreamer)
	{
		Roseek_NetStreamer_Close(MainCT.pStreamer);
		MainCT.pStreamer = NULL;
	}

	Roseek_ImageAcquisition_Stop();
	Roseek_MainCore_UnInit();

	getchar();

	return 0;
}

typedef struct _RAWFrame
{
	RawFrameInfo	FrameInfo;
	void			*pFrameBuff;
}RAWFrame;

void imageStreamThread(void *pParam, std::function<void(uint8_t*, int, int)> rgbUpdateCallback)
{
	MainContext_t *pCT = (MainContext_t*)pParam;
	int ret;
	UINT32 nWidth, nHeight, FrameBuffSize, DestBuffSize, InOutSize, TickBegin, TickEnd;
	RAWFrame Frame;
	void *pDestBuff = NULL;
	UINT8 *pSrcData[4] = { 0 };
	CT_IMAGE_FRAME BitsFrame;
	struct timeval timestamp;

	Roseek_ImageAcquisition_GetResolution(NULL, NULL, NULL, &nWidth, &nHeight);
	FrameBuffSize = nWidth*nHeight * 3;
	DestBuffSize = nWidth*nHeight;
	Frame.pFrameBuff = malloc(FrameBuffSize);
	pDestBuff = malloc(DestBuffSize);
	int rgbaBuffSize = nWidth*nHeight*4*sizeof(unsigned char);
    unsigned char* rgbaBuffer = new unsigned char[rgbaBuffSize];

    int rgbBuffSize = nWidth*nHeight*4*sizeof(unsigned char);
    unsigned char* rgbBuffer = new unsigned char[rgbBuffSize];
	if (Frame.pFrameBuff == NULL || pDestBuff == NULL)
	{
		if (Frame.pFrameBuff) free(Frame.pFrameBuff);
		if (pDestBuff) free(pDestBuff);
        std::cout << "(Frame.pFrameBuff == NULL || pDestBuff == NULL" << std::endl;
    }
    std::cout << "gonna enter while loop" << std::endl;
    while (true)
	{
		Frame.FrameInfo.Size = sizeof(Frame.FrameInfo);
		ret = Roseek_ImageAcquisition_FetchFrame(Frame.pFrameBuff, FrameBuffSize, &Frame.FrameInfo, 100);
		if (ret == 0)
		{
            if (Frame.FrameInfo.ImageFormat == WP_RAWIMAGE_FORMAT_YUV420SP)
            {
                //std::cout << "yuv420sp" << std::endl;
            }
            else if (Frame.FrameInfo.ImageFormat == WP_RAWIMAGE_FORMAT_MONO)
            {
                std::cout << "mono" << std::endl;
                std::exit(3);

            }
			if (Frame.FrameInfo.TriggerSource == 1)
			{
				//printf("<%u>Continuous frame is come.\n", Frame.FrameInfo.FrameIndex);
			}
			else
			{
				//printf("<%u>Grab frame is come, source is 0x%x.\n", Frame.FrameInfo.FrameIndex, Frame.FrameInfo.TriggerSource);
			}
			//nv21_to_rgba(yuv_buf,rgb_buf,width,height);
            nv21_to_rgb((unsigned char *) Frame.pFrameBuff,rgbBuffer,nWidth,nHeight);
            std::cout << "." << std::flush;
            //printf("decoded yuv to rgba");

			/*
			if (pCT->pEncoder)
			{
				if (Frame.FrameInfo.ImageFormat == WP_RAWIMAGE_FORMAT_YUV420SP)
				{
					pSrcData[0] = (UINT8*)(Frame.pFrameBuff);
					pSrcData[1] = (UINT8*)(Frame.pFrameBuff) + nWidth*nHeight;
				}
				else if (Frame.FrameInfo.ImageFormat == WP_RAWIMAGE_FORMAT_MONO)
				{
					pSrcData[0] = (UINT8*)(Frame.pFrameBuff);
					pSrcData[1] = (UINT8*)(Frame.pFrameBuff) + nWidth*nHeight;
					memset(pSrcData[1], 128, nWidth*nHeight / 2);
				}

				InOutSize = DestBuffSize;
				TickBegin = GetTickCount();
				ret = Roseek_MediaEncoder_EncodeFrameSync(pCT->pEncoder, pSrcData, 0, nWidth, nHeight, (UINT8*)pDestBuff, &InOutSize);
				TickEnd = GetTickCount();
				if (ret == 0 && InOutSize > 0)
				{
					printf("<%u>H264 encode success, time is %ums, size is %u.\n", Frame.FrameInfo.FrameIndex, TickEnd - TickBegin, InOutSize);
					if (pCT->pStreamer)
					{
						BitsFrame.pDataBuff = (char*)pDestBuff;
						BitsFrame.BuffSize = DestBuffSize;
						BitsFrame.DataSize = InOutSize;
						util_getTimeOfDay(&timestamp);
						BitsFrame.FrameInfo.Timestamp_sec = timestamp.tv_sec;
						BitsFrame.FrameInfo.Timestamp_usec = timestamp.tv_usec;
						Roseek_NetStreamer_SendFrame(pCT->pStreamer, &BitsFrame);
					}
				}
				else
				{
					printf("<%u>JPG encode failed, ret is %d.\n", Frame.FrameInfo.FrameIndex, ret);
				}
			}
			*/
		}
	}

	free(Frame.pFrameBuff);
	free(pDestBuff);
    std::cout << "finished decoder thread" << std::endl;
}
