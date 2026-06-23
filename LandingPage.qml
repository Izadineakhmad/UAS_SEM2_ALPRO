import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    // Sinyal untuk memberitahu Main.qml agar berpindah ke halaman login
    signal loginRequested()

    // --- BACKGROUND IMAGE ---
    Image {
        anchors.fill: parent
        // Menggunakan gambar placeholder bernuansa resort mewah (silakan ganti dengan gambar lokal jika ada)
        source: "images/hotel.jpg"
        fillMode: Image.PreserveAspectCrop

        // Overlay warna gelap agar teks putih tetap terbaca jelas
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.4
        }
    }

    // --- NAVBAR (BAGIAN ATAS) ---
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100
        color: "white"

        RowLayout {
            anchors.fill: parent //  Layout memenuhi seluruh ruang Rectangle pembungkus

            Item { Layout.fillWidth: true } // Spacer Fleksibel Kiri

            // 1. Logo Text
            Image {
                source: "images/logo.png"
                Layout.preferredWidth: 500
                Layout.preferredHeight: 70
                Layout.alignment: Qt.AlignVCenter
                fillMode: Image.PreserveAspectFit
            }

            Item { Layout.fillWidth: true } // Spacer Fleksibel Kanan
        }
    }

    // --- HERO SECTION (BAGIAN TENGAH) ---
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 25
        width: parent.width * 0.8

        // Judul Utama (Menggunakan font Serif agar elegan sesuai gambar)
        Text {
            text: "Enjoy Your Dream Vacation"
            font.family: "Times New Roman"
            font.pixelSize: 64
            color: "white"
            Layout.alignment: Qt.AlignHCenter
            horizontalAlignment: Text.AlignHCenter
        }

        // Sub-judul
        Text {
            text: "Experience the ultimate luxury and comfort at our hotel.\nBook your stay today and create unforgettable memories."
            font.pixelSize: 17
            color: "#f0f0f0"
            lineHeight: 1.4
            Layout.alignment: Qt.AlignHCenter
            horizontalAlignment: Text.AlignHCenter
        }

        // Kumpulan Tombol Utama
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 25
            spacing: 20

            // Tombol "Book Now" (Solid Blue)
            Button {
                text: "Book Now"
                Layout.preferredWidth: 160
                Layout.preferredHeight: 50

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: parent.down ? Qt.rgba(1.0, 1.0, 1.0, 0.3) : (parent.hovered ? Qt.rgba(1.0, 1.0, 1.0, 0.15)  : Qt.rgba(0, 0, 0, 0.2))
                    border.color: "white"
                    border.width: 2
                }

                onClicked: root.loginRequested() // Arahkan ke sistem login untuk booking
            }
        }
    }
}