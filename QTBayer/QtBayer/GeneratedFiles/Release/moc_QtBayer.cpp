/****************************************************************************
** Meta object code from reading C++ file 'QtBayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtBayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtBayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtBayer_t {
    QByteArrayData data[15];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtBayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtBayer_t qt_meta_stringdata_QtBayer = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QtBayer"
QT_MOC_LITERAL(1, 8, 12), // "LoadRawImage"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "serial"
QT_MOC_LITERAL(4, 29, 10), // "pa_section"
QT_MOC_LITERAL(5, 40, 6), // "pa_for"
QT_MOC_LITERAL(6, 47, 11), // "serial_save"
QT_MOC_LITERAL(7, 59, 12), // "section_save"
QT_MOC_LITERAL(8, 72, 8), // "for_save"
QT_MOC_LITERAL(9, 81, 9), // "inputzoom"
QT_MOC_LITERAL(10, 91, 10), // "serialzoom"
QT_MOC_LITERAL(11, 102, 11), // "sectionzoom"
QT_MOC_LITERAL(12, 114, 7), // "forzoom"
QT_MOC_LITERAL(13, 122, 9), // "show_info"
QT_MOC_LITERAL(14, 132, 11) // "check_round"

    },
    "QtBayer\0LoadRawImage\0\0serial\0pa_section\0"
    "pa_for\0serial_save\0section_save\0"
    "for_save\0inputzoom\0serialzoom\0sectionzoom\0"
    "forzoom\0show_info\0check_round"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtBayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtBayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtBayer *_t = static_cast<QtBayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LoadRawImage(); break;
        case 1: _t->serial(); break;
        case 2: _t->pa_section(); break;
        case 3: _t->pa_for(); break;
        case 4: _t->serial_save(); break;
        case 5: _t->section_save(); break;
        case 6: _t->for_save(); break;
        case 7: _t->inputzoom(); break;
        case 8: _t->serialzoom(); break;
        case 9: _t->sectionzoom(); break;
        case 10: _t->forzoom(); break;
        case 11: _t->show_info(); break;
        case 12: _t->check_round(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QtBayer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtBayer.data,
      qt_meta_data_QtBayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtBayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtBayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtBayer.stringdata0))
        return static_cast<void*>(const_cast< QtBayer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtBayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
