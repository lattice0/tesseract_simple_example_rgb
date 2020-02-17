#ifndef _CT_STREAM_H_
#define _CT_STREAM_H_

#if __GNUC__ >= 4
#define CTSTREAM_API __attribute__ ((visibility("default")))
#else
#define CTSTREAM_API
#endif

#ifndef CT_STD_TYPES
#define CT_STD_TYPES
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed int          INT32;
typedef long long           INT64;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;
#endif

typedef struct _CT_FRAME_INFO
{
	UINT32			Version;
	UINT32			CodecType;//H264, JPG
	UINT32			ImageWidth;
	UINT32			ImageHeight;
	float			FrameRate;
	UINT32			FrameIndex0;
	UINT32			FrameIndex1;
	UINT32			FrameIndex2;
	UINT32			FrameIndex3;
	UINT32			Timestamp_sec;
	UINT32			Timestamp_usec;
}CT_FRAME_INFO;

typedef struct _CT_IMAGE_FRAME 
{
	char			*pDataBuff;
	UINT32			BuffSize;
	UINT32			DataSize;
	CT_FRAME_INFO	FrameInfo;
}CT_IMAGE_FRAME;

enum
{
	CT_STREAM_BY_TCP_SERVER = 0,
	CT_STREAM_BY_TCP_CLIENT = 1,
	CT_STREAM_BY_RTSP = 2,
	CT_STREAM_BY_TCP_SERVER_V2
};

#define CAPTURE_MAX_USERINFO_SIZE						(1024)
#define CAPTURE_MAX_CMD_CNT								(10)
//JPEG information
typedef struct JpegInfo
{
	UINT32 	 	ui32ImgWidth;								//image width
	UINT32		ui32ImgHeight;								//image height
	UINT32		ui32JpegQuality;							//JPEG quality
}RoseekJpegInfo;

//device information
typedef struct DevInfo
{
	UINT8		ui8CpuID[8];								//device CPU ID
	UINT32		ui32IP;										//device IP address
	UINT8		ui8Mac[8];									//device MAC address
	char		chModel[32];								//device Model string
}RoseekDevInfo;

//exposure parameters information
typedef struct ExpoInfo
{
	UINT32 		ui32ImageIndex;								//image frame index
	UINT32 		ui32ShutterTime;							//shutter time
	float		fGain;										//gain
	UINT32		ui32AdjustMode;								//parameter adjustment mode
	UINT32		ui32Region[4];								//metering region
	UINT32		ui32YMean;									//brightness mean value
	float		fColor;										//color saturation
	UINT32		ui32EnhanceLevel;							//image enhancement level
	UINT32		ui32DenoiseLevel;							//image denoise level
	float		fGamma;										//LUT gamma value
	float		fWbParams[3];								//white balance parameters
	float		fDigitalGain;								//digital gain
}RoseekExpoInfo;

//control information
typedef struct CtrlInfo
{
	UINT32  	ui32Need2Compress;							//whether the data should be compressed
	UINT32		ui32SubSampleMode;							//scale level
	UINT32		enumRunMode;					//camera run mode(TrgMode, FconMode)
	UINT32		enumImgFormat;		//image format
	UINT32		ui32SensorRes;								//scaler mode
	UINT32		ui32SaveToSD;								//whether save JPEG data to SD
	UINT32		ui32Rotate;									//whether image rotated
	UINT32		ui32Fps;									//image acquisition FPS
	float		fTemperature;								//CPU temperature
	UINT32		ui32TrgFlash;								//flash lamp in TrgMode state
	UINT32		ui32FconFlash;								//flash lamp in FconMode state
	UINT32		ui32Filter;									//filter state
	UINT32		ui32PwrSyncState;							//power sync state
	UINT32		ui32PwrSyncPhase;							//power sync phase
}RoseekCtrlInfo;

//capture command state
typedef struct CmdStateStruct
{
	UINT32	ui32CmdIndex;									//capture command index
	UINT32	ui32CurIndex;									//current capture step
	UINT32	ui32CmdInfo;									//capture command detail information
	UINT32  ui32CMDSource;									//command trigger source
}RoseekCmdStateStruct;

//capture command information
typedef struct CaptureCmdInfo
{
	UINT32 ui32FconWorkMode;								//FconMode Work Mode,1->Capture Mode 2->PreviewMode
	UINT32	ui32CurValidCmdCnt;								//Current valid command count
	RoseekCmdStateStruct CmdInfo[CAPTURE_MAX_CMD_CNT];  	//command information
}RoseekCaptureCmdInfo;

//image raw buffer information
typedef struct ImageBuffer
{
	UINT8*	pui8BufferAddr;									//buffer point header
	UINT8 	ui8Time[8]; 									//Real time clock
	RoseekJpegInfo JpegParam;								//JPEG parameters
	RoseekExpoInfo ExpoParam;								//exposure parameters
	RoseekCtrlInfo CtrlParam;								//control parameters
	RoseekCaptureCmdInfo CapCmdParam;						//capture mode command parameters
}RoseekImageBuffer;

//JPEG information
typedef struct ImgInfo
{
	char 		chImgDescript[256];							//image information description
	UINT8 		ui8Time[8]; 								//time
	RoseekJpegInfo JpegParam;								//JPEG parameters
	RoseekExpoInfo ExpoParam;								//exposure parameters
	RoseekCtrlInfo CtrlParam;								//control parameters
	RoseekDevInfo  DevParam;								//device parameters
	RoseekCaptureCmdInfo CapCmdParam;						//capture mode command parameters
}RoseekImgInfo;


#ifdef __cplusplus
extern "C"
{
#endif
	CTSTREAM_API const char * Roseek_Stream_GetModuleInfo();

    CTSTREAM_API void* Roseek_NetReceiver_Create(const char *p_url, int flag);
    CTSTREAM_API void Roseek_NetReceiver_Close(void *p_receiver);
	CTSTREAM_API int Roseek_NetReceiver_SetBuffParams(void *p_receiver, int max_buff_count, int max_buff_size);
	CTSTREAM_API int Roseek_NetReceiver_Run(void *p_receiver);
    CTSTREAM_API int Roseek_NetReceiver_Stop(void *p_receiver);
    CTSTREAM_API int Roseek_NetReceiver_Reconnect(void *p_receiver);
    CTSTREAM_API int Roseek_NetReceiver_GetStreamCount(void *p_receiver, int *p_count);
    CTSTREAM_API int Roseek_NetReceiver_GetFrame(void *p_receiver, int stream_index, CT_IMAGE_FRAME *p_frame);
    CTSTREAM_API int Roseek_NetReceiver_ReleaseFrame(void *p_receiver, int stream_index, CT_IMAGE_FRAME *p_frame);

	CTSTREAM_API void* Roseek_NetStreamer_Create(int type);
	CTSTREAM_API void Roseek_NetStreamer_Close(void* p_streamer);
	CTSTREAM_API int Roseek_NetStreamer_SetBuffParams(void *p_streamer, int max_buff_count, int max_buff_size);
	CTSTREAM_API int Roseek_NetStreamer_Listen(void* p_streamer, UINT32 ip, UINT16 port);
	CTSTREAM_API int Roseek_NetStreamer_Connect(void* p_streamer, UINT32 ip, UINT16 port);
	CTSTREAM_API int Roseek_NetStreamer_SendFrame(void* p_streamer, CT_IMAGE_FRAME *p_frame);
	CTSTREAM_API int Roseek_NetStreamer_IsHasClient(void* p_streamer);
	CTSTREAM_API int Roseek_NetStreamer_SetStreamName(void* p_streamer, const char * p_name);
	CTSTREAM_API int Roseek_NetStreamer_AddAuth(void* p_streamer, const char * p_username, const char * p_password);

	CTSTREAM_API int Roseek_NetStreamer_SendFrameV2(void* p_streamer, CT_IMAGE_FRAME *p_frame, RoseekImgInfo *pImgInfo, const char *pUserInfo);
#ifdef __cplusplus
}
#endif

#endif