#include "CameraView.h"


void CameraView::updateImage(std::shared_ptr<QImage> qImage)
{
    std::unique_lock<std::mutex> lk{qImageMutex};
    this->qImage= qImage;
    //update();
}

void CameraView::paint(QPainter* painter)
{
    std::unique_lock<std::mutex> lk{qImageMutex};
    painter->drawImage(this->boundingRect(), *qImage);
}
