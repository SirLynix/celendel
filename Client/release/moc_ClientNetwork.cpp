/****************************************************************************
** Meta object code from reading C++ file 'ClientNetwork.h'
**
** Created: Mon 28. Jun 19:14:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientNetwork.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientNetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientNetwork[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      39,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   60,   14,   14, 0x0a,
     100,   97,   14,   14, 0x2a,
     114,   97,   14,   14, 0x0a,
     138,  128,   14,   14, 0x0a,
     162,   14,   14,   14, 0x0a,
     176,   14,  169,   14, 0x0a,
     186,   14,   14,   14, 0x0a,
     194,   14,   14,   14, 0x08,
     206,   14,   14,   14, 0x08,
     221,   14,   14,   14, 0x08,
     236,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientNetwork[] = {
    "ClientNetwork\0\0packetReceived(Packet*)\0"
    "pingUpdated(quint32)\0pa,delegateDelete\0"
    "send(Packet*,bool)\0pa\0send(Packet*)\0"
    "send(Packet&)\0type,data\0send(qint32,QByteArray)\0"
    "ping()\0qint32\0getPing()\0flush()\0"
    "connected()\0disconnected()\0dataReceived()\0"
    "socketError(QAbstractSocket::SocketError)\0"
};

const QMetaObject ClientNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientNetwork,
      qt_meta_data_ClientNetwork, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientNetwork::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientNetwork))
        return static_cast<void*>(const_cast< ClientNetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: packetReceived((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 1: pingUpdated((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: send((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: send((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 4: send((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 5: send((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 6: ping(); break;
        case 7: { qint32 _r = getPing();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 8: flush(); break;
        case 9: connected(); break;
        case 10: disconnected(); break;
        case 11: dataReceived(); break;
        case 12: socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ClientNetwork::packetReceived(Packet * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientNetwork::pingUpdated(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
