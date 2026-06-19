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
    // Data Dummy Awal
    users.push_back(User(1, "Administrator", "admin", "admin", ADMIN));
    users.push_back(User(2, "Budi Santoso", "budi", "user", USER));

    rooms.push_back(Room(1, "101", "Standard", 500000, 2, AVAILABLE));
    rooms.push_back(Room(2, "102", "Deluxe", 800000, 2, AVAILABLE));
    rooms.push_back(Room(3, "201", "Suite", 1500000, 4, BOOKED));

    transactions.push_back(Transaction(1, 2, 3, 2, 3000000, "Pending"));
}

bool HotelBackend::login(const QString& username, const QString& password) {
    // [Syarat 5: Iterator]
    for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->username == username && it->password == password) {
            currentUser = &(*it); // [Syarat 12: Pointer]
            emit userChanged();
            emit notify("Login Berhasil! Selamat datang " + currentUser->username, false);
            return true;
        }
    }
    emit notify("Username atau Password salah!", true);
    return false;
}

void HotelBackend::logout() {
    currentUser = nullptr;
    emit userChanged();
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
        emit notify("Kamar berhasil ditambahkan!", false);
        return true;
    } catch (const std::exception& e) {
        emit notify(e.what(), true);
        return false;
    }
}

bool HotelBackend::deleteRoom(int id) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [id](const Room& r) { return r.id == id; });
    if (it != rooms.end()) {
        rooms.erase(it);
        emit notify("Kamar berhasil dihapus!", false);
        return true;
    }
    emit notify("Kamar tidak ditemukan!", true);
    return false;
}

// --- USER FEATURES ---
QVariantList HotelBackend::getAvailableRooms() {
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
        map["id"] = r.id; map["nomorKamar"] = r.nomorKamar; map["tipe"] = r.tipe; map["harga"] = r.harga;
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
            map["id"] = r.id; map["nomorKamar"] = r.nomorKamar; map["tipe"] = r.tipe; map["harga"] = r.harga;
            list.append(map);
        }
    }
    return list;
}

bool HotelBackend::bookRoom(int roomId, int malam) {
    try {
        if (!currentUser || currentUser->role != USER) throw HotelException("Hanya user yang dapat booking!");
        if (malam <= 0) throw HotelException("Jumlah malam minimal 1!");

        Room* room = findRoomById(roomId);
        if (!room) throw HotelException("Kamar tidak ditemukan!");
        if (room->status != AVAILABLE) throw HotelException("Kamar tidak tersedia!");

        double total = calculateTotal(malam, room->harga);
        room->status = BOOKED;

        int newTxId = transactions.empty() ? 1 : transactions.back().id + 1;
        transactions.push_back(Transaction(newTxId, currentUser->id, room->id, malam, total, "Pending"));

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
        map["id"] = t.id; map["status"] = t.status; map["total"] = t.totalBiaya; map["malam"] = t.jumlahMalam;
        Room* r = findRoomById(t.idRoom);
        map["nomorKamar"] = r ? r->nomorKamar : "Unknown";
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
            map["id"] = t.id; map["status"] = t.status; map["total"] = t.totalBiaya;
            Room* r = findRoomById(t.idRoom);
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
                Room* r = findRoomById(t.idRoom);
                if(r) r->status = AVAILABLE; // Kembalikan status kamar
            }
            emit notify("Status transaksi diubah menjadi " + newStatus, false);
            return true;
        }
    }
    return false;
}

// [Syarat 4: File Stream]
void HotelBackend::saveData() {
    std::ofstream file("hotel_data.csv");
    if (file.is_open()) {
        file << "ID,Nomor,Tipe,Harga,Kapasitas,Status\n";
        for (const auto& r : rooms) {
            file << r.id << "," << r.nomorKamar.toStdString() << ","
                 << r.tipe.toStdString() << "," << r.harga << ","
                 << r.kapasitas << "," << static_cast<int>(r.status) << "\n";
        }
        file.close();
        emit notify("Data berhasil disimpan ke file CSV!", false);
    } else {
        emit notify("Gagal menyimpan file!", true);
    }
}

void HotelBackend::loadData() {
    std::ifstream file("hotel_data.csv");
    if (!file.is_open()) {
        emit notify("File data tidak ditemukan, menggunakan data default.", true);
        return;
    }

    rooms.clear(); // Bersihkan data default sebelum memuat dari file
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false; // Lewati baris header CSV
            continue;
        }

        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Memisahkan teks berdasarkan koma (Delimiter CSV)
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        // Pastikan kolom sesuai dengan format simpan (6 kolom)
        if (tokens.size() >= 6) {
            try {
                // Konversi string kembali ke tipe aslinya
                int id = std::stoi(tokens[0]);
                QString nomor = QString::fromStdString(tokens[1]);
                QString tipe = QString::fromStdString(tokens[2]);
                double harga = std::stod(tokens[3]);
                int kapasitas = std::stoi(tokens[4]);
                RoomStatus status = static_cast<RoomStatus>(std::stoi(tokens[5]));

                rooms.push_back(Room(id, nomor, tipe, harga, kapasitas, status));
            } catch (const std::exception& e) {
                // Syarat 7: Menangani error parsing tanpa membuat aplikasi crash
                std::cerr << "Error parsing CSV pada baris: " << line << " | " << e.what() << std::endl;
            }
        }
    }
    file.close();
    emit notify("Data berhasil dimuat dari file CSV!", false);
}

// Helpers
Room* HotelBackend::findRoomById(int id) {
    for(auto& r : rooms) { if(r.id == id) return &r; }
    return nullptr;
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