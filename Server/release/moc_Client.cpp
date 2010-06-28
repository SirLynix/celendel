/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created: Mon 28. Jun 15:33:16 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      30,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   45,    7,    7, 0x0a,
      62,   45,    7,    7, 0x0a,
      76,    7,    7,    7, 0x0a,
      84,    7,    7,    7, 0x08,
      96,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0dataReceived(Packet*)\0"
    "disconnected()\0pa\0send(Packet*)\0"
    "send(Packet&)\0flush()\0readyRead()\0"
    "slot_disconnected()\0"
};

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataReceived((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 1: disconnected(); break;
        case 2: send((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 3: send((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 4: flush(); break;
        case 5: readyRead(); break;
        case 6: slot_disconnected(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Client::dataReceived(Packet * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Client::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
