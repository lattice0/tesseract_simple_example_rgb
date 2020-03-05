#ifndef IMAGE_STREAM_RGB_H
#define IMAGE_STREAM_RGB_H
#include <functional>
#include <memory>
#include "SimpleBuffer.h"
void imageStreamRGBThread(std::function<void(std::unique_ptr<SimpleRoseekBuffer>, int, int)> rgbUpdateCallback);
#endif //IMAGE_STREAM_RGB_H
