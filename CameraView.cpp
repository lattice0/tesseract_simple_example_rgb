#include "CameraView.h"

void CameraView::updateImage(const QImage& image)
{
    m_imageThumb = image; // does shallow copy of image data
    update();             // triggers actual update
}

void CameraView::paint(QPainter* painter)
{
    painter->drawImage(this->boundingRect(), m_image);
}