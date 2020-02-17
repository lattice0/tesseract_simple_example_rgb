#ifndef CAMERA_VIEW_THREAD_H
#define CAMERA_VIEW_THREAD_H

class CameraViewThread 
{
    void updateImage(const QImage& image);
    void paint(QPainter* painter);
};

#endif //CAMERA_VIEW_THREAD_H