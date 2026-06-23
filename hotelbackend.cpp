#include "hotelbackend.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace HotelCore;

// [Syarat 7: Exception Handling] Custom Exception
class HotelException : public std::runtime_error {
public:
    HotelException(const std::string& msg) : std::runtime_error(msg) {}
};

// [Syarat 8: Function Template]
template <typename Container>
int countData(const Container& c) {
    return c.size();
}

// [Syarat 9: Inline Function & Default Argument]
inline double calculateTotal(int malam, double harga, double diskon = 0.0) {
    return (malam * harga) * (1.0 - diskon);
}

HotelBackend::HotelBackend(QObject *parent) : QObject(parent) {
    // Memuat data kamar dan transaksi (asumsi fungsi Anda sebelumnya)
    loadData();

    // Memuat data user dari CSV
    loadOtomatisCSVUser();

    // Jika file users_data.csv tidak ada atau isinya kosong (empty)
    if (users.empty()) {
        users.push_back(User(1, "Administrator", "admin", "admin", ADMIN, ACTIVE));
        users.push_back(User(2, "Budi Santoso", "budi", "user", USER, ACTIVE));

        // Simpan seeder awal ini ke dalam CSV agar permanen
        saveUsersToCSV();
    }
}

void HotelBackend::checkAutoCheckout() {
    QDateTime sekarang = QDateTime::currentDateTime();
    QString tglHariIni = sekarang.date().toString("yyyy-MM-dd");
    int jamSekarang = sekarang.time().hour();

    bool adaPerubahan = false;
    qDebug()<<tglHariIni;

    // Iterasi melalui daftar transaksi untuk mendeteksi checkout
    for (auto& t : transactions) {
        // Jika statusnya Approved, tanggal checkout-nya hari ini atau sebelumnya, dan sudah jam 12 siang atau lebih
        if (t.status == "Approved" && t.checkOut <= tglHariIni) {
            Room* r = findRoom(t.idRoom);
            if (r && r->status == BOOKED) {
                if (jamSekarang == 12){
                    r->status = MAINTENANCE;
                } else if (jamSekarang > 12) r->status = AVAILABLE;
                t.status = "Completed"; // Perbarui transaksi menjadi selesai
                adaPerubahan = true;
                qDebug() << "Auto-Checkout Berhasil! Kamar" << r->nomorKamar << "sekarang Available.";
            }
        }
    }

    if (adaPerubahan) {
        saveData(); // Menulis ulang ke file lokal CSV
        emit notify("Sistem otomatis memperbarui kamar yang telah melewati batas waktu check-out!", false);
    }
}

bool HotelBackend::login(const QString& username, const QString& password) {
    // [Syarat 5: Iterator]
    for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->username == username && it->password == password) {
            if (it->status == PENDING) {
                emit notify("Akun anda belum diverify admin!", true);
                return false;
            }
            currentUser = &(*it); // [Syarat 12: Pointer]
            emit userChanged();
            emit notify("Login Berhasil! Selamat datang " + currentUser->username, false);
            return true;
        }
    }
    emit notify("Username atau Password salah!", true);
    return false;
}

bool HotelBackend::registerUser(const QString& name, const QString& username, const QString& password) {
    try {
        for (const auto& u : users) {
            if (u.username == username) {
                throw std::runtime_error("Username sudah terdaftar!");
            }
        }

        int newId = users.empty() ? 1 : users.back().id + 1;

        // Memasukkan User baru dengan status enum STATUS_PENDING
        users.push_back(User(newId, name,username, password, USER, PENDING));

        saveUsersToCSV();
        return true;
    } catch (const std::exception& e) {
        emit notify(e.what(), true);
        return false;
    }
}

void HotelBackend::logout() {
    currentUser = nullptr;
    emit userChanged();
}

void HotelBackend::saveUsersToCSV() {
    std::ofstream file("users_data.csv");
    if (file.is_open()) {
        file << "ID,Nama,Username,Password,Role,Status\n";
        for (const auto& u : users) {
            file << u.id << ","
                 << u.nama.toStdString() << ","
                 << u.username.toStdString() << ","
                 << u.password.toStdString() << ","
                 << static_cast<int>(u.role) << ","
                 << static_cast<int>(u.status) << "\n";
        }
        file.close();
    } else {
        emit notify("Gagal menyimpan data user ke CSV!", true);
    }
}

QVariantList HotelBackend::getAllUsers() {
    QVariantList list;
    for (const auto& u : users) {
        QVariantMap map;
        map["id"] = u.id;
        map["nama"] = u.nama;
        map["username"] = u.username;
        map["password"] = u.password;
        map["roleStr"] = (u.role == ADMIN) ? "ADMIN" : "USER";
        map["roleInt"] = static_cast<int>(u.role);
        map["statusStr"] = (u.status == PENDING) ? "Pending" : "Active";
        map["statusInt"] = static_cast<int>(u.status);
        list << map;
    }
    return list;
}

bool HotelBackend::addUser(const QString& nama, const QString& username, const QString& password, int roleInt, int statusInt) {
    try {
        for (const auto& u : users) {
            if (u.username == username) throw std::runtime_error("Username sudah ada!");
        }
        int newId = users.empty() ? 1 : users.back().id + 1;
        Role roleEnum = static_cast<Role>(roleInt);
        UserStatus statusEnum = static_cast<UserStatus>(statusInt);

        users.push_back(User(newId, nama, username, password, roleEnum, statusEnum));
        saveUsersToCSV();
        emit notify("Pengguna berhasil ditambahkan!", false);
        return true;
    } catch(const std::exception& e) {
        emit notify(e.what(), true);
        return false;
    }
}

bool HotelBackend::editUser(int id, const QString& nama, const QString& username, const QString& password, int roleInt, int statusInt) {
    for (auto& u : users) {
        if (u.id == id) {
            u.nama = nama;
            u.username = username;
            u.password = password;
            u.role = static_cast<Role>(roleInt);
            u.status = static_cast<UserStatus>(statusInt);

            saveUsersToCSV();
            emit notify("Data pengguna diperbarui!", false);
            return true;
        }
    }
    emit notify("Pengguna tidak ditemukan!", true);
    return false;
}

bool HotelBackend::deleteUser(int id) {

    if (id == currentUser->id) {
        emit notify("Tidak Bisa Menghapus diri sendiri",true);
        return false;
    }

    auto it = std::remove_if(users.begin(), users.end(), [id](const User& u) {
        return u.id == id;
    });

    if (it != users.end()) {
        users.erase(it, users.end());
        saveUsersToCSV();
        emit notify("Pengguna dihapus!", false);
        return true;
    }
    return false;
}

bool HotelBackend::approveUser(int id) {
    for (auto& u : users) {
        if (u.id == id) {
            u.status = ACTIVE;
            saveUsersToCSV();
            emit notify("Pengguna berhasil disetujui!", false);
            return true;
        }
    }
    return false;
}


// --- ADMIN FEATURES ---
QVariantMap HotelBackend::getAdminStats() {
    QVariantMap stats;
    stats["totalKamar"] = countData(rooms);
    stats["totalUser"] = countData(users);
    stats["totalTransaksi"] = countData(transactions);

    // [Syarat 1: Lambda Expression] & [Syarat 3: STL Function]
    int tersedia = std::count_if(rooms.begin(), rooms.end(), [](const Room& r) {
        return r.status == AVAILABLE;
    });

    int booked = std::count_if(rooms.begin(), rooms.end(), [](const Room& r) {
        return r.status == BOOKED;
    });

    int pending = std::count_if(transactions.begin(), transactions.end(), [](const Transaction& t) {
        return t.status == "Pending";
    });

    stats["kamarTersedia"] = tersedia;
    stats["kamarBooked"] = booked;
    stats["transaksiPending"] = pending;

    return stats;
}

QVariantList HotelBackend::getAllRooms() {
    QVariantList list;
    for (const auto& r : rooms) {
        QVariantMap map;
        map["id"] = r.id;
        map["nomorKamar"] = r.nomorKamar;
        map["tipe"] = r.tipe;
        map["harga"] = r.harga;
        map["kapasitas"] = r.kapasitas;
        map["status"] = statusToString(r.status);
        list.append(map);
    }
    return list;
}

// [Syarat 10: Passing Parameter (Pass by Const Reference untuk keamanan)]
bool HotelBackend::addRoom(const QString& nomor, const QString& tipe, double harga, int kapasitas) {
    try {
        if (!currentUser || currentUser->role != ADMIN) throw HotelException("Akses Ditolak!");
        if (nomor.isEmpty() || tipe.isEmpty() || harga <= 0) throw HotelException("Data kamar tidak valid!");

        int newId = rooms.empty() ? 1 : rooms.back().id + 1;
        rooms.push_back(Room(newId, nomor, tipe, harga, kapasitas, AVAILABLE));
        saveData();
        emit notify("Kamar berhasil ditambahkan!", false);
        return true;
    } catch (const std::exception& e) {
        emit notify(e.what(), true);
        return false;
    }
}

bool HotelBackend::editRoom(int id, const QString& nomor, const QString& tipe, double harga, int status, int kapasitas) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [id](const Room& r) {
        return r.id == id;
    });
    if (it != rooms.end()) {
        it->harga = harga;
        it->kapasitas = kapasitas;
        it->nomorKamar = nomor;
        it->status = static_cast<RoomStatus>(status);
        it->tipe = tipe;

        saveData();
        emit notify("Kamar berhasil di edit!", false);
        return true;
    }
    emit notify("Kamar tidak ditemukan!", true);
    return false;
}

bool HotelBackend::deleteRoom(int id) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [id](const Room& r) {
        return r.id == id;
    });
    if (it != rooms.end()) {
        rooms.erase(it);
        saveData();
        emit notify("Kamar berhasil dihapus!", false);
        return true;
    }
    emit notify("Kamar tidak ditemukan!", true);
    return false;
}

// --- USER FEATURES ---
QVariantList HotelBackend::getAvailableRooms() {
    checkAutoCheckout();
    QVariantList list;
    for (const auto& r : rooms) {
        if (r.status == AVAILABLE) {
            QVariantMap map;
            map["id"] = r.id;
            map["nomorKamar"] = r.nomorKamar;
            map["tipe"] = r.tipe;
            map["harga"] = r.harga;
            map["kapasitas"] = r.kapasitas;
            list.append(map);
        }
    }
    return list;
}

// [Syarat 2: Sorting]
QVariantList HotelBackend::getAvailableRoomsSortedByPrice() {
    std::vector<Room> tempRooms;
    for(const auto& r : rooms) { if(r.status == AVAILABLE) tempRooms.push_back(r); }

    std::sort(tempRooms.begin(), tempRooms.end(), [](const Room& a, const Room& b) {
        return a.harga < b.harga;
    });

    QVariantList list;
    for(const auto& r : tempRooms) {
        QVariantMap map;
        map["id"] = r.id;
        map["nomorKamar"] = r.nomorKamar;
        map["tipe"] = r.tipe;
        map["harga"] = r.harga;
        list.append(map);
    }
    return list;
}

// [Syarat 2: Searching]
QVariantList HotelBackend::searchRooms(const QString& keyword) {
    QVariantList list;
    for (const auto& r : rooms) {
        if (r.status == AVAILABLE && (r.tipe.contains(keyword, Qt::CaseInsensitive) || r.nomorKamar.contains(keyword))) {
            QVariantMap map;
            map["id"] = r.id;
            map["nomorKamar"] = r.nomorKamar;
            map["tipe"] = r.tipe;
            map["harga"] = r.harga;
            list.append(map);
        }
    }
    return list;
}

bool HotelBackend::bookRoom(const QString& roomType, const QString& checkInDate, const QString& checkOutDate) {
    try {
        if (!currentUser || currentUser->role != USER) throw
            HotelException("Hanya user yang dapat booking!");
        if (checkInDate.isEmpty() || checkOutDate.isEmpty()) throw
            HotelException("Tanggal check-in dan check-out wajib diisi!");

        // Validasi dan parsing format Tanggal
        QDate ci = QDate::fromString(checkInDate, "yyyy-MM-dd");
        QDate co = QDate::fromString(checkOutDate, "yyyy-MM-dd");

        if (!ci.isValid() || !co.isValid()) {
            throw HotelException("Format tanggal salah! Gunakan format yyyy-MM-dd.");
        }

        int hariMenginap = ci.daysTo(co);
        if (hariMenginap <= 0) {
            throw HotelException("Pemesanan tidak valid! Tanggal Check-Out harus setelah Check-In.");
        }

        auto it = std::find_if(rooms.begin(), rooms.end(), [&] (const Room& r) {
            return r.status == AVAILABLE && r.tipe == roomType;
        });

        Room* room = &(*it);

        if (it == rooms.end()) throw
            HotelException("Kamar tidak tersedia!");

        double total = calculateTotal(room->harga, hariMenginap);
        room->status = BOOKED;

        int newTxId = transactions.empty() ? 1 : transactions.back().id + 1;
        transactions.push_back(Transaction(newTxId, currentUser->id, room->id, total, checkInDate, checkOutDate, "Pending"));

        saveData();
        emit notify("Booking berhasil! Menunggu konfirmasi Admin.", false);
        return true;
    } catch(const std::exception& e) {
        emit notify(e.what(), true);
        return false;
    }
}

QVariantList HotelBackend::getAllTransactions() {
    QVariantList list;
    for(const auto& t : transactions) {
        QVariantMap map;
        map["id"] = t.id;
        map["status"] = t.status;
        map["total"] = t.totalBiaya;
        map["checkIn"] = t.checkIn;
        map["checkOut"] = t.checkOut;

        QDate ci = QDate::fromString(t.checkIn, "yyyy-MM-dd");
        QDate co = QDate::fromString(t.checkOut, "yyyy-MM-dd");
        map["malam"] = ci.isValid() && co.isValid() ? ci.daysTo(co) : 0;

        Room* r = findRoom(t.idRoom);
        map["nomorKamar"] = r ? r->nomorKamar : "Tidak diketahui";
        list.append(map);
    }

    return list;
}

QVariantList HotelBackend::getMyTransactions() {
    QVariantList list;
    if(!currentUser) return list;
    for(const auto& t : transactions) {
        if(t.idUser == currentUser->id) {
            QVariantMap map;
            map["id"] = t.id;

            map["status"] = t.status;
            map["total"] = t.totalBiaya;
            map["checkIn"] = t.checkIn;
            map["checkOut"] = t.checkOut;

            QDate ci = QDate::fromString(t.checkIn, "yyyy-MM-dd");
            QDate co = QDate::fromString(t.checkOut, "yyyy-MM-dd");
            map["malam"] = ci.isValid() && co.isValid() ? ci.daysTo(co) : 0;

            Room* r = findRoom(t.idRoom);
            map["nomorKamar"] = r ? r->nomorKamar : "Unknown";
            list.append(map);
        }
    }
    return list;
}

bool HotelBackend::processTransaction(int id, const QString& newStatus) {
    for(auto& t : transactions) {
        if(t.id == id) {
            t.status = newStatus;
            if(newStatus == "Rejected") {
                Room* r = findRoom(t.idRoom);
                if(r) r->status = AVAILABLE; // Kembalikan status kamar
            }
            saveData();
            checkAutoCheckout();
            emit notify("Status transaksi diubah menjadi " + newStatus, false);
            return true;
        }
    }
    return false;
}

// [Syarat 4: File Stream]
void HotelBackend::saveData() {
    // 1. Tulis Kamar
    std::ofstream fileRooms("hotel_rooms.csv");
    if (fileRooms.is_open()) {
        fileRooms << "ID,Nomor,Tipe,Harga,Kapasitas,Status\n";
        for (const auto& r : rooms) {
            fileRooms << r.id << ","
                      << r.nomorKamar.toStdString() << ","
                      << r.tipe.toStdString() << ","
                      << r.harga << ","
                      << r.kapasitas << ","
                      << static_cast<int>(r.status) << "\n";
        }
        fileRooms.close();
    }

    // 2. Tulis Transaksi dengan field Check-In & Check-Out baru
    std::ofstream fileTx("hotel_transactions.csv");
    if (fileTx.is_open()) {
        fileTx << "ID,IDUser,IDRoom,Total,CheckIn,CheckOut,Status\n";
        for (const auto& t : transactions) {
            fileTx << t.id << ","
                   << t.idUser<< ","
                   << t.idRoom << ","
                   << t.totalBiaya << ","
                   << t.checkIn.toStdString() << ","
                   << t.checkOut.toStdString() << ","
                   << t.status.toStdString()
                   << "\n";
        }
        fileTx.close();
        qDebug() << "File Transaksi CSV berhasil diperbarui otomatis!";
    } else {
        qDebug()<<"Gak bisa Bro";
    }
}

void HotelBackend::loadData() {
    // 1. Baca Kamar
    std::ifstream fileRooms("hotel_rooms.csv");
    rooms.clear();
    if (fileRooms.is_open()) {
        std::string line;
        bool firstLine = true;
        while (std::getline(fileRooms, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> kolom;
            while (std::getline(ss, item, ',')) {
                kolom.push_back(item);
            }
            if (kolom.size() == 6) {
                try {
                    rooms.push_back(
                        Room(std::stoi(kolom[0]),
                        QString::fromStdString(kolom[1]),
                        QString::fromStdString(kolom[2]),
                        std::stod(kolom[3]),
                        std::stoi(kolom[4]),
                        static_cast<RoomStatus>(std::stoi(kolom[5])
                        )
                    )
                );
            } catch (...) {}
        }
    }
    fileRooms.close();
    }

    if (rooms.empty()) {
        rooms.push_back(Room(1, "101", "Standard", 500000, 2, AVAILABLE));
        rooms.push_back(Room(2, "102", "Deluxe", 800000, 2, AVAILABLE));
        rooms.push_back(Room(3, "201", "Suite", 1500000, 4, AVAILABLE));
        saveData();
    }

    // 2. Baca Transaksi
    std::ifstream fileTx("hotel_transactions.csv");
    transactions.clear();
    if (fileTx.is_open()) {
        std::string line; bool firstLine = true;

        while (std::getline(fileTx, line)) {

            if (firstLine) {
                firstLine = false;
                continue;
            }

            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> kolom;

            while (std::getline(ss, item, ',')) {
                kolom.push_back(item);
            }

            if (kolom.size() == 7) {
                try {
                    transactions.push_back(
                        Transaction(std::stoi(kolom[0]),
                        std::stoi(kolom[1]),
                        std::stoi(kolom[2]),
                        std::stod(kolom[3]),
                        QString::fromStdString(kolom[4]),
                        QString::fromStdString(kolom[5]),
                        QString::fromStdString(kolom[6])));
                } catch (...) {}
            }
        }
        fileTx.close();
    }
    checkAutoCheckout(); // Jalankan pengecekan otomatis pasca memuat data
}

void HotelBackend::loadOtomatisCSVUser() {
    users.clear(); // Bersihkan vektor sebelum dimuat ulang untuk mencegah duplikasi

    std::ifstream file("users_data.csv");

    // Jika file tidak bisa dibuka (mungkin belum ada), keluar dari fungsi
    // sehingga vektor `users` tetap empty() dan akan memicu seeder di konstruktor
    if (!file.is_open()) {
        return;
    }

    std::string line;
    bool isHeader = true; // Flag untuk melewatkan baris pertama (Header CSV)

    while (std::getline(file, line)) {
        // Lewati baris header: "ID,Nama,Username,Password,Role,Status"
        if (isHeader) {
            isHeader = false;
            continue;
        }

        // Lewati baris kosong jika ada
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, namaStr, usernameStr, passwordStr, roleStr, statusStr;

        // Pisahkan teks berdasarkan delimiter koma ','
        std::getline(ss, idStr, ',');
        std::getline(ss, namaStr, ',');
        std::getline(ss, usernameStr, ',');
        std::getline(ss, passwordStr, ',');
        std::getline(ss, roleStr, ',');
        std::getline(ss, statusStr, ',');

        // Konversi tipe data dari std::string ke tipe data asli
        try {
            int id = std::stoi(idStr);
            Role role = static_cast<Role>(std::stoi(roleStr));
            UserStatus status = static_cast<UserStatus>(std::stoi(statusStr));

            // Konversi dari std::string ke QString lalu masukkan ke vektor
            users.push_back(User(id,
                                 QString::fromStdString(namaStr),
                                 QString::fromStdString(usernameStr),
                                 QString::fromStdString(passwordStr),
                                 role,
                                 status));
        } catch (const std::exception& e) {
            // Lanjutkan loop jika ada baris data yang cacat / tidak valid
            continue;
        }
    }

    file.close();
}


// Helpers
Room* HotelBackend::findRoom(int id) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [id](const Room& r) { return r.id == id; });
    return (it != rooms.end()) ? &(*it) : nullptr;
}

Room* HotelBackend::findRoom(const QString& nomorKamar) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [&nomorKamar](const Room& r) { return r.nomorKamar == nomorKamar; });
    return (it != rooms.end()) ? &(*it) : nullptr;
}

QString HotelBackend::statusToString(RoomStatus status) {
    switch(status) {
    case AVAILABLE: return "Available";
    case BOOKED: return "Booked";
    case MAINTENANCE: return "Maintenance";
    default: return "Unknown";
    }
}

QString HotelBackend::currentUserName() const { return currentUser ? currentUser->nama : ""; }
QString HotelBackend::currentUserRole() const { return currentUser && currentUser->role == ADMIN ? "ADMIN" : "USER"; }