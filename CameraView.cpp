#include "CameraView.h"
#include <iostream>
#include <memory>
#include "SimpleBuffer.h"

void CameraView::updateImage(std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer, int width, int height, QImage::Format format)
{
    std::unique_lock<std::mutex> lk{qImageMutex};
    //Holds buffer too so it automatially deletes it when the buffer is replaced by another
    this->qImage = QImage(simpleRoseekBuffer->data(), width, height, format);
    this->simpleRoseekBuffer= std::move(simpleRoseekBuffer);
}

void CameraView::paint(QPainter* painter)
{
    std::cout << "gonna paint" << std::endl;
    std::unique_lock<std::mutex> lk{qImageMutex};
    //Qt can call update rigth at the beggining when there's no image setted

    if (simpleRoseekBuffer) {
        painter->drawImage(this->boundingRect(), qImage);
    }
    std::cout << "painted" << std::endl;
}
