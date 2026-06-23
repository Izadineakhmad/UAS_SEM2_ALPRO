/****************************************************************************
** Meta object code from reading C++ file 'hotelbackend.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../hotelbackend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hotelbackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12HotelBackendE_t {};
} // unnamed namespace

template <> constexpr inline auto HotelBackend::qt_create_metaobjectdata<qt_meta_tag_ZN12HotelBackendE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HotelBackend",
        "QML.Element",
        "HotelApp",
        "QML.Singleton",
        "true",
        "userChanged",
        "",
        "notify",
        "message",
        "isError",
        "login",
        "username",
        "password",
        "registerUser",
        "name",
        "logout",
        "getAdminStats",
        "QVariantMap",
        "getAllRooms",
        "QVariantList",
        "addRoom",
        "nomor",
        "tipe",
        "harga",
        "kapasitas",
        "editRoom",
        "id",
        "status",
        "deleteRoom",
        "getAllTransactions",
        "processTransaction",
        "newStatus",
        "getAllUsers",
        "addUser",
        "roleInt",
        "statusInt",
        "editUser",
        "deleteUser",
        "approveUser",
        "getAvailableRooms",
        "getAvailableRoomsSortedByPrice",
        "searchRooms",
        "keyword",
        "bookRoom",
        "roomType",
        "checkInDate",
        "checkOutDate",
        "getMyTransactions",
        "saveData",
        "loadData",
        "checkAutoCheckout",
        "saveUsersToCSV",
        "loadOtomatisCSVUser",
        "currentUserName",
        "currentUserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'userChanged'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'notify'
        QtMocHelpers::SignalData<void(QString, bool)>(7, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 }, { QMetaType::Bool, 9 },
        }}),
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(10, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'registerUser'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &)>(13, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 14 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(15, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'getAdminStats'
        QtMocHelpers::MethodData<QVariantMap()>(16, 6, QMC::AccessPublic, 0x80000000 | 17),
        // Method 'getAllRooms'
        QtMocHelpers::MethodData<QVariantList()>(18, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'addRoom'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, double, int)>(20, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 21 }, { QMetaType::QString, 22 }, { QMetaType::Double, 23 }, { QMetaType::Int, 24 },
        }}),
        // Method 'editRoom'
        QtMocHelpers::MethodData<bool(int, const QString &, const QString &, double, int, int)>(25, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 }, { QMetaType::QString, 21 }, { QMetaType::QString, 22 }, { QMetaType::Double, 23 },
            { QMetaType::Int, 27 }, { QMetaType::Int, 24 },
        }}),
        // Method 'deleteRoom'
        QtMocHelpers::MethodData<bool(int)>(28, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 },
        }}),
        // Method 'getAllTransactions'
        QtMocHelpers::MethodData<QVariantList()>(29, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'processTransaction'
        QtMocHelpers::MethodData<bool(int, const QString &)>(30, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 }, { QMetaType::QString, 31 },
        }}),
        // Method 'getAllUsers'
        QtMocHelpers::MethodData<QVariantList()>(32, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'addUser'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, int, int)>(33, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 14 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 }, { QMetaType::Int, 34 },
            { QMetaType::Int, 35 },
        }}),
        // Method 'editUser'
        QtMocHelpers::MethodData<bool(int, const QString &, const QString &, const QString &, int, int)>(36, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 }, { QMetaType::QString, 14 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
            { QMetaType::Int, 34 }, { QMetaType::Int, 35 },
        }}),
        // Method 'deleteUser'
        QtMocHelpers::MethodData<bool(int)>(37, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 },
        }}),
        // Method 'approveUser'
        QtMocHelpers::MethodData<bool(int)>(38, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 26 },
        }}),
        // Method 'getAvailableRooms'
        QtMocHelpers::MethodData<QVariantList()>(39, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'getAvailableRoomsSortedByPrice'
        QtMocHelpers::MethodData<QVariantList()>(40, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'searchRooms'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(41, 6, QMC::AccessPublic, 0x80000000 | 19, {{
            { QMetaType::QString, 42 },
        }}),
        // Method 'bookRoom'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &)>(43, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 44 }, { QMetaType::QString, 45 }, { QMetaType::QString, 46 },
        }}),
        // Method 'getMyTransactions'
        QtMocHelpers::MethodData<QVariantList()>(47, 6, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'saveData'
        QtMocHelpers::MethodData<void()>(48, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadData'
        QtMocHelpers::MethodData<void()>(49, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'checkAutoCheckout'
        QtMocHelpers::MethodData<void()>(50, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveUsersToCSV'
        QtMocHelpers::MethodData<void()>(51, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadOtomatisCSVUser'
        QtMocHelpers::MethodData<void()>(52, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'currentUserName'
        QtMocHelpers::MethodData<QString() const>(53, 6, QMC::AccessPublic, QMetaType::QString),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentUserName'
        QtMocHelpers::PropertyData<QString>(53, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'currentUserRole'
        QtMocHelpers::PropertyData<QString>(54, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<HotelBackend, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject HotelBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HotelBackendE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HotelBackendE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12HotelBackendE_t>.metaTypes,
    nullptr
} };

void HotelBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HotelBackend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->userChanged(); break;
        case 1: _t->notify((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: { bool _r = _t->login((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->registerUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->logout(); break;
        case 5: { QVariantMap _r = _t->getAdminStats();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->getAllRooms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->addRoom((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->editRoom((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->deleteRoom((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->getAllTransactions();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->processTransaction((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->getAllUsers();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->addUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->editUser((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->deleteUser((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->approveUser((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->getAvailableRooms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->getAvailableRoomsSortedByPrice();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantList _r = _t->searchRooms((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->bookRoom((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 21: { QVariantList _r = _t->getMyTransactions();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->saveData(); break;
        case 23: _t->loadData(); break;
        case 24: _t->checkAutoCheckout(); break;
        case 25: _t->saveUsersToCSV(); break;
        case 26: _t->loadOtomatisCSVUser(); break;
        case 27: { QString _r = _t->currentUserName();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (HotelBackend::*)()>(_a, &HotelBackend::userChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (HotelBackend::*)(QString , bool )>(_a, &HotelBackend::notify, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->currentUserName(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->currentUserRole(); break;
        default: break;
        }
    }
}

const QMetaObject *HotelBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotelBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HotelBackendE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HotelBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HotelBackend::userChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HotelBackend::notify(QString _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
