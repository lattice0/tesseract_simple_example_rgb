#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H
#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CameraView)

public:
    CameraView(QQuickItem* parent = nullptr);
    void updateImage(const QImage&);
public slots:
    
    void paint(QPainter *painter) override;

protected:
    std::shared_ptr<QImage> qImage;
};

#endif //CAMERA_VIEW_H
