import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

    Rectangle {
        color: "#2c3e50"
        Rectangle {
            width: 450; height: 500
            anchors.centerIn: parent
            radius: 15
            color: "white"

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 25
                width: parent.width * 0.8

                Text {
                    text: "Hotel Management"
                    font.pixelSize: 28
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    color: "#2c3e50"
                }
                Text {
                    text: "Login untuk melanjutkan"
                    font.pixelSize: 14
                    color: "#7f8c8d"
                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: 20
                }

                TextField {
                    id: usernameField
                    placeholderText: "Username (admin / budi)"
                    Layout.fillWidth: true
                    font.pixelSize: 16
                }
                TextField {
                    id: passwordField
                    placeholderText: "Password (admin / user)"
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    font.pixelSize: 16
                }

                Button {
                    id : loginButton
                    text: "MASUK"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    palette.buttonText: "White"
                    background: Rectangle {
                        color: parent.down ? "#2980b9" : "#3498db";
                        radius: 8
                    }
                    contentItem: Text {
                        text: loginButton.text // Ambil text dari button
                        color: "white"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: {
                        // [Kriteria: Validasi form]
                        if(usernameField.text === "" || passwordField.text === "") {
                            HotelApp.notify("Harap isi semua kolom!", true); return;
                        }
                        if (HotelApp.login(usernameField.text, passwordField.text)) {
                            mainStack.replace(HotelApp.currentUserRole === "ADMIN" ? "AdminDashboard.qml" : "UserDashboard.qml");
                        }
                    }
                }
            }
        }
    }