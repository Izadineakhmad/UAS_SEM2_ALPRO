# Dokumentasi Sistem Manajemen Hotel

## Deskripsi Proyek
Sistem Manajemen Hotel ini adalah aplikasi desktop yang dikembangkan menggunakan kerangka kerja Qt 6. Antarmuka pengguna dibangun menggunakan QML (Qt Quick) untuk memberikan pengalaman visual yang responsif dan modern, sementara logika inti sistem dan pemrosesan data ditulis menggunakan C++ standar. 

Sistem ini mendukung arsitektur multi-peran yang memisahkan hak akses antara Administrator dan Pengguna (Tamu). Fitur utama meliputi pendaftaran dan persetujuan akun, manajemen inventaris kamar (CRUD), pemesanan kamar, serta pelacakan riwayat transaksi. Seluruh data disebarkan secara persisten menggunakan operasi *File Stream* (I/O) standar C++ ke dalam format file *Comma-Separated Values* (CSV).

## Prasyarat Sistem
Sebelum melakukan konfigurasi dan kompilasi proyek, pastikan lingkungan pengembangan Anda telah memenuhi persyaratan berikut:

* **Qt Framework:** Versi 6.10 atau yang lebih baru (termasuk modul Qt Quick dan Qt Qml).
* **IDE:** Qt Creator.
* **Build System:** CMake (versi 3.16 atau yang lebih baru).
* **Compiler:** Kompilator C++ yang mendukung standar C++17 atau yang lebih baru (MSVC untuk Windows, GCC untuk Linux, atau Clang untuk macOS).

## Konfigurasi dan Instalasi

### 1. Mengimpor Proyek ke Qt Creator
1. Buka aplikasi Qt Creator.
2. Pilih menu **File** > **Open File or Project...**.
3. Navigasikan ke direktori proyek Anda dan pilih file `CMakeLists.txt`.
4. Pada jendela konfigurasi proyek (*Configure Project*), pilih *Kit* yang sesuai dengan sistem operasi Anda (misalnya: *Desktop Qt 6.x.x MinGW 64-bit* atau *MSVC 64-bit*).
5. Klik **Configure Project**.

### 2. Konfigurasi Aset dan Direktori
Sistem ini menggunakan integrasi modul QML melalui CMake (`qt_add_qml_module`). Direktori aset harus terstruktur dengan benar agar antarmuka dapat merender gambar.

Pastikan struktur direktori di tingkat root proyek Anda (sejajar dengan `CMakeLists.txt`) memiliki folder `images` yang berisi aset visual yang dipanggil di dalam file QML, misalnya:
* `images/logovertical.png`
* `images/standard.jpg`
* `images/deluxe.jpg`
* `images/suite.jpg`

Tidak perlu menggunakan file `qml.qrc` secara manual, karena `CMakeLists.txt` telah dikonfigurasi untuk menyertakan aset-aset ini ke dalam modul kompilasi.

### 3. Konfigurasi Penyimpanan Data (CSV)
Aplikasi ini membaca dan menulis data menggunakan file CSV (seperti `users_data.csv`).
* File CSV akan secara otomatis dibuat oleh sistem pada saat pertama kali aplikasi dijalankan apabila file tersebut belum eksis.
* **Penting:** File CSV ini akan disimpan di dalam **direktori kerja (Working Directory)** atau **direktori build** (misalnya direktori `build-Hotel-Desktop_Qt_6...` yang dihasilkan oleh Qt Creator), bukan di direktori *source code*. Jika Anda perlu memeriksa atau memodifikasi file CSV secara manual, pastikan Anda mencarinya di dalam direktori *build* tersebut.

### 4. Proses Kompilasi (Build)
1. Lakukan pembersihan proyek terlebih dahulu dengan memilih menu **Build** > **Clean All**.
2. Jalankan konfigurasi ulang dengan memilih menu **Build** > **Run CMake**.
3. Lakukan kompilasi dengan menekan ikon **Build** (ikon palu) pada sudut kiri bawah IDE atau melalui menu **Build** > **Build Project**.
4. Setelah kompilasi berhasil tanpa peringatan kritis, tekan ikon **Run** (ikon segitiga hijau) untuk meluncurkan aplikasi.

## Informasi Pengujian Sistem (Seeder)
Sistem memiliki mekanisme inisialisasi otomatis yang akan menyuntikkan data *dummy* jika file data masih kosong. Untuk pengujian awal pasca-instalasi, Anda dapat menggunakan kredensial Administrator bawaan berikut:


* **Username:** admin
* **Password:** admin
*
* USER
* * **Username:** admin
* **Password:** admin

Setelah masuk ke dalam Panel Admin, Anda dapat menyetujui akun pengguna baru yang terdaftar melalui antarmuka pendaftaran, mengelola kamar, serta mengelola transaksi secara penuh.
