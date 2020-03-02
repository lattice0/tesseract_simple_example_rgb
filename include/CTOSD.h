#ifndef _CTOSD_H_
#define _CTOSD_H_

#if __GNUC__ >= 4
#define CTOSD_API __attribute__ ((visibility("default")))
#else
#define CTOSD_API
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

#define CT_SUCCESS							(0)
#define CT_ERROR_INVALID_PARAMETERS			(-1)
#define CT_ERROR_UNSUPPORTED				(-2)
#define CT_ERROR_EXCEPTION					(-3)
#define CT_ERROR_BUSY						(-4)
#define CT_ERROR_CREATEFAILED				(-5)
#define CT_ERROR_OPENFAILED					(-6)
#define CT_ERROR_TIMEOUT					(-7)
#define CT_ERROR_BUFFNOTENOUGH				(-8)
#define CT_ERROR_LACKOFRESOURCE				(-9)

enum
{
	IMG_FMT_YUV420SP,
	IMG_FMT_MAX
};

typedef struct _OSDFormat
{
	UINT32		FontWidth;
	UINT32		FontHeight;
	UINT32		FontColor;
	UINT32		BackColor;
	UINT32		ImageFormat;
	UINT32		IsRevertColor;
}OSDFormat;

typedef struct _RAWImageInfo
{
	UINT32		ImageFormat;
	UINT32		ImageWidth;
	UINT32		ImageHeight;
	UINT8*		pImageData[4];
}RAWImageInfo;

CTOSD_API const char * Roseek_OSD_GetModuleInfo();

CTOSD_API int Roseek_OSD_Create(void ** pHandle, const char * pFontFilePath);
CTOSD_API int Roseek_OSD_Close(void * Handle);

CTOSD_API int Roseek_OSD_AddTextCache(void * Handle, OSDFormat Fmt, const UINT16 * pUnicodeText);

CTOSD_API int Roseek_OSD_DrawText(void * Handle, RAWImageInfo ImageInfo, OSDFormat Fmt, UINT32 LocationX, UINT32 LocationY, UINT32 Alpha, const UINT16 * pUnicodeText);

CTOSD_API int Roseek_OSD_MBCSToUTF16(const char * pText, const char * pCodeName, UINT16 *pBuff, UINT32 BuffSize);

#ifdef __cplusplus
}
#endif

#endif
