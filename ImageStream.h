#ifndef IMAGE_STREAM_H
#define IMAGE_STREAM_H
#include <functional>
#include <memory>
#include "SimpleBuffer.h"
//TODO: change void *pParam to MainContext_t*
void imageStreamThread(void *pParam, std::function<void(std::unique_ptr<SimpleRoseekBuffer>, int, int)> rgbUpdateCallback);

#endif //IMAGE_STREAM_H
