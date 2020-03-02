#ifndef __CT_MEDIA_H__
#define __CT_MEDIA_H__

#if __GNUC__ >= 4
#define CTMEDIA_API __attribute__ ((visibility("default")))
#else
#define CTMEDIA_API
#endif

#ifdef __cplusplus
extern "C" {
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

enum {
		CT_USE_AUTO = 0,
		CT_USE_HW,
		CT_USE_SW
	};

#define CT_MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((UINT32)(UINT8)(ch0) | ((UINT32)(UINT8)(ch1) << 8) |   \
	((UINT32)(UINT8)(ch2) << 16) | ((UINT32)(UINT8)(ch3) << 24 ))

enum {
	CT_FOURCC_NV12         = CT_MAKEFOURCC('N','V','1','2'),   /* Native Format */
	CT_FOURCC_NV16         = CT_MAKEFOURCC('N','V','1','6'),
	CT_FOURCC_YV12         = CT_MAKEFOURCC('Y','V','1','2'),
	CT_FOURCC_RGB3         = CT_MAKEFOURCC('R','G','B','3'),   /* deprecated */
	CT_FOURCC_RGB4         = CT_MAKEFOURCC('R','G','B','4'),   /* ARGB in that order, A channel is 8 MSBs */
	CT_FOURCC_BGR4         = CT_MAKEFOURCC('B','G','R','4'),   /* ABGR in that order, A channel is 8 MSBs */
	CT_CODEC_JPEG		   = CT_MAKEFOURCC('J','P','E','G'),
	CT_CODEC_AVC           = CT_MAKEFOURCC('A','V','C',' '),
	CT_CODEC_HEVC			=CT_MAKEFOURCC('H','E','V','C'),
	CT_CODEC_MPEG2         = CT_MAKEFOURCC('M','P','G','2')
};

/* CodecProfile, CodecLevel */
enum {
	CT_PROFILE_UNKNOWN                     =0,
	CT_LEVEL_UNKNOWN                       =0,

	/* AVC Profiles & Levels */
	CT_PROFILE_AVC_CONSTRAINT_SET0     = (0x100 << 0),
	CT_PROFILE_AVC_CONSTRAINT_SET1     = (0x100 << 1),
	CT_PROFILE_AVC_CONSTRAINT_SET2     = (0x100 << 2),
	CT_PROFILE_AVC_CONSTRAINT_SET3     = (0x100 << 3),
	CT_PROFILE_AVC_CONSTRAINT_SET4     = (0x100 << 4),
	CT_PROFILE_AVC_CONSTRAINT_SET5     = (0x100 << 5),

	CT_PROFILE_AVC_BASELINE                =66,
	CT_PROFILE_AVC_MAIN                    =77,
	CT_PROFILE_AVC_EXTENDED                =88,
	CT_PROFILE_AVC_HIGH                    =100,
	CT_PROFILE_AVC_CONSTRAINED_BASELINE    =CT_PROFILE_AVC_BASELINE + CT_PROFILE_AVC_CONSTRAINT_SET1,
	CT_PROFILE_AVC_CONSTRAINED_HIGH        =CT_PROFILE_AVC_HIGH     + CT_PROFILE_AVC_CONSTRAINT_SET4
	+ CT_PROFILE_AVC_CONSTRAINT_SET5,
	CT_PROFILE_AVC_PROGRESSIVE_HIGH        =CT_PROFILE_AVC_HIGH     + CT_PROFILE_AVC_CONSTRAINT_SET4,

	CT_LEVEL_AVC_1                         =10,
	CT_LEVEL_AVC_1b                        =9,
	CT_LEVEL_AVC_11                        =11,
	CT_LEVEL_AVC_12                        =12,
	CT_LEVEL_AVC_13                        =13,
	CT_LEVEL_AVC_2                         =20,
	CT_LEVEL_AVC_21                        =21,
	CT_LEVEL_AVC_22                        =22,
	CT_LEVEL_AVC_3                         =30,
	CT_LEVEL_AVC_31                        =31,
	CT_LEVEL_AVC_32                        =32,
	CT_LEVEL_AVC_4                         =40,
	CT_LEVEL_AVC_41                        =41,
	CT_LEVEL_AVC_42                        =42,
	CT_LEVEL_AVC_5                         =50,
	CT_LEVEL_AVC_51                        =51,
	CT_LEVEL_AVC_52                        =52,

	/* MPEG-2 Profiles & Levels */
	CT_PROFILE_MPEG2_SIMPLE                =0x50,
	CT_PROFILE_MPEG2_MAIN                  =0x40,
	CT_PROFILE_MPEG2_HIGH                  =0x10,

	CT_LEVEL_MPEG2_LOW                     =0xA,
	CT_LEVEL_MPEG2_MAIN                    =0x8,
	CT_LEVEL_MPEG2_HIGH                    =0x4,
	CT_LEVEL_MPEG2_HIGH1440                =0x6,

	/* VC1 Profiles & Levels */
	CT_PROFILE_VC1_SIMPLE                  =(0+1),
	CT_PROFILE_VC1_MAIN                    =(4+1),
	CT_PROFILE_VC1_ADVANCED                =(12+1),

	/* VC1 levels for simple & main profiles */
	CT_LEVEL_VC1_LOW                       =(0+1),
	CT_LEVEL_VC1_MEDIAN                    =(2+1),
	CT_LEVEL_VC1_HIGH                      =(4+1),

	/* VC1 levels for the advanced profile */
	CT_LEVEL_VC1_0                         =(0x00+1),
	CT_LEVEL_VC1_1                         =(0x01+1),
	CT_LEVEL_VC1_2                         =(0x02+1),
	CT_LEVEL_VC1_3                         =(0x03+1),
	CT_LEVEL_VC1_4                         =(0x04+1),

	/* HEVC Profiles & Levels & Tiers */
	CT_PROFILE_HEVC_MAIN             =1,
	CT_PROFILE_HEVC_MAIN10           =2,
	CT_PROFILE_HEVC_MAINSP           =3,

	CT_LEVEL_HEVC_1   = 10,
	CT_LEVEL_HEVC_2   = 20,
	CT_LEVEL_HEVC_21  = 21,
	CT_LEVEL_HEVC_3   = 30,
	CT_LEVEL_HEVC_31  = 31,
	CT_LEVEL_HEVC_4   = 40,
	CT_LEVEL_HEVC_41  = 41,
	CT_LEVEL_HEVC_5   = 50,
	CT_LEVEL_HEVC_51  = 51,
	CT_LEVEL_HEVC_52  = 52,
	CT_LEVEL_HEVC_6   = 60,
	CT_LEVEL_HEVC_61  = 61,
	CT_LEVEL_HEVC_62  = 62,

	CT_TIER_HEVC_MAIN  = 0,
	CT_TIER_HEVC_HIGH  = 0x100,
};

#define CT_CODEC_H264 CT_CODEC_AVC
#define CT_CODEC_H265 CT_CODEC_HEVC

#define CT_MEDIA_SUCCESS							(0)
#define CT_MEDIA_ERROR_INVALID_PARAMETERS			(-1)
#define CT_MEDIA_ERROR_UNSUPPORTED					(-2)
#define CT_MEDIA_ERROR_EXCEPTION					(-3)
#define CT_MEDIA_ERROR_BUSY							(-4)
#define CT_MEDIA_ERROR_CREATEFAILED					(-5)
#define CT_MEDIA_ERROR_OPENFAILED					(-6)
#define CT_MEDIA_ERROR_TIMEOUT						(-7)


typedef int (*FUNC_ReadRawData)(void * pToken, UINT32 DataFormat, UINT32 Width, UINT32 Height, UINT32 DataPitch, void * pData[4]);
typedef int (*FUNC_ReadBitstream)(void * pToken, void * pBuff, unsigned int BuffSize);
typedef int (*FUNC_WriteRawData)(void * pToken, UINT32 DataFormat, UINT32 Width, UINT32 Height, UINT32 DataPitch, void * pData[4]);
typedef int (*FUNC_WriteBitstream)(void * pToken, void * pData, UINT32 DataSize);
typedef int (*FUNC_PreProcessRawData)(void * pToken, UINT32 DataFormat, UINT32 Width, UINT32 Height, UINT32 DataPitch, void * pData[4]);

typedef struct _MediaEncoderParams
{
	UINT32		HWOrSW;
	UINT32		SourceFormat;
	UINT32		SourceWidth;
	UINT32		SourceHeight;
	UINT32		DestCodecID;
	UINT32		DestWidth;
	UINT32		DestHeight;
	float		FrameRate;
	UINT32		BitRate;
	UINT32		Quality;
	UINT32		GopPicSize;
	UINT32		CodecProfile;
	UINT32		CodecLevel;
	FUNC_ReadRawData	FuncReader;
	void				*pTokenReader;
	FUNC_WriteBitstream FuncWriter;
	void				*pTokenWriter;
}MediaEncoderParams;

typedef struct _ProcAmpParam
{
	float   brightness;
	float   contrast;
	float   saturation;
	float   hue;
	UINT32	mode;
} ProcAmpParam_t;

typedef struct _DenoiseParam
{
	UINT32  factor;
	UINT32	mode;
} DenoiseParam_t;

typedef struct _DetailParam
{
	UINT32  factor;
	UINT32	mode;
} DetailParam_t;

typedef struct _MediaEncoderParamsV1
{
	UINT32		HWOrSW;
	UINT32		SourceFormat;
	UINT32		SourceWidth;
	UINT32		SourceHeight;
	float		SourceFrameRate;
	UINT32		DestCodecID;
	UINT32		DestWidth;
	UINT32		DestHeight;
	float		DestFrameRate;
	UINT32		BitRate;
	UINT32		Quality;
	UINT32		GopPicSize;
	UINT32		CodecProfile;
	UINT32		CodecLevel;
	FUNC_ReadRawData	FuncReader;
	void				*pTokenReader;
	FUNC_WriteBitstream FuncWriter;
	void				*pTokenWriter;

	ProcAmpParam_t	ProcAmpParam;
	DenoiseParam_t	DenoiseParam;
	DetailParam_t	DetailParam;
}MediaEncoderParamsV1;

typedef struct _MediaDecoderParams
{
	UINT32		HWOrSW;
	UINT32		SourceCodecID;
	FUNC_ReadBitstream	FuncReader;
	void				*pTokenReader;
	FUNC_WriteRawData	FuncWriter;
	void				*pTokenWriter;
}MediaDecoderParams;

CTMEDIA_API const char * Roseek_Media_GetModuleInfo();

CTMEDIA_API	void Roseek_MediaEncoder_InitParams(MediaEncoderParams *pParams);
CTMEDIA_API int Roseek_MediaEncoder_Create(void ** pEncoderHandler, MediaEncoderParams *pParams);
CTMEDIA_API	void Roseek_MediaEncoder_InitParamsV1(MediaEncoderParamsV1 *pParams);
CTMEDIA_API int Roseek_MediaEncoder_CreateV1(void ** pEncoderHandler, MediaEncoderParamsV1 *pParams);
CTMEDIA_API void Roseek_MediaEncoder_Close(void * hEncoder);
CTMEDIA_API int Roseek_MediaEncoder_Run(void * hEncoder, UINT32 *pRunFlag);
CTMEDIA_API int Roseek_MediaEncoder_EncodeFrameSync(void * hEncoder, UINT8 * pSrcData[4], UINT32 Format, UINT32 Width, UINT32 Height, UINT8 * pDestBuff, UINT32 *pInOutSize);
CTMEDIA_API int Roseek_MediaEncoder_RegisterRawDataPreProcessFunc(void * hEncoder, FUNC_PreProcessRawData Func, void * pToken);

CTMEDIA_API void Roseek_MediaDecoder_InitParams(MediaDecoderParams *pParams);
CTMEDIA_API int Roseek_MediaDecoder_Create(void ** pDecoderHandler, MediaDecoderParams *pParams);
CTMEDIA_API void Roseek_MediaDecoder_Close(void * hDecoder);
CTMEDIA_API int Roseek_MediaDecoder_Run(void * hDecoder, UINT32 *pRunFlag);
CTMEDIA_API int Roseek_MediaDecoder_DecodeFrameSync(void * hDecoder, UINT8 * pData, UINT32 DataSize, UINT8 * pImageData[4], UINT32 *pFormat, UINT32 *pWidth, UINT32 *pHeight);

#ifdef __cplusplus
}
#endif

#endif