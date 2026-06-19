import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: userDashboard
    RowLayout {
        spacing: 0
        anchors.fill: parent

        Component.onCompleted: {
            userStack.currentIndex = 0;
        }

        Rectangle {
            Layout.preferredWidth: 260; Layout.fillHeight: true; color: "#2980b9"
            ColumnLayout {
                anchors.fill: parent; anchors.margins: 20; spacing: 15
                Text { text: "Halo, " + HotelApp.currentUserName;
                    color: "white";
                    font.pixelSize: 22;
                    font.bold: true;
                    Layout.bottomMargin: 30
                }
                Button { text: "Pesan Kamar"; Layout.fillWidth: true; onClicked: { userStack.currentIndex = 0; loadUserRooms() } }
                Button { text: "Riwayat Transaksi"; Layout.fillWidth: true; onClicked: { userStack.currentIndex = 1; loadUserTx() } }
                Item { Layout.fillHeight: true }
                Button {
                    text: "Logout";
                    Layout.fillWidth: true;
                    background:
                        Rectangle {
                        color: "#e74c3c";
                        radius: 5
                    }
                    onClicked: {
                        HotelApp.logout();
                        mainStack.replace("LoginView.qml")
                    }
                }
            }
        }

        StackLayout {
            id: userStack
            Layout.fillWidth: true; Layout.fillHeight: true
            currentIndex: 0

            // Page 0: Cari & Pesan Kamar
            Rectangle {
                color: "#f4f6f9"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 40; spacing: 15
                    Text { text: "Pesan Kamar"; font.pixelSize: 30; font.bold: true }

                    RowLayout {
                        // [Kriteria: Searching & Sorting]
                        TextField {
                            id: searchBox
                            placeholderText: "Cari tipe atau nomor..."
                            Layout.preferredWidth: 300
                            onTextChanged: userRoomList.model = HotelApp.searchRooms(text)
                        }
                        Button {
                            text: "Urutkan Harga Termurah"
                            onClicked: userRoomList.model = HotelApp.getAvailableRoomsSortedByPrice()
                        }
                    }

                    ListView {
                        id: userRoomList
                        Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 10
                        delegate: Rectangle {
                            width: ListView.view.width; height: 80; radius: 8; border.color: "#bdc3c7"
                            RowLayout {
                                anchors.fill: parent; anchors.margins: 15
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    Text { text: "Kamar " + modelData.nomorKamar; font.bold: true; font.pixelSize: 18 }
                                    Text { text: modelData.tipe; color: "gray" }
                                }
                                Text { text: "Rp " + modelData.harga; font.bold: true; color: "#27ae60"; Layout.rightMargin: 20 }
                                Button {
                                    text: "Booking"
                                    background: Rectangle { color: "#3498db"; radius: 5 }
                                    onClicked: { bookDialog.roomId = modelData.id; bookDialog.open() }
                                }
                            }
                        }
                    }
                }
            }

            // Page 1: Riwayat Transaksi User
            Rectangle {
                color: "#f4f6f9"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 40
                    Text { text: "Riwayat Transaksi Saya"; font.pixelSize: 30; font.bold: true }
                    ListView {
                        id: userTxList
                        Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 10
                        delegate: Rectangle {
                            width: ListView.view.width; height: 70; radius: 8; border.color: "#bdc3c7"
                            RowLayout {
                                anchors.fill: parent; anchors.margins: 15
                                Text { text: "Kamar: " + modelData.nomorKamar; font.bold: true; Layout.preferredWidth: 150 }
                                Text { text: "Total: Rp " + modelData.total; Layout.fillWidth: true }
                                Text { text: modelData.status; font.bold: true; color: modelData.status==="Pending"?"#e67e22":(modelData.status==="Approved"?"#27ae60":"#e74c3c") }
                            }
                        }
                    }
                }
            }
        }
    }

    // Dialog Booking User
    Dialog {
        id: bookDialog
        anchors.centerIn: parent
        title: "Konfirmasi Booking"
        property int roomId: -1
        standardButtons: Dialog.Ok | Dialog.Cancel
        ColumnLayout {
            Text { text: "Berapa malam Anda ingin menginap?" }
            TextField { id: inputMalam; text: "1"; validator: IntValidator{bottom: 1} }
        }
        onAccepted: {
            if(HotelApp.bookRoom(roomId, parseInt(inputMalam.text))) {
                userDashboard.loadUserRooms() // Refresh daftar kamar
            }
        }
    }


    // Functions for User
    function loadUserRooms() { userRoomList.model = HotelApp.getAvailableRooms() }
    function loadUserTx() { userTxList.model = HotelApp.getMyTransactions() }
}

