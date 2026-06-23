import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import "components/QDatePicker"

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
    function loadAdminUsers() { adminUserList.model = HotelApp.getAllUsers() }
    function roomPriceandCapacity(valueCombo) {
        switch (valueCombo) {
        case "Standard" :
            return [500000, 1];
        case "Deluxe" :
            return [800000, 2];
        case "Suite" :
            return [1500000, 4];
        default :
            return undefined;
        }
    }

    function getStatusColor(status) {
        switch(status) {
            case "Pending":
                return "#e67e22"; // Oranye/Amber: Menunggu persetujuan
            case "Approved":
                return "#27ae60"; // Hijau: Berhasil disetujui
            case "Completed":
                return "#2980b9"; // Biru: Sudah selesai
            case "Rejected":
                return "#e74c3c"; // Merah: Ditolak
            default:
                return "#7f8c8d"; // Abu-abu: Status tidak diketahui
        }
    }


    function statustoInt(status) {
        switch(status) {
            case "Available"   : return 1;
            case "Booked"      : return 2;
            case "Maintenance" : return 3;
            default: return undefined;
        }
    }

    function formatAngka(angka) {
        return angka.toFixed(0).replace(/\B(?=(\d{3})+(?!\d))/g, ".")
    }

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

                Text {
                    text: "ADMIN PANEL";
                    color: "white";
                    font.pixelSize: 22;
                    font.bold: true;
                    Layout.bottomMargin: 30
                }

                Button {
                    text: "Dashboard Statistik";
                    Layout.fillWidth: true;
                    onClicked: adminStack.currentIndex = 0
                }

                Button {
                    text: "Kelola Kamar";
                    Layout.fillWidth: true;
                    onClicked: {
                        adminStack.currentIndex = 1;
                        loadAdminRooms()
                    }
                }

                Button {
                    text: "Kelola Transaksi";
                    Layout.fillWidth: true;
                    onClicked: {
                        adminStack.currentIndex = 2;
                        loadAdminTx()
                    }
                }

                Button {
                    text: "Kelola Pengguna";
                    Layout.fillWidth: true;
                    onClicked: {
                        adminStack.currentIndex = 3;
                        loadAdminUsers()
                    }
                }

                Item { Layout.fillHeight: true }

                Button {
                    text: "Logout";
                    Layout.fillWidth: true;
                    background: Rectangle {
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
                        rowSpacing: 20;
                        columnSpacing: 20
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
                                    Layout.alignment: Qt.AlignHCenter
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

                                Text {
                                    text: "No: " + modelData.nomorKamar;
                                    font.bold: true;
                                    font.pixelSize: 18;
                                    Layout.preferredWidth: 100
                                }

                                Text {
                                    text: modelData.tipe;
                                    Layout.preferredWidth: 150
                                }

                                Text {
                                    text: "Rp " + formatAngka(modelData.harga);
                                    color: "#27ae60";
                                    font.bold: true;
                                    Layout.preferredWidth: 150
                                }

                                Text {
                                    text: modelData.status;
                                    color: modelData.status ==="Available" ? "#2980b9" : "#e67e22";
                                    Layout.fillWidth: true
                                }

                                RowLayout {
                                    spacing: 10

                                    Button {
                                        text: "Hapus"
                                        background: Rectangle { color: "#e74c3c"; radius: 5 }
                                        onClicked: {
                                            // [Kriteria: Konfirmasi sebelum menghapus]
                                            confirmDeleteDialog.roomId = modelData.id
                                            confirmDeleteDialog.open()
                                        }
                                    }

                                    Button {
                                        text: "Edit"
                                        background: Rectangle {
                                            color: "#fdc700";
                                            radius: 5
                                        }
                                        onClicked: {
                                            // [Kriteria: Konfirmasi sebelum menghapus]
                                            editRoomPopup.roomId = modelData.id
                                            editRoomPopup.defaultNo = modelData.nomorKamar
                                            editRoomPopup.defaultStatus = statustoInt(modelData.status);
                                            editRoomPopup.defaultTipe = modelData.tipe
                                            editRoomPopup.open()
                                        }
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

                    Text {
                        text: "Persetujuan Transaksi";
                        font.pixelSize: 30;
                        font.bold: true
                    }

                    ListView {
                        id: adminTxList
                        Layout.fillWidth: true;
                        Layout.fillHeight: true;
                        clip: true;
                        spacing: 10

                        delegate: Rectangle {
                            width: ListView.view.width; height: 70; radius: 8; color: "white"
                            RowLayout {
                                anchors.fill: parent; anchors.margins: 15
                                Text { text: "Kamar: " + modelData.nomorKamar; font.bold: true; Layout.preferredWidth: 150 }
                                Text { text: modelData.malam + " Malam"; Layout.preferredWidth: 100 }
                                Text {
                                    text: "Rp " + formatAngka(modelData.total)
                                    color: "#27ae60"
                                    font.bold: true
                                    Layout.fillWidth: true
                                }

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
                                    font.bold: true;
                                    color: getStatusColor(modelData.status)
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                color: "#ecf0f1"
                ColumnLayout {
                    anchors.fill: parent;
                    anchors.margins: 40

                    RowLayout {
                        Text { text: "Kelola Akun Pengguna";
                            font.pixelSize: 30;
                            font.bold: true;
                            Layout.fillWidth: true }
                        Button {
                            text: "+ Tambah Pengguna"
                            background: Rectangle {
                                color: "#27ae60";
                                radius: 5
                            }
                            contentItem: Text {
                                text: "+ Tambah Pengguna";
                                color: "white";
                                font.bold:true
                            }
                            onClicked: {
                                addUserPopup.clearForm();
                                addUserPopup.open();
                            }
                        }
                    }

                    ListView {
                        id: adminUserList
                        Layout.fillWidth: true;
                        Layout.fillHeight: true;
                        clip: true;
                        spacing: 10
                        delegate: Rectangle {
                            width: ListView.view.width;
                            height: 75;
                            radius: 8;
                            color: "white"
                            border.color: "#bdc3c7"

                            RowLayout {
                                anchors.fill: parent;
                                anchors.margins: 15

                                ColumnLayout {
                                    Layout.preferredWidth: 200
                                    Text {
                                        text: modelData.nama;
                                        font.bold: true;
                                        font.pixelSize: 16
                                    }
                                    Text {
                                        text: "Username: " + modelData.username;
                                        color: "#7f8c8d";
                                        font.pixelSize: 12
                                    }
                                }

                                Text {
                                    text: modelData.roleStr;
                                    Layout.preferredWidth: 100;
                                    font.bold: true;
                                    color: modelData.roleStr === "ADMIN" ? "#8e44ad" : "#2c3e50"
                                }
                                Text {
                                    text: modelData.statusStr;
                                    Layout.fillWidth: true;
                                    font.bold: true;
                                    color: modelData.statusStr === "Active" ? "#27ae60" : "#e67e22"
                                }

                                RowLayout {
                                    spacing: 10

                                    Button {
                                        text: "Approve"
                                        visible: modelData.statusStr === "Pending"
                                        background: Rectangle {
                                            color: "#2980b9";
                                            radius: 5
                                        }
                                        contentItem: Text {
                                            text: parent.text;
                                            color: "white"
                                        }
                                        onClicked: {
                                            HotelApp.approveUser(modelData.id);
                                            loadAdminUsers();
                                        }
                                    }

                                    Button {
                                        text: "Edit"
                                        background: Rectangle {
                                            color: "#f39c12";
                                            radius: 5
                                        }
                                        contentItem: Text {
                                            text: parent.text;
                                            color: "white"
                                        }
                                        onClicked: {
                                            editUserPopup.userId = modelData.id;
                                            editUserPopup.defaultNama = modelData.nama;
                                            editUserPopup.defaultUser = modelData.username;
                                            editUserPopup.defaultPass = modelData.password;
                                            editUserPopup.defaultRoleInt = modelData.roleInt;
                                            editUserPopup.defaultStatusInt = modelData.statusInt;
                                            editUserPopup.open();
                                        }
                                    }

                                    Button {
                                        text: "Hapus"
                                        background: Rectangle {
                                            color: "#e74c3c";
                                            radius: 5
                                        }
                                        contentItem: Text {
                                            text: parent.text;
                                            color: "white"
                                        }
                                        onClicked: {
                                            confirmDeleteUserDialog.userId = modelData.id;
                                            confirmDeleteUserDialog.open();
                                        }
                                    }
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
            TextField {
                id: inNo;
                placeholderText: "Nomor Kamar"
            }
            ComboBox {
                id: inTipe
                model: ["Standard", "Deluxe", "Suite"]
                Layout.fillWidth: true
                currentIndex: -1
                displayText: currentIndex === -1 ? "Tipe Kamar" : currentText
                background: Rectangle {
                    color: "white"
                    border.color: "gray";
                    border.width: 1
                }

                delegate: ItemDelegate {
                        width: inTipe.width
                        text: modelData
                        highlighted: inTipe.highlightedIndex === index

                        // Mengatur font opsi
                        contentItem: Text {
                            text: parent.text
                            font: inTipe.font
                            color: parent.highlighted ? "#ffffff" : "#2c3e50"
                            verticalAlignment: Text.AlignVCenter
                        }

                        // Background tiap baris opsi saat disorot/hover
                        background: Rectangle {
                            color: parent.highlighted ? "#2196F3" : "white"
                        }
                }
            }
        }

        onAccepted: {

            if(HotelApp.addRoom(inNo.text, inTipe.currentValue, parseInt(roomPriceandCapacity(inTipe.currentValue)[0]), roomPriceandCapacity(inTipe.currentValue)[1])) {
                adminDashboard.loadAdminRooms()
            }

            inNo.text = "";
            inTipe.currentIndex = -1
            inHarga.text = ""
        }
    }

    Dialog {
        id: editRoomPopup
        property int roomId         : -1
        property string defaultNo   : ""
        property string defaultTipe : ""
        property int defaultStatus  : -1

        anchors.centerIn: parent
        title: "Edit Kamar"
        standardButtons: Dialog.Save | Dialog.Cancel
        ColumnLayout {

            TextField {
                id: editNo;
                placeholderText: "Nomor Kamar"
                text: editRoomPopup.defaultNo
            }

            ComboBox {
                id: editTipe
                model: ["Standard", "Deluxe", "Suite"]
                Layout.fillWidth: true
                currentValue: editRoomPopup.defaultTipe
                background: Rectangle {
                    color: "white"
                    border.color: "gray";
                    border.width: 1
                }
                delegate: ItemDelegate {
                        width: editTipe.width
                        highlighted: editTipe.highlightedIndex === index
                        text: modelData
                        // Mengatur font opsi
                        contentItem: Text {
                            text: parent.text
                            font: editTipe.font
                            color: parent.highlighted ? "#ffffff" : "#2c3e50"
                            verticalAlignment: Text.AlignVCenter
                        }

                        // Background tiap baris opsi saat disorot/hover
                        background: Rectangle {
                            color: parent.highlighted ? "#2196F3" : "white"
                        }
                }
            }

            ComboBox {
                id: editStatus
                textRole: "name"
                valueRole : "id"
                currentValue: editRoomPopup.defaultStatus
                model: [
                    { name : "Available",   id :  1 },
                    { name : "Booked",      id :  2 },
                    { name : "Maintenance",  id:  3 }
                ]
                Layout.fillWidth: true
                background: Rectangle {
                    color: "white"
                    border.color: "gray";
                    border.width: 1
                }

                delegate: ItemDelegate {
                        width: editStatus.width
                        highlighted: editStatus.highlightedIndex === index

                        // Mengatur font opsi
                        contentItem: Text {
                            text: modelData.name
                            font: editStatus.font
                            color: parent.highlighted ? "#ffffff" : "#2c3e50"
                            verticalAlignment: Text.AlignVCenter
                        }

                        // Background tiap baris opsi saat disorot/hover
                        background: Rectangle {
                            color: parent.highlighted ? "#2196F3" : "white"
                        }
                }
            }

        }

        onAccepted: {

            if(HotelApp.editRoom(roomId, editNo.text, editTipe.currentValue,parseInt(roomPriceandCapacity(editTipe.currentValue)[0]), editTipe.currentValue,parseInt(roomPriceandCapacity(editTipe.currentValue)[1]))) {
                adminDashboard.loadAdminRooms()
            }

            editNo.text = editRoomPopup.defaultNo;
            editTipe.currentValue = editRoomPopup.defaultTipe
            editStatus.currentValue = editRoomPopup.defaultStatus
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

    // --- POPUPS ADMIN PENGGUNA ---
        Dialog {
            id: addUserPopup
            anchors.centerIn: parent
            title: "Tambah Pengguna Baru"
            standardButtons: Dialog.Save | Dialog.Cancel

            function clearForm() {
                inNama.text = ""; inUsername.text = ""; inPassword.text = "";
                inRole.currentIndex = 1;   // Default USER
                inStatus.currentIndex = 1; // Default ACTIVE
            }

            ColumnLayout {
                spacing: 10
                TextField { id: inNama; placeholderText: "Nama Lengkap"; Layout.fillWidth: true }
                TextField { id: inUsername; placeholderText: "Username"; Layout.fillWidth: true }
                TextField { id: inPassword; placeholderText: "Password"; Layout.fillWidth: true }

                ComboBox {
                    id: inRole
                    textRole: "name"
                    valueRole: "val"
                    model: [
                        { name: "ADMIN", val: 0 },
                        { name: "USER", val: 1 }
                    ]
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "white"
                        border.color: "gray";
                        border.width: 1
                    }
                    delegate: ItemDelegate {
                            width: inRole.width
                            highlighted: inRole.highlightedIndex === index

                            // Mengatur font opsi
                            contentItem: Text {
                                text: modelData.name
                                font: inRole.font
                                color: parent.highlighted ? "#ffffff" : "#2c3e50"
                                verticalAlignment: Text.AlignVCenter
                            }

                            // Background tiap baris opsi saat disorot/hover
                            background: Rectangle {
                                color: parent.highlighted ? "#2196F3" : "white"
                            }
                    }
                }
                ComboBox {
                    id: inStatus
                    textRole: "name"
                    valueRole: "val"
                    model: [
                        { name: "Pending", val: 0 },
                        { name: "Active", val: 1 }
                    ]
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "white"
                        border.color: "gray";
                        border.width: 1
                    }
                    delegate: ItemDelegate {
                            width: inStatus.width
                            highlighted: inStatus.highlightedIndex === index

                            // Mengatur font opsi
                            contentItem: Text {
                                text: modelData.name
                                font: inStatus.font
                                color: parent.highlighted ? "#ffffff" : "#2c3e50"
                                verticalAlignment: Text.AlignVCenter
                            }

                            // Background tiap baris opsi saat disorot/hover
                            background: Rectangle {
                                color: parent.highlighted ? "#2196F3" : "white"
                            }
                    }
                }
            }
            onAccepted: {
                if (inUsername.text === "" || inPassword.text === "") return;
                if (HotelApp.addUser(inNama.text, inUsername.text, inPassword.text, inRole.currentValue, inStatus.currentValue)) {
                    adminDashboard.loadAdminUsers();
                }
            }
        }

        Dialog {
            id: editUserPopup
            property int userId: -1
            property string defaultNama: ""
            property string defaultUser: ""
            property string defaultPass: ""
            property int defaultRoleInt: -1
            property int defaultStatusInt: -1

            anchors.centerIn: parent
            title: "Edit Pengguna"
            standardButtons: Dialog.Save | Dialog.Cancel

            onOpened: {
                editNama.text = defaultNama;
                editUsername.text = defaultUser;
                editPassword.text = defaultPass;
                editRole.currentValue = defaultRoleInt;
                editUserStatus.currentValue = defaultStatusInt;
            }

            ColumnLayout {
                spacing: 10
                TextField { id: editNama; placeholderText: "Nama Lengkap"; Layout.fillWidth: true }
                TextField { id: editUsername; placeholderText: "Username"; Layout.fillWidth: true }
                TextField { id: editPassword; placeholderText: "Password"; Layout.fillWidth: true }

                ComboBox {
                    id: editRole
                    textRole: "name"
                    valueRole: "val"
                    model: [ { name: "ADMIN", val: 0 }, { name: "USER", val: 1 } ]
                    Layout.fillWidth: true
                }
                ComboBox {
                    id: editUserStatus
                    textRole: "name"
                    valueRole: "val"
                    model: [ { name: "Pending", val: 0 }, { name: "Active", val: 1 } ]
                    Layout.fillWidth: true
                }
            }
            onAccepted: {
                if (HotelApp.editUser(userId, editNama.text, editUsername.text, editPassword.text, editRole.currentValue, editUserStatus.currentValue)) {
                    adminDashboard.loadAdminUsers();
                }
            }
        }

        Dialog {
            id: confirmDeleteUserDialog
            property int userId: -1
            anchors.centerIn: parent
            title: "Hapus Pengguna"
            Text { text: "Anda yakin ingin menghapus akun pengguna ini?" }
            standardButtons: Dialog.Yes | Dialog.No
            onAccepted: {
                HotelApp.deleteUser(userId);
                adminDashboard.loadAdminUsers();
            }
        }

}