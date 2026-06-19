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
        "userChanged",
        "",
        "notify",
        "message",
        "isError",
        "login",
        "username",
        "password",
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
        "deleteRoom",
        "id",
        "getAllTransactions",
        "processTransaction",
        "newStatus",
        "getAvailableRooms",
        "getAvailableRoomsSortedByPrice",
        "searchRooms",
        "keyword",
        "bookRoom",
        "roomId",
        "malam",
        "getMyTransactions",
        "saveData",
        "loadData",
        "currentUserName",
        "currentUserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'userChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'notify'
        QtMocHelpers::SignalData<void(QString, bool)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 }, { QMetaType::Bool, 5 },
        }}),
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getAdminStats'
        QtMocHelpers::MethodData<QVariantMap()>(10, 2, QMC::AccessPublic, 0x80000000 | 11),
        // Method 'getAllRooms'
        QtMocHelpers::MethodData<QVariantList()>(12, 2, QMC::AccessPublic, 0x80000000 | 13),
        // Method 'addRoom'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, double, int)>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 15 }, { QMetaType::QString, 16 }, { QMetaType::Double, 17 }, { QMetaType::Int, 18 },
        }}),
        // Method 'deleteRoom'
        QtMocHelpers::MethodData<bool(int)>(19, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'getAllTransactions'
        QtMocHelpers::MethodData<QVariantList()>(21, 2, QMC::AccessPublic, 0x80000000 | 13),
        // Method 'processTransaction'
        QtMocHelpers::MethodData<bool(int, const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 23 },
        }}),
        // Method 'getAvailableRooms'
        QtMocHelpers::MethodData<QVariantList()>(24, 2, QMC::AccessPublic, 0x80000000 | 13),
        // Method 'getAvailableRoomsSortedByPrice'
        QtMocHelpers::MethodData<QVariantList()>(25, 2, QMC::AccessPublic, 0x80000000 | 13),
        // Method 'searchRooms'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(26, 2, QMC::AccessPublic, 0x80000000 | 13, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'bookRoom'
        QtMocHelpers::MethodData<bool(int, int)>(28, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 29 }, { QMetaType::Int, 30 },
        }}),
        // Method 'getMyTransactions'
        QtMocHelpers::MethodData<QVariantList()>(31, 2, QMC::AccessPublic, 0x80000000 | 13),
        // Method 'saveData'
        QtMocHelpers::MethodData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadData'
        QtMocHelpers::MethodData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'currentUserName'
        QtMocHelpers::MethodData<QString() const>(34, 2, QMC::AccessPublic, QMetaType::QString),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentUserName'
        QtMocHelpers::PropertyData<QString>(34, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'currentUserRole'
        QtMocHelpers::PropertyData<QString>(35, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HotelBackend, qt_meta_tag_ZN12HotelBackendE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
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
        case 3: _t->logout(); break;
        case 4: { QVariantMap _r = _t->getAdminStats();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->getAllRooms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->addRoom((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->deleteRoom((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->getAllTransactions();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->processTransaction((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->getAvailableRooms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->getAvailableRoomsSortedByPrice();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->searchRooms((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->bookRoom((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->getMyTransactions();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->saveData(); break;
        case 16: _t->loadData(); break;
        case 17: { QString _r = _t->currentUserName();
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
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
