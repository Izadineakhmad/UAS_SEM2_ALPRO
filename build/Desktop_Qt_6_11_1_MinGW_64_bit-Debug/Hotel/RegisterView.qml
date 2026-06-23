import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle {
    id: registerRoot
    color: "#0f172a"

    function enterRegister() {
        var cleanNama = nameField.text.trim();
        var cleanUsername = usernameField.text.trim();
        var cleanPassword = passwordField.text.trim();

        if (cleanNama === "" || cleanUsername === "" || cleanPassword === "") {
            HotelApp.notify("Harap isi semua kolom!", true);
            return;
        }

        // Panggil C++ dengan parameter nama
        if (HotelApp.registerUser(cleanNama, cleanUsername, cleanPassword)) {
            HotelApp.notify("Registrasi berhasil! Menunggu konfirmasi.", false);
            mainStack.pop();
        }
    }

    Rectangle {
        width: 450
        height: 600
        anchors.centerIn: parent
        radius: 15
        color: "#ffffff"
        border.color: "#e2e8f0"
        border.width: 1
        clip: true

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20
            width: parent.width * 0.8

            Image {
                source: "images/logovertical.png"
                Layout.preferredHeight: 100
                Layout.preferredWidth: 80
                Layout.alignment: Qt.AlignHCenter
                fillMode: Image.PreserveAspectFit
            }

            Text {
                text: "CREATE ACCOUNT"
                font.pixelSize: 22
                font.bold: true
                color: "#1e293b"
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                text: "Daftar untuk mulai memesan kamar"
                font.pixelSize: 13
                color: "#7f8c8d"
                Layout.alignment: Qt.AlignHCenter
                Layout.bottomMargin: 15
            }

            TextField {
                id: nameField
                placeholderText: "Nama Lengkap"
                Layout.fillWidth: true
                font.pixelSize: 15
                topPadding: 12; bottomPadding: 12; leftPadding: 15
                background: Rectangle { color: "#f8fafc"; border.color: "#e2e8f0"; radius: 8 }
            }

            TextField {
                id: usernameField
                placeholderText: "Buat Username"
                Layout.fillWidth: true
                font.pixelSize: 15
                topPadding: 12; bottomPadding: 12; leftPadding: 15
                color: "#1e293b"
                background: Rectangle {
                    color: "#f8fafc"
                    border.color: usernameField.activeFocus ? "#C5A059" : "#e2e8f0"
                    border.width: 1
                    radius: 8
                }
                onAccepted: passwordField.forceActiveFocus()
            }

            TextField {
                id: passwordField
                placeholderText: "Buat Password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                font.pixelSize: 15
                topPadding: 12; bottomPadding: 12; leftPadding: 15
                color: "#1e293b"
                background: Rectangle {
                    color: "#f8fafc"
                    border.color: passwordField.activeFocus ? "#C5A059" : "#e2e8f0"
                    border.width: 1
                    radius: 8
                }
                onAccepted: enterRegister()
            }

            Item { height: 10; Layout.fillWidth: true }

            ColumnLayout {
                width: parent.width
                spacing: 12

                Button {
                    id: registerBtn
                    text: "REGISTER"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50

                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        font.bold: true
                        font.letterSpacing: 1
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        color: registerBtn.down ? "#A6864B" : (registerBtn.hovered ? "#D4AF37" : "#C5A059")
                        radius: 8
                    }
                    onClicked: enterRegister()
                }

                Button {
                    id: backToLoginBtn
                    text: "SUDAH PUNYA AKUN? LOGIN"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50

                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "#1e293b" : "#64748b"
                        font.bold: true
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle { color: "transparent" }
                    onClicked: mainStack.pop()
                }
            }
        }
    }
}