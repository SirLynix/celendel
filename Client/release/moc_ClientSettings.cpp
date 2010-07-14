/****************************************************************************
** Meta object code from reading C++ file 'ClientSettings.h'
**
** Created: Wed 14. Jul 18:28:37 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientSettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientSettings[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      21,   15,   15,   15, 0x08,
      31,   15,   15,   15, 0x08,
      43,   15,   15,   15, 0x08,
      59,   15,   15,   15, 0x08,
      77,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientSettings[] = {
    "ClientSettings\0\0ok()\0openCSS()\0"
    "selectCSS()\0openInterface()\0"
    "selectInterface()\0saveInterface()\0"
};

const QMetaObject ClientSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClientSettings,
      qt_meta_data_ClientSettings, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSettings))
        return static_cast<void*>(const_cast< ClientSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClientSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ok(); break;
        case 1: openCSS(); break;
        case 2: selectCSS(); break;
        case 3: openInterface(); break;
        case 4: selectInterface(); break;
        case 5: saveInterface(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
