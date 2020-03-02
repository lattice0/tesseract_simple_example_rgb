#ifndef _RS_JPEG_UTIL_H_
#define _RS_JPEG_UTIL_H_

#if __GNUC__ >= 4
#define RSJPEGUTIL_API __attribute__ ((visibility("default")))
#else
#define RSJPEGUTIL_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

	enum LJ_YUV_TYPE
	{
		LJ_UNKNOWN,
		LJ_YUV420P,
		LJ_YUV422P,
		LJ_YUV444P
	};

RSJPEGUTIL_API void* Roseek_JpegEncoder_Create();
RSJPEGUTIL_API void Roseek_JpegEncoder_Destroy(void* handle);
RSJPEGUTIL_API int Roseek_JpegEncoder_EncodeRGB(void* handle
						, unsigned char * p_src, int width, int height, int quality
						, unsigned char * p_dest, long * p_dest_size);
RSJPEGUTIL_API int Roseek_JpegEncoder_EncodeYUV(void * handle
						, unsigned char * p_src_y, unsigned char * p_src_u, unsigned char * p_src_v
						, int width, int height, int fmt, int quality
						, unsigned char * p_dest, long * p_dest_size);

RSJPEGUTIL_API void * Roseek_JpegDecoder_Create();
RSJPEGUTIL_API void Roseek_JpegDecoder_Destroy(void * handle);
RSJPEGUTIL_API int Roseek_JpegDecoder_DecodeToRGB(void * handle
						, unsigned char * p_src, long src_size
						, unsigned char * p_dest, long dest_size
						, int * p_width, int * p_height);
RSJPEGUTIL_API int Roseek_JpegDecoder_DecodeToYUV(void * handle
						, unsigned char * p_src, long src_size
						, unsigned char * p_dest, long dest_size
						, int * p_width, int * p_height, int * p_fmt);

#ifdef __cplusplus
};
#endif

#endif