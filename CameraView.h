#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H
#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include <memory>
#include <mutex>
class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CameraView)

public:
    CameraView(QQuickItem* parent = nullptr) {

    }
    void updateImage(std::shared_ptr<QImage> qImage);
public slots:
    void paint(QPainter *painter) override;

protected:
    std::shared_ptr<QImage> qImage;
    std::mutex qImageMutex;
};

#endif //CAMERA_VIEW_H
