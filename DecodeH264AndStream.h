#ifndef DECODEH264_AND_STREAM_H
#define DECODEH264_AND_STREAM_H


static int Yuv420SPToYV12(unsigned char * pSrcY, unsigned char * pSrcUV, unsigned char * pDest, unsigned int width, unsigned int height, int pitch);
static int KFDecodeH264AndStream();
int decoder_thread();

#endif //DECODEH264_AND_STREAM_H