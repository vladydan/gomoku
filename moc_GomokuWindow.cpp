/****************************************************************************
** Meta object code from reading C++ file 'GomokuWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "includes/GomokuWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GomokuWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GomokuWindow_t {
    QByteArrayData data[10];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GomokuWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GomokuWindow_t qt_meta_stringdata_GomokuWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GomokuWindow"
QT_MOC_LITERAL(1, 13, 35), // "on_actionBack_to_the_menu_tri..."
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 20), // "on_pvpButton_clicked"
QT_MOC_LITERAL(4, 71, 21), // "on_exitButton_clicked"
QT_MOC_LITERAL(5, 93, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(6, 117, 25), // "on_actionReplay_triggered"
QT_MOC_LITERAL(7, 143, 27), // "on_doubleTrois_stateChanged"
QT_MOC_LITERAL(8, 171, 4), // "arg1"
QT_MOC_LITERAL(9, 176, 27) // "on_cinqCassble_stateChanged"

    },
    "GomokuWindow\0on_actionBack_to_the_menu_triggered\0"
    "\0on_pvpButton_clicked\0on_exitButton_clicked\0"
    "on_actionExit_triggered\0"
    "on_actionReplay_triggered\0"
    "on_doubleTrois_stateChanged\0arg1\0"
    "on_cinqCassble_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GomokuWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    1,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void GomokuWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GomokuWindow *_t = static_cast<GomokuWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionBack_to_the_menu_triggered(); break;
        case 1: _t->on_pvpButton_clicked(); break;
        case 2: _t->on_exitButton_clicked(); break;
        case 3: _t->on_actionExit_triggered(); break;
        case 4: _t->on_actionReplay_triggered(); break;
        case 5: _t->on_doubleTrois_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_cinqCassble_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GomokuWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GomokuWindow.data,
      qt_meta_data_GomokuWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GomokuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GomokuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GomokuWindow.stringdata0))
        return static_cast<void*>(const_cast< GomokuWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GomokuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
