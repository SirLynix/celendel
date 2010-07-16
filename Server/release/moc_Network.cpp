/****************************************************************************
** Meta object code from reading C++ file 'Network.h'
**
** Created: Fri 16. Jul 22:41:55 2010
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
      22,   14, // methods
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
     109,   88,   83,   14, 0x0a,
     147,  141,   83,   14, 0x2a,
     192,  174,   14,   14, 0x0a,
     219,  216,   14,   14, 0x2a,
     258,  238,   83,   14, 0x0a,
     325,  309,   83,   14, 0x2a,
     382,  369,   83,   14, 0x2a,
     436,  419,   14,   14, 0x0a,
     492,  479,   14,   14, 0x2a,
     538,  528,   14,   14, 0x2a,
     567,  141,   83,   14, 0x0a,
     594,  216,   14,   14, 0x0a,
     623,  613,   14,   14, 0x0a,
     642,  613,   14,   14, 0x0a,
     667,  664,  660,   14, 0x0a,
     682,   14,   14,   14, 0x08,
     698,   14,   14,   14, 0x08,
     719,   14,   14,   14, 0x08,
     746,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ServerNetwork[] = {
    "ServerNetwork\0\0ID\0newClient(CLID)\0"
    "clientGone(CLID)\0,who\0dataReceived(Packet*,CLID)\0"
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
    "int\0IP\0unban(QString)\0newConnection()\0"
    "clientDisconnected()\0slot_dataReceived(Packet*)\0"
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
        case 2: dataReceived((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
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
        case 17: { int _r = unban((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: newConnection(); break;
        case 19: clientDisconnected(); break;
        case 20: slot_dataReceived((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 21: flush(); break;
        default: ;
        }
        _id -= 22;
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
void ServerNetwork::dataReceived(Packet * _t1, CLID _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
