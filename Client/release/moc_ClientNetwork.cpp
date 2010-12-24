/****************************************************************************
** Meta object code from reading C++ file 'ClientNetwork.h'
**
** Created: Wed 8. Dec 15:33:32 2010
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
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      32,   14,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      94,   71,   14,   14, 0x05,
     139,   14,   14,   14, 0x05,
     185,   14,   14,   14, 0x05,
     209,  207,   14,   14, 0x05,
     239,  207,   14,   14, 0x05,
     268,  264,   14,   14, 0x05,
     291,   14,   14,   14, 0x05,
     311,   14,   14,   14, 0x05,
     331,   14,   14,   14, 0x05,
     352,   14,   14,   14, 0x05,
     367,   14,   14,   14, 0x05,
     393,   14,   14,   14, 0x05,
     416,   14,   14,   14, 0x05,
     433,  207,   14,   14, 0x05,
     461,  458,   14,   14, 0x05,
     497,  207,   14,   14, 0x05,
     524,   14,   14,   14, 0x05,
     541,  207,   14,   14, 0x05,
     568,   14,   14,   14, 0x05,
     606,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     674,  656,   14,   14, 0x0a,
     696,  693,   14,   14, 0x2a,
     710,  693,   14,   14, 0x0a,
     734,  724,   14,   14, 0x0a,
     758,   14,   14,   14, 0x0a,
     772,   14,  765,   14, 0x0a,
     790,   14,  782,   14, 0x0a,
     809,   14,  801,   14, 0x0a,
     822,   14,   14,   14, 0x0a,
     830,   14,   14,   14, 0x0a,
     843,   14,   14,   14, 0x0a,
     872,  864,  859,   14, 0x0a,
     899,   14,   14,   14, 0x08,
     911,   14,   14,   14, 0x08,
     926,   14,   14,   14, 0x08,
     941,   14,   14,   14, 0x08,
     990,  983,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientNetwork[] = {
    "ClientNetwork\0\0packetReceived()\0"
    "packetCorrupted()\0pingUpdated(quint32)\0"
    "sender,lang,text,canal\0"
    "chatReceived(CLID,QString,QString,ENUM_TYPE)\0"
    "serverInformationsChanged(ServerInformations)\0"
    "clientIDChanged(CLID)\0,\0"
    "nicknameChanged(CLID,QString)\0"
    "error(ENUM_TYPE,QString)\0f,t\0"
    "clientVoted(CLID,CLID)\0newGameMaster(CLID)\0"
    "serverName(QString)\0motdChanged(QString)\0"
    "gameLaunched()\0narrationChanged(QString)\0"
    "connectionEtablished()\0connectionLost()\0"
    "diceRolled(CLID,quint16)\0,,\0"
    "sanctionned(CLID,ENUM_TYPE,QString)\0"
    "clientJoined(CLID,QString)\0clientLeft(CLID)\0"
    "playSound(QString,QString)\0"
    "syncLibs(QList<SoundLibInformations>)\0"
    "syncLanguagesList(QList<QPair<QString,QString> >)\0"
    "pa,delegateDelete\0send(Packet*,bool)\0"
    "pa\0send(Packet*)\0send(Packet&)\0type,data\0"
    "send(qint32,QByteArray)\0ping()\0qint32\0"
    "getPing()\0QString\0serverIP()\0quint16\0"
    "serverPort()\0flush()\0connection()\0"
    "disconnection()\0bool\0IP,port\0"
    "setServer(QString,quint16)\0connected()\0"
    "disconnected()\0dataReceived()\0"
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
        case 1: packetCorrupted(); break;
        case 2: pingUpdated((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 3: chatReceived((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[4]))); break;
        case 4: serverInformationsChanged((*reinterpret_cast< ServerInformations(*)>(_a[1]))); break;
        case 5: clientIDChanged((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 6: nicknameChanged((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: error((*reinterpret_cast< ENUM_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: clientVoted((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
        case 9: newGameMaster((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 10: serverName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: motdChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: gameLaunched(); break;
        case 13: narrationChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: connectionEtablished(); break;
        case 15: connectionLost(); break;
        case 16: diceRolled((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 17: sanctionned((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 18: clientJoined((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: clientLeft((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 20: playSound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 21: syncLibs((*reinterpret_cast< QList<SoundLibInformations>(*)>(_a[1]))); break;
        case 22: syncLanguagesList((*reinterpret_cast< QList<QPair<QString,QString> >(*)>(_a[1]))); break;
        case 23: send((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 24: send((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 25: send((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 26: send((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 27: ping(); break;
        case 28: { qint32 _r = getPing();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 29: { QString _r = serverIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 30: { quint16 _r = serverPort();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        case 31: flush(); break;
        case 32: connection(); break;
        case 33: disconnection(); break;
        case 34: { bool _r = setServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 35: connected(); break;
        case 36: disconnected(); break;
        case 37: dataReceived(); break;
        case 38: socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 39: operatePacket((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void ClientNetwork::packetReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ClientNetwork::packetCorrupted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ClientNetwork::pingUpdated(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientNetwork::chatReceived(CLID _t1, QString _t2, QString _t3, ENUM_TYPE _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientNetwork::serverInformationsChanged(ServerInformations _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientNetwork::clientIDChanged(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientNetwork::nicknameChanged(CLID _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClientNetwork::error(ENUM_TYPE _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ClientNetwork::clientVoted(CLID _t1, CLID _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ClientNetwork::newGameMaster(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ClientNetwork::serverName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ClientNetwork::motdChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ClientNetwork::gameLaunched()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void ClientNetwork::narrationChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ClientNetwork::connectionEtablished()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void ClientNetwork::connectionLost()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void ClientNetwork::diceRolled(CLID _t1, quint16 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ClientNetwork::sanctionned(CLID _t1, ENUM_TYPE _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ClientNetwork::clientJoined(CLID _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ClientNetwork::clientLeft(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ClientNetwork::playSound(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ClientNetwork::syncLibs(QList<SoundLibInformations> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ClientNetwork::syncLanguagesList(QList<QPair<QString,QString> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}
QT_END_MOC_NAMESPACE
