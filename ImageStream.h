#ifndef IMAGE_STREAM_H
#define IMAGE_STREAM_H
#include <functional>
//TODO: change void *pParam to MainContext_t*
void imageStreamThread(void *pParam, std::function<void(uint8_t*, int, int)> rgbUpdateCallback);

#endif //IMAGE_STREAM_H
