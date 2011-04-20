/****************************************************************************
** Meta object code from reading C++ file 'SoundsGUI.h'
**
** Created: Wed 20. Apr 12:17:15 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SoundsGUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SoundsGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dial[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_dial[] = {
    "dial\0"
};

const QMetaObject dial::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dial,
      qt_meta_data_dial, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dial::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dial))
        return static_cast<void*>(const_cast< dial*>(this));
    return QDialog::qt_metacast(_clname);
}

int dial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SoundsGUI[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      18,   10,   10,   10, 0x08,
      25,   10,   10,   10, 0x08,
      45,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SoundsGUI[] = {
    "SoundsGUI\0\0stop()\0play()\0contextMenu(QPoint)\0"
    "createLib()\0"
};

const QMetaObject SoundsGUI::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SoundsGUI,
      qt_meta_data_SoundsGUI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SoundsGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SoundsGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SoundsGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SoundsGUI))
        return static_cast<void*>(const_cast< SoundsGUI*>(this));
    return QDialog::qt_metacast(_clname);
}

int SoundsGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stop(); break;
        case 1: play(); break;
        case 2: contextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: createLib(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
