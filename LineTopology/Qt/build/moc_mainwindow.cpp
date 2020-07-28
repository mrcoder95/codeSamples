/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../LineTopology/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "on_start_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 23), // "on_clearconsole_clicked"
QT_MOC_LITERAL(4, 53, 8), // "main_run"
QT_MOC_LITERAL(5, 62, 27), // "on_ElementX_editingFinished"
QT_MOC_LITERAL(6, 90, 27), // "on_ElementY_editingFinished"
QT_MOC_LITERAL(7, 118, 26), // "on_volfrac_editingFinished"
QT_MOC_LITERAL(8, 145, 24), // "on_penal_editingFinished"
QT_MOC_LITERAL(9, 170, 23), // "on_rmin_editingFinished"
QT_MOC_LITERAL(10, 194, 24), // "on_E_Val_editingFinished"
QT_MOC_LITERAL(11, 219, 22), // "on_saveImage_activated"
QT_MOC_LITERAL(12, 242, 4), // "arg1"
QT_MOC_LITERAL(13, 247, 15), // "on_stop_clicked"
QT_MOC_LITERAL(14, 263, 29), // "on_imageScale_editingFinished"
QT_MOC_LITERAL(15, 293, 30), // "ReceiveStatusFromSaveImageForm"
QT_MOC_LITERAL(16, 324, 3), // "arg"
QT_MOC_LITERAL(17, 328, 11), // "updateImage"
QT_MOC_LITERAL(18, 340, 3) // "img"

    },
    "MainWindow\0on_start_clicked\0\0"
    "on_clearconsole_clicked\0main_run\0"
    "on_ElementX_editingFinished\0"
    "on_ElementY_editingFinished\0"
    "on_volfrac_editingFinished\0"
    "on_penal_editingFinished\0"
    "on_rmin_editingFinished\0"
    "on_E_Val_editingFinished\0"
    "on_saveImage_activated\0arg1\0on_stop_clicked\0"
    "on_imageScale_editingFinished\0"
    "ReceiveStatusFromSaveImageForm\0arg\0"
    "updateImage\0img"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    1,   98,    2, 0x0a /* Public */,
      17,    1,  101,    2, 0x0a /* Public */,

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
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::QImage,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_start_clicked(); break;
        case 1: _t->on_clearconsole_clicked(); break;
        case 2: _t->main_run(); break;
        case 3: _t->on_ElementX_editingFinished(); break;
        case 4: _t->on_ElementY_editingFinished(); break;
        case 5: _t->on_volfrac_editingFinished(); break;
        case 6: _t->on_penal_editingFinished(); break;
        case 7: _t->on_rmin_editingFinished(); break;
        case 8: _t->on_E_Val_editingFinished(); break;
        case 9: _t->on_saveImage_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_stop_clicked(); break;
        case 11: _t->on_imageScale_editingFinished(); break;
        case 12: _t->ReceiveStatusFromSaveImageForm((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 13: _t->updateImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
