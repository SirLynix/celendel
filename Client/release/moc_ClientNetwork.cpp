/****************************************************************************
** Meta object code from reading C++ file 'ClientNetwork.h'
**
** Created: Wed 30. Jun 21:58:36 2010
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
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      32,   14,   14,   14, 0x05,
      71,   53,   14,   14, 0x05,
     108,   14,   14,   14, 0x05,
     154,   14,   14,   14, 0x05,
     178,  176,   14,   14, 0x05,
     208,  176,   14,   14, 0x05,
     237,  233,   14,   14, 0x05,
     260,   14,   14,   14, 0x05,
     280,   14,   14,   14, 0x05,
     303,   14,   14,   14, 0x05,
     320,  176,   14,   14, 0x05,
     348,  345,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     402,  384,   14,   14, 0x0a,
     424,  421,   14,   14, 0x2a,
     438,  421,   14,   14, 0x0a,
     462,  452,   14,   14, 0x0a,
     486,   14,   14,   14, 0x0a,
     500,   14,  493,   14, 0x0a,
     518,   14,  510,   14, 0x0a,
     537,   14,  529,   14, 0x0a,
     550,   14,   14,   14, 0x0a,
     558,   14,   14,   14, 0x0a,
     571,   14,   14,   14, 0x08,
     583,   14,   14,   14, 0x08,
     598,   14,   14,   14, 0x08,
     613,   14,   14,   14, 0x08,
     662,  655,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientNetwork[] = {
    "ClientNetwork\0\0packetReceived()\0"
    "pingUpdated(quint32)\0sender,text,canal\0"
    "chatReceived(CLID,QString,ENUM_TYPE)\0"
    "serverInformationsChanged(ServerInformations)\0"
    "clientIDChanged(CLID)\0,\0"
    "nicknameChanged(CLID,QString)\0"
    "error(ENUM_TYPE,QString)\0f,t\0"
    "clientVoted(CLID,CLID)\0newGameMaster(CLID)\0"
    "connectionEtablished()\0connectionLost()\0"
    "diceRolled(CLID,quint16)\0,,\0"
    "sanctionned(CLID,ENUM_TYPE,QString)\0"
    "pa,delegateDelete\0send(Packet*,bool)\0"
    "pa\0send(Packet*)\0send(Packet&)\0type,data\0"
    "send(qint32,QByteArray)\0ping()\0qint32\0"
    "getPing()\0QString\0serverIP()\0quint16\0"
    "serverPort()\0flush()\0connection()\0"
    "connected()\0disconnected()\0dataReceived()\0"
    "socketError(QAbstractSocket::SocketError)\0"
    "packet\0operatePacket(Packet*)\0"
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
        case 0: packetReceived(); break;
        case 1: pingUpdated((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: chatReceived((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[3]))); break;
        case 3: serverInformationsChanged((*reinterpret_cast< ServerInformations(*)>(_a[1]))); break;
        case 4: clientIDChanged((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 5: nicknameChanged((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: error((*reinterpret_cast< ENUM_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: clientVoted((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
        case 8: newGameMaster((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 9: connectionEtablished(); break;
        case 10: connectionLost(); break;
        case 11: diceRolled((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 12: sanctionned((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: send((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: send((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 15: send((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 16: send((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 17: ping(); break;
        case 18: { qint32 _r = getPing();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 19: { QString _r = serverIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: { quint16 _r = serverPort();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        case 21: flush(); break;
        case 22: connection(); break;
        case 23: connected(); break;
        case 24: disconnected(); break;
        case 25: dataReceived(); break;
        case 26: socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 27: operatePacket((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void ClientNetwork::packetReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ClientNetwork::pingUpdated(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientNetwork::chatReceived(CLID _t1, QString _t2, ENUM_TYPE _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientNetwork::serverInformationsChanged(ServerInformations _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientNetwork::clientIDChanged(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientNetwork::nicknameChanged(CLID _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientNetwork::error(ENUM_TYPE _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClientNetwork::clientVoted(CLID _t1, CLID _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ClientNetwork::newGameMaster(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ClientNetwork::connectionEtablished()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void ClientNetwork::connectionLost()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void ClientNetwork::diceRolled(CLID _t1, quint16 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ClientNetwork::sanctionned(CLID _t1, ENUM_TYPE _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
