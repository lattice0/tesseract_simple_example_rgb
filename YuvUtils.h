#ifndef _CT_YUV_UTILS_H_
#define _CT_YUV_UTILS_H_

int CropImageYuv420SP(unsigned char * pSrc, unsigned int SrcWidth, unsigned int SrcHeight, unsigned char * pDest, unsigned int DestWidth, unsigned int DestHeight, int x, int y);
int Yuv422SPToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch);
int Yuv420SPToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch);
int Yuv444ToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch);
void yuv2rgb_init();
int Yuv422SPToRgb24(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height);
int Yuv420SPToRgb24(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height);
int WriteRgb24ToBmpFile(unsigned char * pData, unsigned int nWidth, unsigned int nHeight, char *pFilePath);
int WriteMonoToBmpFile(unsigned char * pData, unsigned int nWidth, unsigned int nHeight, char *pFilePath);
enum
{
	RAW_GBRG,
	RAW_BGGR,
	RAW_GRBG,
	RAW_RGGB
};
int RawToRgb24(unsigned char * pSrc, unsigned int RawFormat, unsigned char * pDest, unsigned int width, unsigned int height);

#endif
