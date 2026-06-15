import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia
import com.barcodescanner 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: "Barcode Scanner"

    AppController {
            id: appController
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            CaptureSession {
                camera: Camera {
                    id: camera
                    active: true
                    focusMode: Camera.FocusModeAutoNear
                    customFocusPoint: Qt.point(0.2, 0.2)
                }
                videoOutput: videoOutput
            }

            VideoOutput {
                id: videoOutput
                anchors.fill: parent

                Component.onCompleted: {
                    appController.videoManager.videoSink = videoOutput.videoSink
                }
            }
        }


        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: "#f0f0f0"
            radius: 10
            border.color: "lightgrey"
            border.width: 1

            Text {
                id: barcodeText
                anchors.fill: parent
                anchors.margins: 5
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 18
                text: appController.barcodeDecoder.lastResult
                color: "dimgrey"
                wrapMode: Text.WordWrap
            }
        }
    }
}
