#ifndef _ROSEEK_CIRCULAR_QUEUE_H_
#define _ROSEEK_CIRCULAR_QUEUE_H_

#if __GNUC__ >= 4
#define CTMAINCORE_API __attribute__ ((visibility("default")))
#else
#define CTMAINCORE_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CQ_SUCCESS              0
#define CQ_ERR_INVALIDPARAM     -1
#define CQ_ERR_OVERFLOW         -2
#define CQ_ERR_OUTOFMEM         -3
#define CQ_ERR_NOITEM           -4

CTMAINCORE_API void * Roseek_CQ_CreateOne(int ItemSize, int InitItemCount, int AutoIncrease);
CTMAINCORE_API int Roseek_CQ_CloseOne(void * Handle);
CTMAINCORE_API int Roseek_CQ_Capacity(void * Handle);
CTMAINCORE_API int Roseek_CQ_IncreaseCapacity(void * Handle);
CTMAINCORE_API int Roseek_CQ_Count(void * Handle);
CTMAINCORE_API int Roseek_CQ_IsEmpty(void * Handle);
CTMAINCORE_API int Roseek_CQ_IsFull(void * Handle);
CTMAINCORE_API int Roseek_CQ_Clear(void * Handle);
CTMAINCORE_API int Roseek_CQ_PushBack(void * Handle, void * pItem);
CTMAINCORE_API int Roseek_CQ_PopFront(void * Handle, void * pItem);
CTMAINCORE_API int Roseek_CQ_Front(void * Handle, void * pItem);

#ifdef __cplusplus
};
#endif

#endif
