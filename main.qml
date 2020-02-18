import QtQuick 2.12
import QtQuick.Window 2.12
import com.lucaszanella.camera_view 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Leuze OCR")
    CameraView{
        id: cameraView
    }
}
