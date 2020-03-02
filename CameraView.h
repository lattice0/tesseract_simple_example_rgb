#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <memory>
#include <mutex>
#include "SimpleBuffer.h"
class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CameraView)

public:
    CameraView(QQuickItem* parent = nullptr) {

    }
    void updateImage(std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer, int width, int height, QImage::Format);
public slots:
    void paint(QPainter *painter) override;

protected:
    std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer;
    QImage qImage;
    std::mutex qImageMutex;
};

#endif //CAMERA_VIEW_H
