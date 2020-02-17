#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CameraView)

public:
    CameraView(QQuickItem* parent = nullptr);

public slots:
    void updateImage(const QImage&);

protected:
    QImage m_image;
};

#endif //CAMERA_VIEW_H