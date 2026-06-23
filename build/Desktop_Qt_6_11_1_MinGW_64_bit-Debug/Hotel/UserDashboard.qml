import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import "./components/QDatePicker/src"

Item {
    id: userDashboard

    property string tempCheckInStr: ""
    property string tempCheckOutStr: ""

    RowLayout {
        spacing: 0
        anchors.fill: parent

        Component.onCompleted: {
            userStack.currentIndex = 0;
        }

        // --- SIDEBAR ---
        Rectangle {
            Layout.preferredWidth: 260;
            Layout.fillHeight: true;
            color: "white"
            ColumnLayout {
                anchors.fill: parent;
                anchors.margins: 20;
                spacing: 20
                Image {
                    source: "images/logonotext.png"
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredHeight: 75
                    Layout.preferredWidth: 75
                }

                Text {
                    text: "Halo, " + HotelApp.currentUserName;
                    Layout.alignment: Qt.AlignHCenter
                    color: "#C5A059";
                    font.pixelSize: 22;
                    font.bold: true;
                }
                Button {
                    text: "● Dashboard Booking"
                    Layout.fillWidth: true;

                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "#D4AF37" : "#C5A059"
                        font.pixelSize: 19
                    }

                    onClicked: {
                        userStack.currentIndex = 0;
                    }

                    background: Rectangle {
                        color: "transparent"
                    }
                }
                Button {
                    id: riwayatBtn
                    text: "● Riwayat Transaksi"
                    Layout.fillWidth: true;
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "#D4AF37" : "#C5A059"
                        font.pixelSize: 19
                    }
                    onClicked: {
                        userStack.currentIndex = 1;
                        loadUserTx()
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
                Item { Layout.fillHeight: true }
                Button {
                    text: "LOGOUT";
                    Layout.fillWidth: true
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        font.bold: true
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    background : Rectangle { color: parent.down ? "#333333" : "#0f172a"; radius: 6 }
                    onClicked: {
                        HotelApp.logout();
                        mainStack.replace("LoginView.qml")
                    }

                }
            }
        }

        // --- MAIN CONTENT AREA ---
        StackLayout {
            id: userStack
            Layout.fillWidth: true; Layout.fillHeight: true
            currentIndex: 0

            // PAGE 0: HOTEL BOOKING DASHBOARD (Sesuai Desain PDF)
            Rectangle {
                color: "#f4f6f9"

                ScrollView {
                    anchors.fill: parent
                    contentWidth: availableWidth
                    clip: true

                    ColumnLayout {
                        width: parent.width * 0.9
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 30
                        Item { height: 20 } // Top margin

                        // 1. KOTAK FORM BOOKING (Bagian Atas)
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 380
                            color: "white"
                            radius: 12
                            border.color: "#e2e8f0"

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 30
                                spacing: 12

                                Image {
                                    source: "images/logo.png"
                                    Layout.preferredWidth: 200
                                    Layout.preferredHeight: 52
                                    Layout.alignment: Qt.AlignHCenter
                                    Layout.bottomMargin: 10
                                }

                                // Baris 1: Tanggal
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 20

                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        Text { text: "Check-in Date"; color: "#7f8c8d"; font.pixelSize: 13 }
                                        DatePicker {
                                            id: checkInPicker
                                            placeholderText: "mm/dd/yyyy"
                                            locale: "en-US"
                                            width: 300
                                            Layout.fillWidth: true
                                            height: 40
                                            minDate: new Date()
                                            primaryColor: "Teal"
                                            calendar: "Gregorian"
                                            mainWindow: appWindow
                                            onSelectedDateChanged: {
                                                if (selectedDate) {
                                                    userDashboard.tempCheckInStr = Qt.formatDate(selectedDate, "yyyy-MM-dd")
                                                }
                                            }
                                        }
                                    }

                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        Text { text: "Check-out Date"; color: "#7f8c8d"; font.pixelSize: 13 }
                                        DatePicker {
                                            id: checkOutPicker
                                            placeholderText: "mm/dd/yyyy"
                                            locale: "en-US"
                                            calendar: "Gregorian"
                                            width: 300
                                            Layout.fillWidth: true
                                            height: 40
                                            minDate : {
                                                var result = new Date();
                                                result.setDate(result.getDate() + 1);
                                                return result;
                                            }
                                            primaryColor: "Teal"
                                            mainWindow: appWindow
                                            onSelectedDateChanged: {
                                                if (selectedDate) {
                                                    userDashboard.tempCheckOutStr = Qt.formatDate(selectedDate, "yyyy-MM-dd")
                                                }
                                            }
                                        }
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    Text {
                                        text: "Room Type";
                                        color: "#7f8c8d";
                                        font.pixelSize: 13
                                    }
                                    ComboBox {
                                        id: roomTypeCombo
                                        model: ["Standard", "Suite", "Deluxe"]
                                        Layout.fillWidth: true
                                        padding: 10
                                        font.pixelSize: 15
                                        background: Rectangle {
                                            color: "white"
                                            border.color: "#e2e8f0"
                                            border.width: 1
                                            radius: 5
                                        }
                                        delegate: ItemDelegate {
                                            width: roomTypeCombo.width
                                            text: modelData
                                            highlighted: roomTypeCombo.highlightedIndex === index

                                            contentItem: Text {
                                                text: parent.text
                                                font: roomTypeCombo.font
                                                color: parent.highlighted ? "#ffffff" : "#2c3e50"
                                                verticalAlignment: Text.AlignVCenter
                                            }

                                            background: Rectangle {
                                                color: parent.highlighted ? "#2196F3" : "white"
                                            }
                                        }
                                    }
                                }

                                // Tombol Book Now (Hitam elegan seperti PDF)
                                Button {
                                    text: "Book Now"
                                    Layout.fillWidth: true
                                    Layout.topMargin: 20
                                    Layout.preferredHeight: 50
                                    background: Rectangle { color: parent.down ? "#333333" : "#0f172a"; radius: 6 }
                                    contentItem: Text {
                                        text: parent.text
                                        color: "white"
                                        font.bold: true
                                        font.pixelSize: 16
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    onClicked: {
                                        if (userDashboard.tempCheckInStr === "" || userDashboard.tempCheckOutStr === "") {
                                            HotelApp.notify("Harap lengkapi tanggal Check-In dan Check-Out terlebih dahulu!", true)
                                            return
                                        }

                                        // Menggunakan model data ComboBox sebagai Tipe Kamar
                                        var selectedRoomType = roomTypeCombo.currentValue

                                        // Eksekusi pemesanan
                                        if (HotelApp.bookRoom(selectedRoomType, userDashboard.tempCheckInStr, userDashboard.tempCheckOutStr)) {
                                            HotelApp.notify("Pemesanan " + selectedRoomType + " berhasil diajukan!", false)
                                            // Opsional: Langsung arahkan ke halaman transaksi untuk melihat status
                                            userStack.currentIndex = 1;
                                            loadUserTx();
                                        }
                                    }
                                }
                            }
                        }

                        // 2. BAGIAN DAFTAR TIPE KAMAR (Bagian Bawah)
                        Text {
                            text: "TIPE KAMAR"
                            Layout.alignment: Qt.AlignHCenter
                            font.family: "Times New Roman"
                            font.pixelSize: 22
                            font.bold: true
                            color: "#0f172a"
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 20

                            // CARD 1: STANDARD
                            RoomCard {
                                Layout.fillWidth: true
                                imageSource: "images/standard.jpg" // Sesuaikan path Anda
                                roomName: "Standard"
                                description: "Pilihan terbaik untuk perjalanan bisnis atau liburan singkat dengan harga terjangkau."
                                price: "Rp 750.000/malam"
                            }

                            // CARD 2: SUITE
                            RoomCard {
                                Layout.fillWidth: true
                                imageSource: "images/suite.jpg"
                                roomName: "Suite"
                                description: "Kamar luas dengan pemandangan indah, cocok untuk liburan keluarga."
                                price: "Rp 1.350.000/malam"
                            }

                            // CARD 3: DELUXE
                            RoomCard {
                                Layout.fillWidth: true
                                imageSource: "images/deluxe.jpg"
                                roomName: "Deluxe"
                                description: "Nikmati pengalaman menginap dengan fasilitas premium dan layanan eksklusif."
                                price: "Rp 2.000.000/malam"
                            }
                        }

                        Item { height: 40 } // Bottom padding
                    }
                }
            }
            Rectangle {
                color: "#f4f6f9"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 40
                    Text { text: "Riwayat Transaksi Saya"; font.pixelSize: 28; font.bold: true; color: "#2c3e50" }

                    ListView {
                        id: userTxList
                        Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 12
                        delegate: Rectangle {
                            width: ListView.view.width;
                            height: 75; radius: 8;
                            border.color: "#e2e8f0"
                            color: "white"

                            RowLayout {
                                anchors.fill: parent;
                                anchors.margins: 15

                                ColumnLayout {
                                    Layout.preferredWidth: 200
                                    Text { text: "Kamar ID: " + modelData.nomorKamar; font.bold: true; font.pixelSize: 15; color: "#2c3e50" }
                                    Text { text: "Total: Rp " + modelData.total; color: "#27ae60"; font.bold: true }
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    Text { text: "Check-In: " + modelData.checkIn; font.pixelSize: 13; color: "#7f8c8d" }
                                    Text { text: "Check-Out: " + modelData.checkOut; font.pixelSize: 13; color: "#7f8c8d" }
                                }

                                Text {
                                    text: "Durasi: " + modelData.malam + " Malam";
                                    font.pixelSize: 13; color: "#7f8c8d"; Layout.rightMargin: 30
                                }

                                Text {
                                    text: modelData.status
                                    font.bold: true
                                    font.pixelSize: 14
                                    color: modelData.status === "Pending" ? "#e67e22" : (modelData.status === "Approved" ? "#27ae60" : (modelData.status === "Completed" ? "#2980b9" : "#e74c3c"))
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Component Reusable untuk Card Tipe Kamar
    component RoomCard : Rectangle {
        id: card
        property string imageSource: ""
        property string roomName: ""
        property string description: ""
        property string price: ""

        height: 380
        color: "white"
        radius: 10
        border.color: "#e2e8f0"
        clip: true

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 180
                color: "#bdc3c7"
                Image {
                    anchors.fill: parent
                    source: card.imageSource
                    fillMode: Image.PreserveAspectCrop
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 15
                spacing: 10

                Text { text: card.roomName; font.pixelSize: 18; font.bold: true; color: "#2c3e50" }
                Text {
                    text: card.description
                    font.pixelSize: 13
                    color: "#7f8c8d"
                    wrapMode: Text.WordWrap
                    lineHeight: 1.3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    verticalAlignment: Text.AlignTop
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Price:"; font.pixelSize: 14; font.bold: true; color: "#2c3e50" }
                    Item { Layout.fillWidth: true }
                    Text { text: card.price; font.pixelSize: 14; font.bold: true; color: "#2c3e50" }
                }
            }
        }
    }

    // Functions for User
    function loadUserTx() { userTxList.model = HotelApp.getMyTransactions() }
}