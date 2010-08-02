/****************************************************************************
** Meta object code from reading C++ file 'Network.h'
**
** Created: Sun 1. Aug 21:26:56 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Network.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerNetwork[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   15,   14,   14, 0x05,
      34,   15,   14,   14, 0x05,
      56,   51,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,  102,   97,   14, 0x0a,
     161,  155,   97,   14, 0x2a,
     206,  188,   14,   14, 0x0a,
     233,  230,   14,   14, 0x2a,
     272,  252,   97,   14, 0x0a,
     339,  323,   97,   14, 0x2a,
     396,  383,   97,   14, 0x2a,
     450,  433,   14,   14, 0x0a,
     506,  493,   14,   14, 0x2a,
     552,  542,   14,   14, 0x2a,
     581,  155,   97,   14, 0x0a,
     608,  230,   14,   14, 0x0a,
     637,  627,   14,   14, 0x0a,
     656,  627,   14,   14, 0x0a,
     674,   15,   97,   14, 0x0a,
     693,  690,  686,   14, 0x0a,
     708,   14,   14,   14, 0x08,
     724,   14,   14,   14, 0x08,
     745,   14,   14,   14, 0x08,
     786,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ServerNetwork[] = {
    "ServerNetwork\0\0ID\0newClient(CLID)\0"
    "clientGone(CLID)\0,who\0"
    "dataReceived(std::auto_ptr<Packet>,CLID)\0"
    "bool\0ID,pa,delegateDelete\0"
    "sendToClient(CLID,Packet*,bool)\0ID,pa\0"
    "sendToClient(CLID,Packet*)\0pa,delegateDelete\0"
    "sendToAll(Packet*,bool)\0pa\0"
    "sendToAll(Packet*)\0ID,type,data,ts,pID\0"
    "sendToClient(CLID,qint32,QByteArray,qint32,qint32)\0"
    "ID,type,data,ts\0"
    "sendToClient(CLID,qint32,QByteArray,qint32)\0"
    "ID,type,data\0sendToClient(CLID,qint32,QByteArray)\0"
    "type,data,ts,pID\0"
    "sendToAll(qint32,QByteArray,qint32,qint32)\0"
    "type,data,ts\0sendToAll(qint32,QByteArray,qint32)\0"
    "type,data\0sendToAll(qint32,QByteArray)\0"
    "sendToClient(CLID,Packet&)\0"
    "sendToAll(Packet&)\0ID,reason\0"
    "kick(CLID,QString)\0ban(CLID,QString)\0"
    "blame(CLID)\0int\0IP\0unban(QString)\0"
    "newConnection()\0clientDisconnected()\0"
    "slot_dataReceived(std::auto_ptr<Packet>)\0"
    "flush()\0"
};

const QMetaObject ServerNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerNetwork,
      qt_meta_data_ServerNetwork, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ServerNetwork::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ServerNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ServerNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerNetwork))
        return static_cast<void*>(const_cast< ServerNetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newClient((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 1: clientGone((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 2: dataReceived((*reinterpret_cast< std::auto_ptr<Packet>(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
        case 3: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< Packet*(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< Packet*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: sendToAll((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: sendToAll((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 7: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3])),(*reinterpret_cast< qint32(*)>(_a[4])),(*reinterpret_cast< qint32(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3])),(*reinterpret_cast< qint32(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: sendToAll((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< qint32(*)>(_a[4]))); break;
        case 11: sendToAll((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 12: sendToAll((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 13: { bool _r = sendToClient((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< Packet(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: sendToAll((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 15: kick((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: ban((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: { bool _r = blame((*reinterpret_cast< CLID(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { int _r = unban((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: newConnection(); break;
        case 20: clientDisconnected(); break;
        case 21: slot_dataReceived((*reinterpret_cast< std::auto_ptr<Packet>(*)>(_a[1]))); break;
        case 22: flush(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void ServerNetwork::newClient(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerNetwork::clientGone(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerNetwork::dataReceived(std::auto_ptr<Packet> _t1, CLID _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
