#ifndef HOTELBACKEND_H
#define HOTELBACKEND_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QDebug>
#include <QDateTime>
#include <QtQml/qqml.h>
#include <vector>
#include <sstream>
#include <list>
#include <string>

// [Syarat 11: Namespace]
namespace HotelCore {

enum Role { ADMIN, USER };
enum RoomStatus { AVAILABLE, BOOKED, MAINTENANCE };
enum UserStatus { PENDING, ACTIVE };

class User {
    public:
        int id;
        QString nama;
        QString username;
        QString password;
        Role role;
        UserStatus status;

        User(int i, QString n, QString u, QString p, Role r, UserStatus s) : id(i), nama(n), username(u), password(p), role(r), status(s) {}
};

class Room {
    public:
        int id;
        QString nomorKamar;
        QString tipe;
        double harga;
        int kapasitas;
        RoomStatus status;
        Room(int i, QString no, QString t, double h, int k, RoomStatus s) : id(i), nomorKamar(no), tipe(t), harga(h), kapasitas(k), status(s)
        {}
};

class Transaction {
    public:
        int id, idUser, idRoom;
        double totalBiaya;
        QString checkIn;
        QString checkOut;
        QString status; // Pending, Approved, Rejected
        Transaction(int i, int iu, int ir, double tot, const QString& ci, const QString& co, const QString& st)
        : id(i), idUser(iu), idRoom(ir), totalBiaya(tot), checkIn(ci), checkOut(co), status(st) {}
    };
}

// Wrapper Class untuk QML
class HotelBackend : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(HotelApp)
    QML_SINGLETON
    Q_PROPERTY(QString currentUserName READ currentUserName NOTIFY userChanged)
    Q_PROPERTY(QString currentUserRole READ currentUserRole NOTIFY userChanged)

public:
    explicit HotelBackend(QObject *parent = nullptr);

    // --- AUTENTIKASI ---
    Q_INVOKABLE bool login(const QString& username, const QString& password);
    Q_INVOKABLE bool registerUser(const QString& name, const QString& username, const QString& password);
    Q_INVOKABLE void logout();

    // --- FITUR ADMIN ---
    Q_INVOKABLE QVariantMap getAdminStats();
    Q_INVOKABLE QVariantList getAllRooms();
    Q_INVOKABLE bool addRoom(const QString& nomor, const QString& tipe, double harga, int kapasitas);
    Q_INVOKABLE bool editRoom(int id, const QString& nomor, const QString& tipe, double harga, int status, int kapasitas);
    Q_INVOKABLE bool deleteRoom(int id);

    // --- FITUR ADMIN TRANSAKSI ---
    Q_INVOKABLE QVariantList getAllTransactions();
    Q_INVOKABLE bool processTransaction(int id, const QString& newStatus);



    // --- FITUR ADMIN CRUD USER ---
    Q_INVOKABLE QVariantList getAllUsers();
    Q_INVOKABLE bool addUser(const QString& name, const QString& username, const QString& password, int roleInt, int statusInt);
    Q_INVOKABLE bool editUser(int id, const QString& name, const QString& username, const QString& password, int roleInt, int statusInt);
    Q_INVOKABLE bool deleteUser(int id);
    Q_INVOKABLE bool approveUser(int id);

    // --- FITUR USER ---
    Q_INVOKABLE QVariantList getAvailableRooms();
    Q_INVOKABLE QVariantList getAvailableRoomsSortedByPrice(); 
    Q_INVOKABLE QVariantList searchRooms(const QString& keyword); 
    Q_INVOKABLE bool bookRoom(const QString& roomType, const QString& checkInDate, const QString& checkOutDate);
    Q_INVOKABLE QVariantList getMyTransactions();

    // --- SISTEM FILE ---
    Q_INVOKABLE void saveData(); // [Syarat 4: File Stream]
    Q_INVOKABLE void loadData();
    Q_INVOKABLE void checkAutoCheckout();
    Q_INVOKABLE void saveUsersToCSV();
    Q_INVOKABLE void loadOtomatisCSVUser();

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
    HotelCore::Room* findRoom(int id);
    HotelCore::Room* findRoom(const QString& nomorKamar);
    QString statusToString(HotelCore::RoomStatus status);
};

#endif // HOTELBACKEND_H