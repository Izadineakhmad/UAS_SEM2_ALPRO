import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: adminDashboard
    property var stats: ({})
    Component.onCompleted: refreshDashboard()
    function refreshDashboard() {
        stats = HotelApp.getAdminStats();
        loadAdminRooms()
        loadAdminTx()
    }

    function loadAdminRooms() { adminRoomList.model = HotelApp.getAllRooms() }
    function loadAdminTx() { adminTxList.model = HotelApp.getAllTransactions() }


    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar Admin
        Rectangle {
            Layout.preferredWidth: 260
            Layout.fillHeight: true
            color: "#1a252f"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Text { text: "ADMIN PANEL"; color: "white"; font.pixelSize: 22; font.bold: true; Layout.bottomMargin: 30 }

                Button { text: "Dashboard Statistik"; Layout.fillWidth: true; onClicked: adminStack.currentIndex = 0 }
                Button { text: "Kelola Kamar"; Layout.fillWidth: true; onClicked: { adminStack.currentIndex = 1; loadAdminRooms() } }
                Button { text: "Kelola Transaksi"; Layout.fillWidth: true; onClicked: { adminStack.currentIndex = 2; loadAdminTx() } }
                Button { text: "Simpan Data (File)"; Layout.fillWidth: true; onClicked: HotelApp.saveData() }

                Item { Layout.fillHeight: true }
                Button {
                    text: "Logout"; Layout.fillWidth: true; background: Rectangle { color: "#e74c3c"; radius: 5 }
                    onClicked: { HotelApp.logout(); mainStack.replace(loginPage) }
                }
            }
        }

        // Konten Kanan Admin
        StackLayout {
            id: adminStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: 0

            // Page 0: Statistik
            Rectangle {
                color: "#ecf0f1"
                ColumnLayout {
                    id : adminStatsList
                    anchors.fill: parent
                    anchors.margins: 40
                    spacing: 20
                    Text {
                        text: "Ringkasan Sistem";
                        font.pixelSize: 30;
                        font.bold: true;
                        color: "#2c3e50"
                    }
                    GridLayout {
                        columns: 3
                        rowSpacing: 20; columnSpacing: 20
                        Layout.fillWidth: true
                        visible: stats !== null
                        // Widget helper
                        component StatCard : Rectangle {
                            id: cardRoot
                            width: 250;
                            height: 120;
                            radius: 10;
                            color: "white"
                            property string title: ""
                            property string val: ""

                            ColumnLayout {
                                anchors.centerIn: parent;
                                spacing: 10
                                Text { text: cardRoot.title;
                                    color: "#7f8c8d";
                                    font.pixelSize: 16
                                }
                                Text {
                                    text: cardRoot.val;
                                    color: "#2c3e50";
                                    font.pixelSize: 32;
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }

                        StatCard { title: "Total Kamar"; val : stats.totalKamar.toString()}
                        StatCard { title: "Kamar Tersedia"; val: stats.kamarTersedia.toString() }
                        StatCard { title: "Kamar Dipesan"; val: stats.kamarBooked.toString() }
                        StatCard { title: "Total Pengguna"; val: stats.totalUser.toString() }
                        StatCard { title: "Total Transaksi"; val: stats.totalTransaksi.toString() }
                        StatCard { title: "Transaksi Pending"; val: stats.transaksiPending.toString() }
                    }
                    Item { Layout.fillHeight: true }
                }
            }

            // Page 1: CRUD Kamar
            Rectangle {
                color: "#ecf0f1"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 40
                    RowLayout {
                        Text { text: "Kelola Data Kamar"; font.pixelSize: 30; font.bold: true; Layout.fillWidth: true }
                        Button {
                            text: "+ Tambah Kamar"
                            background: Rectangle { color: "#27ae60"; radius: 5 }
                            contentItem: Text { text: "+ Tambah Kamar"; color: "white"; font.bold:true }
                            onClicked: addRoomPopup.open()
                        }
                    }

                    ListView {
                        id: adminRoomList
                        Layout.fillWidth: true;
                        Layout.fillHeight: true;
                        clip: true;
                        spacing: 10
                        delegate: Rectangle {
                            width: ListView.view.width; height: 70; radius: 8; color: "white"
                            RowLayout {
                                anchors.fill: parent; anchors.margins: 15
                                Text { text: "No: " + modelData.nomorKamar; font.bold: true; font.pixelSize: 18; Layout.preferredWidth: 100 }
                                Text { text: modelData.tipe; Layout.preferredWidth: 150 }
                                Text { text: "Rp " + modelData.harga; color: "#27ae60"; font.bold: true; Layout.preferredWidth: 150 }
                                Text { text: modelData.status; color: modelData.status ==="Available"?"#2980b9":"#e67e22"; Layout.fillWidth: true }

                                Button {
                                    text: "Hapus"
                                    background: Rectangle { color: "#e74c3c"; radius: 5 }
                                    onClicked: {
                                        // [Kriteria: Konfirmasi sebelum menghapus]
                                        confirmDeleteDialog.roomId = modelData.id
                                        confirmDeleteDialog.open()
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Page 2: Transaksi
            Rectangle {
                color: "#ecf0f1"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 40
                    Text { text: "Persetujuan Transaksi"; font.pixelSize: 30; font.bold: true }
                    ListView {
                        id: adminTxList
                        Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 10
                        delegate: Rectangle {
                            width: ListView.view.width; height: 70; radius: 8; color: "white"
                            RowLayout {
                                anchors.fill: parent; anchors.margins: 15
                                Text { text: "Kamar: " + modelData.nomorKamar; font.bold: true; Layout.preferredWidth: 150 }
                                Text { text: modelData.malam + " Malam"; Layout.preferredWidth: 100 }
                                Text { text: "Rp " + modelData.total; color: "#27ae60"; font.bold: true; Layout.fillWidth: true }

                                Button {
                                    text: "Terima"
                                    visible: modelData.status === "Pending"
                                    onClicked: { HotelApp.processTransaction(modelData.id, "Approved"); loadAdminTx() }
                                }
                                Button {
                                    text: "Tolak"
                                    visible: modelData.status === "Pending"
                                    background: Rectangle { color: "#e74c3c"; radius: 5 }
                                    onClicked: { HotelApp.processTransaction(modelData.id, "Rejected"); loadAdminTx() }
                                }
                                Text {
                                    text: modelData.status
                                    visible: modelData.status !== "Pending"
                                    font.bold: true; color: modelData.status === "Approved" ? "#27ae60" : "#e74c3c"
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // --- POPUPS ADMIN ---
    Dialog {
        id: addRoomPopup
        anchors.centerIn: parent
        title: "Tambah Kamar Baru"
        standardButtons: Dialog.Save | Dialog.Cancel
        ColumnLayout {
            TextField { id: inNo; placeholderText: "Nomor Kamar" }
            TextField { id: inTipe; placeholderText: "Tipe (Standard/Deluxe)" }
            TextField { id: inHarga; placeholderText: "Harga per Malam"; validator: IntValidator{} }
        }
        onAccepted: {
            if(HotelApp.addRoom(inNo.text, inTipe.text, parseInt(inHarga.text), 2)) {
                adminDashboard.loadAdminRooms()
                inNo.text = ""; inTipe.text = ""; inHarga.text = ""
            }
        }
    }

    Dialog {
        id: confirmDeleteDialog
        anchors.centerIn: parent
        title: "Konfirmasi Hapus"
        property int roomId: -1
        Text { text: "Apakah Anda yakin ingin menghapus data kamar ini?" }
        standardButtons: Dialog.Yes | Dialog.No
        onAccepted: {
            HotelApp.deleteRoom(roomId);
            adminDashboard.loadAdminRooms();
        }
    }


}

