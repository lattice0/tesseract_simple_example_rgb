#include "CameraView.h"
#include <iostream>

void CameraView::updateImage(std::shared_ptr<QImage> qImage)
{
    std::unique_lock<std::mutex> lk{qImageMutex};
    this->qImage= qImage;
    //update();
}

void CameraView::paint(QPainter* painter)
{
    std::cout << "gonna paint" << std::endl;
    std::unique_lock<std::mutex> lk{qImageMutex};
    //Qt can call update rigth at the beggining when there's no image setted
    if (qImage) {
        painter->drawImage(this->boundingRect(), *qImage);
    }
    std::cout << "painted" << std::endl;
}
