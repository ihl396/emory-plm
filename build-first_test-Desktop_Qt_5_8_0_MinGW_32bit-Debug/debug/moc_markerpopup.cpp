/****************************************************************************
** Meta object code from reading C++ file 'markerpopup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/markerpopup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'markerpopup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MarkerPopup_t {
    QByteArrayData data[9];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MarkerPopup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MarkerPopup_t qt_meta_stringdata_MarkerPopup = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MarkerPopup"
QT_MOC_LITERAL(1, 12, 12), // "ColorChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "markerDataSend"
QT_MOC_LITERAL(4, 41, 6), // "setCol"
QT_MOC_LITERAL(5, 48, 11), // "strListData"
QT_MOC_LITERAL(6, 60, 13), // "getMarkerName"
QT_MOC_LITERAL(7, 74, 10), // "setTagName"
QT_MOC_LITERAL(8, 85, 5) // "color"

    },
    "MarkerPopup\0ColorChanged\0\0markerDataSend\0"
    "setCol\0strListData\0getMarkerName\0"
    "setTagName\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarkerPopup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       1,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   50,    2, 0x0a /* Public */,
       5,    0,   51,    2, 0x0a /* Public */,
       6,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // properties: name, type, flags
       8, QMetaType::QColor, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void MarkerPopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarkerPopup *_t = static_cast<MarkerPopup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->markerDataSend((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->setCol(); break;
        case 3: _t->strListData(); break;
        case 4: _t->getMarkerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setTagName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MarkerPopup::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarkerPopup::ColorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MarkerPopup::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarkerPopup::markerDataSend)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        MarkerPopup *_t = static_cast<MarkerPopup *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject MarkerPopup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MarkerPopup.data,
      qt_meta_data_MarkerPopup,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MarkerPopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarkerPopup::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MarkerPopup.stringdata0))
        return static_cast<void*>(const_cast< MarkerPopup*>(this));
    return QDialog::qt_metacast(_clname);
}

int MarkerPopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MarkerPopup::ColorChanged(QColor _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MarkerPopup::markerDataSend(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
