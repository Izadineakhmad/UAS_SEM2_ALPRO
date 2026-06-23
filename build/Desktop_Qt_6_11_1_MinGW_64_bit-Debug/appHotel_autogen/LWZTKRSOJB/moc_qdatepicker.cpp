/****************************************************************************
** Meta object code from reading C++ file 'qdatepicker.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../components/QDatePicker/src/qdatepicker.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdatepicker.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11QDatePickerE_t {};
} // unnamed namespace

template <> constexpr inline auto QDatePicker::qt_create_metaobjectdata<qt_meta_tag_ZN11QDatePickerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QDatePicker",
        "localeChanged",
        "",
        "calendarChanged",
        "selectedDateChanged",
        "getLongWeekDaysName",
        "getShortWeekDaysName",
        "getNarrowWeekDaysName",
        "getLongMonthsName",
        "getShortMonthsName",
        "getNarrowMonthsName",
        "getAvailableCalendars",
        "getGridDaysOfMonth",
        "year",
        "month",
        "getCurrentLocalDateString",
        "getCurrentLocalDateTimeString",
        "dateToLocalDateString",
        "day",
        "localeToGregorianDate",
        "localeYear",
        "localeMonth",
        "localeDay",
        "shiftAmountForFirstDayOfWeek",
        "shiftListForFirstdayOfWeek",
        "list",
        "locale",
        "calendar"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'localeChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'calendarChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedDateChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getLongWeekDaysName'
        QtMocHelpers::MethodData<QList<QString>()>(5, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getShortWeekDaysName'
        QtMocHelpers::MethodData<QList<QString>()>(6, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getNarrowWeekDaysName'
        QtMocHelpers::MethodData<QList<QString>()>(7, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getLongMonthsName'
        QtMocHelpers::MethodData<QList<QString>()>(8, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getShortMonthsName'
        QtMocHelpers::MethodData<QList<QString>()>(9, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getNarrowMonthsName'
        QtMocHelpers::MethodData<QList<QString>()>(10, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getAvailableCalendars'
        QtMocHelpers::MethodData<QList<QString>()>(11, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getGridDaysOfMonth'
        QtMocHelpers::MethodData<QList<QString>(int, int)>(12, 2, QMC::AccessPublic, QMetaType::QStringList, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 14 },
        }}),
        // Method 'getCurrentLocalDateString'
        QtMocHelpers::MethodData<QString()>(15, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'getCurrentLocalDateTimeString'
        QtMocHelpers::MethodData<QString()>(16, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'dateToLocalDateString'
        QtMocHelpers::MethodData<QStringList(int, int, int)>(17, 2, QMC::AccessPublic, QMetaType::QStringList, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 14 }, { QMetaType::Int, 18 },
        }}),
        // Method 'localeToGregorianDate'
        QtMocHelpers::MethodData<QDate(int, int, int)>(19, 2, QMC::AccessPublic, QMetaType::QDate, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { QMetaType::Int, 22 },
        }}),
        // Method 'shiftAmountForFirstDayOfWeek'
        QtMocHelpers::MethodData<int()>(23, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'shiftListForFirstdayOfWeek'
        QtMocHelpers::MethodData<QList<QString>(QList<QString>)>(24, 2, QMC::AccessPublic, QMetaType::QStringList, {{
            { QMetaType::QStringList, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'locale'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 0),
        // property 'calendar'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QDatePicker, qt_meta_tag_ZN11QDatePickerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QDatePicker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11QDatePickerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11QDatePickerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11QDatePickerE_t>.metaTypes,
    nullptr
} };

void QDatePicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QDatePicker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->localeChanged(); break;
        case 1: _t->calendarChanged(); break;
        case 2: _t->selectedDateChanged(); break;
        case 3: { QList<QString> _r = _t->getLongWeekDaysName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 4: { QList<QString> _r = _t->getShortWeekDaysName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 5: { QList<QString> _r = _t->getNarrowWeekDaysName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 6: { QList<QString> _r = _t->getLongMonthsName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 7: { QList<QString> _r = _t->getShortMonthsName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 8: { QList<QString> _r = _t->getNarrowMonthsName();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 9: { QList<QString> _r = _t->getAvailableCalendars();
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 10: { QList<QString> _r = _t->getGridDaysOfMonth((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getCurrentLocalDateString();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->getCurrentLocalDateTimeString();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 13: { QStringList _r = _t->dateToLocalDateString((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast<QStringList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QDate _r = _t->localeToGregorianDate((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast<QDate*>(_a[0]) = std::move(_r); }  break;
        case 15: { int _r = _t->shiftAmountForFirstDayOfWeek();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 16: { QList<QString> _r = _t->shiftListForFirstdayOfWeek((*reinterpret_cast<std::add_pointer_t<QList<QString>>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QList<QString>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QDatePicker::*)()>(_a, &QDatePicker::localeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QDatePicker::*)()>(_a, &QDatePicker::calendarChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (QDatePicker::*)()>(_a, &QDatePicker::selectedDateChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->getLocaleText(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->getCalendarText(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLocaleText(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setCalnedarText(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QDatePicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDatePicker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11QDatePickerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QDatePicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
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
void QDatePicker::localeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QDatePicker::calendarChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QDatePicker::selectedDateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
