#ifndef HOTELBACKEND_H
#define HOTELBACKEND_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <vector>
#include <list>
#include <string>

// [Syarat 11: Namespace]
namespace HotelCore {

// [Syarat 12: Struct]
struct Date {
    int day, month, year;
    QString toString() const {
        return QString("%1/%2/%3").arg(day).arg(month).arg(year);
    }
};

enum Role { ADMIN, USER };
enum RoomStatus { AVAILABLE, BOOKED, MAINTENANCE };

class User {
public:
    int id;
    QString nama, username, password;
    Role role;
    User(int i, QString n, QString u, QString p, Role r) : id(i), nama(n), username(u), password(p), role(r) {}
};

class Room {
public:
    int id;
    QString nomorKamar, tipe;
    double harga;
    int kapasitas;
    RoomStatus status;
    Room(int i, QString no, QString t, double h, int k, RoomStatus s) : id(i), nomorKamar(no), tipe(t), harga(h), kapasitas(k), status(s) {}
};

class Transaction {
public:
    int id, idUser, idRoom;
    int jumlahMalam;
    double totalBiaya;
    QString status; // Pending, Approved, Rejected
    Transaction(int i, int iu, int ir, int jm, double tot, QString st) : id(i), idUser(iu), idRoom(ir), jumlahMalam(jm), totalBiaya(tot), status(st) {}
};
}

// Wrapper Class untuk QML
class HotelBackend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentUserName READ currentUserName NOTIFY userChanged)
    Q_PROPERTY(QString currentUserRole READ currentUserRole NOTIFY userChanged)

public:
    explicit HotelBackend(QObject *parent = nullptr);

    // --- AUTENTIKASI ---
    Q_INVOKABLE bool login(const QString& username, const QString& password);
    Q_INVOKABLE void logout();

    // --- FITUR ADMIN ---
    Q_INVOKABLE QVariantMap getAdminStats(); // [Kriteria: Dashboard Statistik]
    Q_INVOKABLE QVariantList getAllRooms();
    Q_INVOKABLE bool addRoom(const QString& nomor, const QString& tipe, double harga, int kapasitas);
    Q_INVOKABLE bool deleteRoom(int id); // [Kriteria: Konfirmasi Hapus Data ada di QML]
    Q_INVOKABLE QVariantList getAllTransactions();
    Q_INVOKABLE bool processTransaction(int id, const QString& newStatus); // Approve/Reject

    // --- FITUR USER ---
    Q_INVOKABLE QVariantList getAvailableRooms();
    Q_INVOKABLE QVariantList getAvailableRoomsSortedByPrice(); // [Kriteria: Sorting]
    Q_INVOKABLE QVariantList searchRooms(const QString& keyword); // [Kriteria: Searching]
    Q_INVOKABLE bool bookRoom(int roomId, int malam);
    Q_INVOKABLE QVariantList getMyTransactions();

    // --- SISTEM FILE ---
    Q_INVOKABLE void saveData(); // [Syarat 4: File Stream]
    Q_INVOKABLE void loadData();

    Q_INVOKABLE QString currentUserName() const;
    QString currentUserRole() const;

signals:
    void userChanged();
    void notify(QString message, bool isError);

private:
    // [Syarat 6: Vector dan List STL]
    std::vector<HotelCore::User> users;
    std::vector<HotelCore::Room> rooms;
    std::list<HotelCore::Transaction> transactions;

    HotelCore::User* currentUser = nullptr;

    // Helper functions
    HotelCore::Room* findRoomById(int id);
    QString statusToString(HotelCore::RoomStatus status);
};

#endif // HOTELBACKEND_H