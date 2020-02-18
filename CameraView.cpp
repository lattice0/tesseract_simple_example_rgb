#include "CameraView.h"


void CameraView::updateImage(std::shared_ptr<QImage> qImage)
{
    this->qImage= qImage;
    update();
}

void CameraView::paint(QPainter* painter)
{
    painter->drawImage(this->boundingRect(), *qImage);
}
