#include "CameraView.h"

void CameraView::updateImage(std::shared_ptr<QImage> qImage)
{
    this->qImage= qImage; // does shallow copy of image data
    update();             // triggers actual update
}

void CameraView::paint(QPainter* painter)
{
    painter->drawImage(this->boundingRect(), *qImage);
}
