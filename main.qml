import QtQuick 2.12
import QtQuick.Window 2.12
import com.lucaszanella.camera_view 1.0

Window {
    objectName: "mainWindow"
    visible: true
    width: 640
    height: 480
    title: qsTr("Leuze OCR")
    CameraView{
        width: 640
        height: 480
        objectName: "cameraView"
    }
}
