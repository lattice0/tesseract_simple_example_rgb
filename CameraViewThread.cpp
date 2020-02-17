#include "CameraViewThread.h"

CameraViewThread::CameraViewThread()
{
    this->moveToThread(&m_workerThread);
    // the below will allow communication between threads
    connect(this, SIGNAL(signalUiUpdate(QImage)), m_cameraView, SLOT(updateImage(QImage)));

    m_workerThread.start();
}

void CameraViewThread::cvRead()
{
     QImage image;

     // OpenCV details available in your code
     // cv::read
     // make QImage from frame


     // deliver QImage to another thread
     emit signalUiUpdate(image);
}