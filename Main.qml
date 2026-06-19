import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    minimumWidth: 1280
    minimumHeight: 720
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    title: "Sistem Manajemen Hotel - UAS OOP"
    color: "#f4f6f9"

    // [Kriteria: Notifikasi berhasil/gagal]
    Popup {
        id: notificationPopup
        y: 20
        x: (parent.width - width) / 2
        width: 500
        height: 50
        modal: false
        closePolicy: Popup.CloseOnEscape

        property alias message: msgText.text
        property bool isError: false

        background: Rectangle {
            color: notificationPopup.isError ? "#e74c3c" : "#2ecc71"
            radius: 8
            opacity: 0.95
        }
        Text {
            id: msgText
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 16
            font.bold: true
        }
        Timer {
            id: hideTimer
            interval: 3000
            onTriggered: notificationPopup.close()
        }
        onOpened: hideTimer.start()
    }

    Connections {
        target: HotelApp
        function onNotify(message, isError) {
            notificationPopup.message = message;
            notificationPopup.isError = isError;
            notificationPopup.open();
        }
    }

    StackView {
        id: mainStack
        anchors.fill: parent
        initialItem: "LoginView.qml"
    }

}