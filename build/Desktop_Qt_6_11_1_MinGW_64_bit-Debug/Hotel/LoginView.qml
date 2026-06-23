import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

    Rectangle {
        color: "#0f172a"

        function enterLogin () {
            var cleanUsername = usernameField.text.trim();
            var cleanPassword = passwordField.text.trim();
            if (usernameField.text === "" || passwordField.text === "") {
                HotelApp.notify("Harap isi semua kolom!", true);
                return;
            }
            if (HotelApp.login(cleanUsername, cleanPassword))
                mainStack.replace(HotelApp.currentUserRole === "ADMIN" ? "AdminDashboard.qml" : "UserDashboard.qml");
        }

        Rectangle {
            width: 450
            height: 520
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
                    Layout.preferredHeight: 120
                    Layout.preferredWidth: 90
                    Layout.alignment: Qt.AlignHCenter
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
                    placeholderText: "Username"
                    Layout.fillWidth: true
                    font.pixelSize: 15
                    topPadding: 12
                    bottomPadding: 12
                    leftPadding: 15
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
                    placeholderText: "Password"
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    font.pixelSize: 15
                    topPadding: 12
                    leftPadding: 15
                    color: "#1e293b"
                    background: Rectangle {
                        color: "#f8fafc"
                        border.color: passwordField.activeFocus ? "#C5A059" : "#e2e8f0"
                        border.width: 1
                        radius: 8
                    }
                    onAccepted: enterLogin()
                }

                ColumnLayout {
                    width: parent.width
                    spacing: 6;


                    Button {
                        id: goToRegisterBtn
                        text: "BELUM PUNYA AKUN? DAFTAR"
                        Layout.fillWidth: true

                        contentItem: Text {
                            text: parent.text
                            color: parent.hovered ? "#C5A059" : "#64748b"
                            font.bold: true
                            font.pixelSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle { color: "transparent" }

                        onClicked: {
                            mainStack.push("RegisterView.qml")
                        }
                    }

                    Button {
                        id : loginButton
                        text: "LOGIN"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50

                        contentItem: Text {
                            text: loginButton.text
                            color: "white"
                            font.bold: true
                            font.letterSpacing: 1
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            color: loginButton.down ? "#A6864B" :
                                   (loginButton.hovered ? "#D4AF37" : "#C5A059")
                            radius: 8
                        }

                        onClicked: {
                            // [Kriteria: Validasi form]
                            enterLogin()
                        }
                    }

                    Button {
                        id: backButton
                        text: "BACK TO HOME"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50

                        contentItem: Text {
                            text: backButton.text
                            color: backButton.hovered ? "#1e293b" : "#64748b"
                            font.bold: false
                            font.pixelSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            mainStack.pop()
                        }
                    }
                }
            }
        }
    }