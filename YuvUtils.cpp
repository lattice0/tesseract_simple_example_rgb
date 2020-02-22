#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "YuvUtils.h"

int CropImageYuv420SP(unsigned char * pSrc, unsigned int SrcWidth, unsigned int SrcHeight, unsigned char * pDest, unsigned int DestWidth, unsigned int DestHeight, int x, int y)
{
	unsigned int i, GapTop, GapBottom, Gapleft, GapRight, CropX, CropY, RealCopyWidth, RealCopyHeight;
	unsigned char * pSrcY, *pSrcUV, *pDestY, *pDestUV;

	if (pSrc == NULL || pDest == NULL)
	{
		return -1;
	}

	if ((SrcWidth & 0x1) != 0 || (SrcHeight & 0x1) != 0 || (DestWidth & 0x1) != 0 || (DestHeight & 0x1) != 0)
	{
		return -1;
	}

	GapTop = GapBottom = Gapleft = GapRight = CropX = CropY = 0;

	if (SrcWidth <= DestWidth)
	{
		CropX = 0;
		if (x < 0)
		{
			Gapleft = (DestWidth - SrcWidth) / 2;
		}
		else
		{
			x &= ~0x1;
			if (x + SrcWidth > DestWidth)
			{
				x = DestWidth - SrcWidth;
			}
			Gapleft = x;
		}
		Gapleft &= ~0x1;
		RealCopyWidth = SrcWidth;
		GapRight = DestWidth - RealCopyWidth - Gapleft;
	}
	else
	{
		Gapleft = GapRight = 0;
		if (x < 0)
		{
			CropX = (SrcWidth - DestWidth) / 2;
		}
		else
		{
			x = x & ~0x1;
			if (x + DestWidth > SrcWidth)
			{
				x = SrcWidth - DestWidth;
			}
			CropX = x;
		}
		CropX &= ~0x1;
		RealCopyWidth = DestWidth;
	}

	if (SrcHeight <= DestHeight)
	{
		CropY = 0;
		if (y < 0)
		{
			GapTop = (DestHeight - SrcHeight) / 2;
		}
		else
		{
			y &= ~0x1;
			if (y + SrcHeight > DestHeight)
			{
				y = DestHeight - SrcHeight;
			}
			GapTop = y;
		}
		GapTop &= ~0x1;
		RealCopyHeight = SrcHeight;
		GapBottom = DestHeight - RealCopyHeight - GapTop;
	}
	else
	{
		GapTop = GapBottom = 0;
		if (y < 0)
		{
			CropY = (SrcHeight - DestHeight) / 2;
		}
		else
		{
			y = y & ~0x1;
			if (y + DestHeight > SrcHeight)
			{
				y = SrcHeight - DestHeight;
			}
			CropY = y;
		}
		CropY &= ~0x1;
		RealCopyHeight = DestHeight;
	}

	pSrcY = pSrc;
	pSrcUV = pSrc + SrcWidth * SrcHeight;
	pDestY = pDest;
	pDestUV = pDest + DestWidth * DestHeight;
	for (i = 0; i < GapTop; i += 2)
	{
		memset(pDestY + i*DestWidth, 0, DestWidth);
		memset(pDestY + (i + 1)*DestWidth, 0, DestWidth);
		memset(pDestUV + (i / 2)*DestWidth, 128, DestWidth);
	}

	for (i = 0; i < RealCopyHeight; i += 2)
	{
		if (Gapleft)
		{
			memset(pDestY + (i + GapTop)*DestWidth, 0, Gapleft);
			memset(pDestY + ((i + GapTop) + 1)*DestWidth, 0, Gapleft);
			memset(pDestUV + ((i + GapTop) / 2)*DestWidth, 128, Gapleft);
		}

		memcpy(pDestY + (i + GapTop)*DestWidth + Gapleft, pSrcY + (CropY + i)*SrcWidth + CropX, RealCopyWidth);
		memcpy(pDestY + ((i + GapTop) + 1)*DestWidth + Gapleft, pSrcY + (CropY + i + 1)*SrcWidth + CropX, RealCopyWidth);
		memcpy(pDestUV + ((i + GapTop) / 2)*DestWidth + Gapleft, pSrcUV + ((CropY + i) / 2)*SrcWidth + CropX, RealCopyWidth);

		if (GapRight)
		{
			memset(pDestY + (i + GapTop)*DestWidth + Gapleft + RealCopyWidth, 0, GapRight);
			memset(pDestY + ((i + GapTop) + 1)*DestWidth + Gapleft + RealCopyWidth, 0, GapRight);
			memset(pDestUV + ((i + GapTop) / 2)*DestWidth + Gapleft + RealCopyWidth, 128, GapRight);
		}
	}

	for (i = 0; i < GapBottom; i += 2)
	{
		memset(pDestY + (i + GapTop + RealCopyHeight)*DestWidth, 0, DestWidth);
		memset(pDestY + ((i + GapTop + RealCopyHeight) + 1)*DestWidth, 0, DestWidth);
		memset(pDestUV + ((i + GapTop + RealCopyHeight) / 2)*DestWidth, 128, DestWidth);
	}

	return 0;
}

int Yuv422SPToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch)
{
	unsigned int i, j;

	for (i = 0; i < height; ++i)
	{
		memcpy(pDest + i*pitch, pSrc + i*width, width);
	}

	unsigned char *pDestU, *pDestV, *pSrcUV;
	pSrcUV = pSrc + width * height;
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
		pSrcUV += width * 2;
	}

	return 0;
}

int Yuv420SPToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch)
{
	unsigned int i, j;

	for (i = 0; i < height; ++i)
	{
		memcpy(pDest + i*pitch, pSrc + i*width, width);
	}

	unsigned char *pDestU, *pDestV, *pSrcUV;
	pSrcUV = pSrc + width * height;
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


int Yuv444ToYV12(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height, int pitch)
{
	unsigned int i, j;

	unsigned char *pDestY, *pDestU, *pDestV, *pSrcYUV;
	pSrcYUV = pSrc;
	pDestY = pDest;
	pDestV = pDest + pitch * height;
	pDestU = pDest + pitch * height + (pitch / 2) * (height / 2);

	for (i = 0; i < height; i += 1)
	{
		for (j = 0; j < width; j += 1)
		{
			if ((i & 1) == 0 && (j & 1) == 0)
			{
				pDestU[j / 2] = pSrcYUV[j * 3 + 1];
				pDestV[j / 2] = pSrcYUV[j * 3 + 0];
			}
			pDestY[j] = pSrcYUV[j * 3 + 2];
		}
		pDestY += pitch;
		if ((i & 1) == 0)
		{
			pDestU += pitch / 2;
			pDestV += pitch / 2;
		}
		pSrcYUV += width * 3;
	}

	return 0;
}

unsigned char tableYUV2RGB[256][256][256][3];
#define clip0_255(x) ((x)>255?255:(x)<0?0:(x))
void yuv2rgb_init()
{
	int y, u, v;
	int r, g, b;

	for (y = 0; y < 256; ++y)
	{
		for (u = 0; u < 256; ++u)
		{
			for (v = 0; v < 256; ++v)
			{
				r = (int)(y + 1.402 * (v - 128));
				g = (int)(y - 0.34413 * (u - 128) - 0.71414 * (v - 128));
				b = (int)(y + 1.772 * (u - 128));
				tableYUV2RGB[y][u][v][0] = clip0_255(r);
				tableYUV2RGB[y][u][v][1] = clip0_255(g);
				tableYUV2RGB[y][u][v][2] = clip0_255(b);
			}
		}
	}
}

int Yuv422SPToRgb24(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height)
{
	int y1, y2, u, v;
	unsigned char *pY, *pUV;
	unsigned int i, j;
	unsigned char *pRGB;

	pY = pSrc;
	pUV = pSrc + width*height;
	pRGB = pDest;
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i += 2)
		{
			y1 = pY[0];
			y2 = pY[1];
			u = pUV[0];
			v = pUV[1];

			pRGB[0] = tableYUV2RGB[y1][u][v][2];
			pRGB[1] = tableYUV2RGB[y1][u][v][1];
			pRGB[2] = tableYUV2RGB[y1][u][v][0];

			pRGB[3] = tableYUV2RGB[y2][u][v][2];
			pRGB[4] = tableYUV2RGB[y2][u][v][1];
			pRGB[5] = tableYUV2RGB[y2][u][v][0];

			pY += 2;
			pUV += 2;
			pRGB += 6;
		}

	}

	return 0;
}

int Yuv420SPToRgb24(unsigned char * pSrc, unsigned char * pDest, unsigned int width, unsigned int height)
{
	int y1, y2, u, v;
	unsigned char *pY, *pUV;
	unsigned int i, j;
	unsigned char *pRGB;

	pY = pSrc;
	pUV = pSrc + width*height;
	pRGB = pDest;
	for (j = 0; j < height; j++)
	{
		if (j % 2) pUV -= width;

		for (i = 0; i < width; i += 2)
		{
			y1 = pY[0];
			y2 = pY[1];
			u = pUV[0];
			v = pUV[1];

			pRGB[0] = tableYUV2RGB[y1][u][v][2];
			pRGB[1] = tableYUV2RGB[y1][u][v][1];
			pRGB[2] = tableYUV2RGB[y1][u][v][0];

			pRGB[3] = tableYUV2RGB[y2][u][v][2];
			pRGB[4] = tableYUV2RGB[y2][u][v][1];
			pRGB[5] = tableYUV2RGB[y2][u][v][0];

			pY += 2;
			pUV += 2;
			pRGB += 6;
		}
	}
	return 0;
}
/*
int WriteRgb24ToBmpFile(unsigned char * pData, unsigned int nWidth, unsigned int nHeight, char *pFilePath)
{
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpif;
	FILE *pFile = NULL;

	memset(&bmpfh, 0, sizeof(bmpfh));
	bmpfh.bfType = MAKEWORD('B', 'M');
	bmpfh.bfSize = sizeof(bmpfh) + sizeof(bmpif) + nWidth*nHeight * 3;
	bmpfh.bfOffBits = sizeof(bmpfh) + sizeof(bmpif);


	memset(&bmpif, 0, sizeof(bmpif));
	bmpif.biSize = sizeof(bmpif);
	bmpif.biWidth = nWidth;
	bmpif.biHeight = -(int)(nHeight);
	bmpif.biPlanes = 1;
	bmpif.biBitCount = 24;

	fopen_s(&pFile, pFilePath, "wb");
	if (NULL != pFile)
	{
		fwrite(&bmpfh, 1, sizeof(bmpfh), pFile);
		fwrite(&bmpif, 1, sizeof(bmpif), pFile);
		fwrite((void*)pData, 1, nWidth*nHeight * 3, pFile);
		fclose(pFile);
	}

	return 0;
}
*/
int RawToRgb24(unsigned char * pSrc, unsigned int RawFormat, unsigned char * pDest, unsigned int width, unsigned int height)
{
	unsigned int i, j;
	unsigned char r, gb, gr, b;

	for (i = 0; i < height; i += 2)
	{
		for (j = 0; j < width; j += 2)
		{
			switch (RawFormat)
			{
			case RAW_GBRG:
			{
				gb = pSrc[(i + 0)*width + j + 0];
				b = pSrc[(i + 0)*width + j + 1];
				r = pSrc[(i + 1)*width + j + 0];
				gr = pSrc[(i + 1)*width + j + 1];

				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 1] = gb;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 1] = pSrc[(i + 0)*width + j + 2];
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 2] = pSrc[(i + 1)*width + j + 2];

				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 0] = pSrc[(i + 2)*width + j + 1];
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 1] = gr;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 0] = pSrc[(i + 2)*width + j + 1];
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 1] = gr;
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 2] = pSrc[(i + 1)*width + j + 2];
			}
			break;
			case RAW_BGGR:
			{
				b = pSrc[(i + 0)*width + j + 0];
				gb = pSrc[(i + 0)*width + j + 1];
				gr = pSrc[(i + 1)*width + j + 0];
				r = pSrc[(i + 1)*width + j + 1];

				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 1] = gb;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 0] = pSrc[(i + 0)*width + j + 2];
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 1] = gb;
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 2] = r;

				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 0] = pSrc[(i + 2)*width + j + 0];
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 1] = gr;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 0] = pSrc[(i + 2)*width + j + 2];
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 1] = pSrc[(i + 1)*width + j + 2];
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 2] = r;
			}
			break;
			case RAW_GRBG:
			{
				gr = pSrc[(i + 0)*width + j + 0];
				r = pSrc[(i + 0)*width + j + 1];
				b = pSrc[(i + 1)*width + j + 0];
				gb = pSrc[(i + 1)*width + j + 1];

				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 1] = gr;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 0] = pSrc[(i + 1)*width + j + 2];
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 1] = pSrc[(i + 0)*width + j + 2];
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 2] = r;

				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 1] = gb;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 2] = pSrc[(i + 2)*width + j + 1];

				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 0] = pSrc[(i + 1)*width + j + 2];
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 1] = gb;
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 2] = pSrc[(i + 2)*width + j + 1];
			}
			break;
			case RAW_RGGB:
			{
				r = pSrc[(i + 0)*width + j + 0];
				gr = pSrc[(i + 0)*width + j + 1];
				gb = pSrc[(i + 1)*width + j + 0];
				b = pSrc[(i + 1)*width + j + 1];

				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 1] = gr;
				pDest[(i + 0)*width * 3 + (j + 0) * 3 + 2] = r;

				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 0] = b;
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 1] = gr;
				pDest[(i + 0)*width * 3 + (j + 1) * 3 + 2] = pSrc[(i + 0)*width + j + 2];

				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 0] = b;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 1] = gb;
				pDest[(i + 1)*width * 3 + (j + 0) * 3 + 2] = pSrc[(i + 2)*width + j + 0];

				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 0] = b;
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 1] = pSrc[(i + 1)*width + j + 2];
				pDest[(i + 1)*width * 3 + (j + 1) * 3 + 2] = pSrc[(i + 2)*width + j + 2];
			}
			break;
			default:
				break;
			}
		}
	}

	return 0;
}
/*
static BOOL bPaletteInit = FALSE;
static RGBQUAD rgbPalette[256] = { 0 };
int WriteMonoToBmpFile(unsigned char * pData, unsigned int nWidth, unsigned int nHeight, char *pFilePath)
{
	BITMAPFILEHEADER bmpfh;
	BITMAPINFOHEADER bmpif;
	FILE *pFile = NULL;

	if (!bPaletteInit)
	{
		for (int i = 0; i < 256; i++)
		{
			rgbPalette[i].rgbBlue = i;
			rgbPalette[i].rgbGreen = i;
			rgbPalette[i].rgbRed = i;
			rgbPalette[i].rgbReserved = 0;
		}
		bPaletteInit = TRUE;
	}

	memset(&bmpfh, 0, sizeof(bmpfh));
	bmpfh.bfType = MAKEWORD('B', 'M');
	bmpfh.bfSize = sizeof(bmpfh) + sizeof(bmpif) + nWidth*nHeight;
	bmpfh.bfOffBits = sizeof(bmpfh) + sizeof(bmpif);


	memset(&bmpif, 0, sizeof(bmpif));
	bmpif.biSize = sizeof(bmpif);
	bmpif.biWidth = nWidth;
	bmpif.biHeight = -(int)(nHeight);
	bmpif.biPlanes = 1;
	bmpif.biBitCount = 8;
	bmpif.biClrImportant = BI_RGB;

	fopen_s(&pFile, pFilePath, "wb");
	if (NULL != pFile)
	{
		fwrite(&bmpfh, 1, sizeof(bmpfh), pFile);
		fwrite(&bmpif, 1, sizeof(bmpif), pFile);
		fwrite(rgbPalette, 1, 256 * sizeof(RGBQUAD), pFile);
		fwrite((void*)pData, 1, nWidth*nHeight, pFile);
		fclose(pFile);
	}

	return 0;

}
*/

