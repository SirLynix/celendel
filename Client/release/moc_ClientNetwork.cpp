/****************************************************************************
** Meta object code from reading C++ file 'ClientNetwork.h'
**
** Created: Sun 22. Jul 20:25:52 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientNetwork.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientNetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientNetwork[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      56,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      39,       // signalCount

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
     412,  207,   14,   14, 0x05,
     442,  434,   14,   14, 0x05,
     473,  434,   14,   14, 0x05,
     507,  434,   14,   14, 0x05,
     540,  434,   14,   14, 0x05,
     575,  434,   14,   14, 0x05,
     602,  434,   14,   14, 0x05,
     631,   14,   14,   14, 0x05,
     673,   14,   14,   14, 0x05,
     706,   14,   14,   14, 0x05,
     742,  729,   14,   14, 0x05,
     778,  774,   14,   14, 0x05,
     816,   14,   14,   14, 0x05,
     839,   14,   14,   14, 0x05,
     859,  856,   14,   14, 0x05,
     892,  856,   14,   14, 0x05,
     928,  207,   14,   14, 0x05,
     955,   14,   14,   14, 0x05,
     972,  207,   14,   14, 0x05,
     999,   14,   14,   14, 0x05,
    1037,   14,   14,   14, 0x05,
    1092, 1087,   14,   14, 0x05,
    1126, 1087,   14,   14, 0x05,
    1154, 1087,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
    1205, 1187,   14,   14, 0x0a,
    1227, 1224,   14,   14, 0x2a,
    1241, 1224,   14,   14, 0x0a,
    1265, 1255,   14,   14, 0x0a,
    1289,   14,   14,   14, 0x0a,
    1303,   14, 1296,   14, 0x0a,
    1321,   14, 1313,   14, 0x0a,
    1340,   14, 1332,   14, 0x0a,
    1353,   14,   14,   14, 0x0a,
    1361,   14,   14,   14, 0x0a,
    1374,   14,   14,   14, 0x0a,
    1403, 1395, 1390,   14, 0x0a,
    1430,   14,   14,   14, 0x08,
    1442,   14,   14,   14, 0x08,
    1457,   14,   14,   14, 0x08,
    1472,   14,   14,   14, 0x08,
    1521, 1514,   14,   14, 0x08,

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
    "mapChanged(MapPtr)\0mapFlare(QPoint,CLID)\0"
    "ent,txt\0scriptToGMMsg(QString,QString)\0"
    "scriptToOwnerMsg(QString,QString)\0"
    "scriptActionMsg(QString,QString)\0"
    "scriptToPlayerMsg(QString,QString)\0"
    "scriptMsg(QString,QString)\0"
    "scriptError(QString,QString)\0"
    "updateEntities(QList<EntityInformations>)\0"
    "updateEntity(EntityInformations)\0"
    "entityDeleted(QString)\0name,content\0"
    "scriptReceived(QString,QString)\0rss\0"
    "ressourcesUpdated(QMap<QString,RSID>)\0"
    "connectionEtablished()\0connectionLost()\0"
    ",,\0diceRolled(CLID,quint16,quint16)\0"
    "sanctionned(CLID,ENUM_TYPE,QString)\0"
    "clientJoined(CLID,QString)\0clientLeft(CLID)\0"
    "playSound(QString,QString)\0"
    "syncLibs(QList<SoundLibInformations>)\0"
    "syncLanguagesList(QList<QPair<QString,QString> >)\0"
    "list\0syncDictionariesList(QStringList)\0"
    "syncScriptList(QStringList)\0"
    "updateCharacterList(QStringList)\0"
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
        case 14: mapChanged((*reinterpret_cast< MapPtr(*)>(_a[1]))); break;
        case 15: mapFlare((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
        case 16: scriptToGMMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: scriptToOwnerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: scriptActionMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: scriptToPlayerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: scriptMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 21: scriptError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: updateEntities((*reinterpret_cast< const QList<EntityInformations>(*)>(_a[1]))); break;
        case 23: updateEntity((*reinterpret_cast< const EntityInformations(*)>(_a[1]))); break;
        case 24: entityDeleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: scriptReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 26: ressourcesUpdated((*reinterpret_cast< const QMap<QString,RSID>(*)>(_a[1]))); break;
        case 27: connectionEtablished(); break;
        case 28: connectionLost(); break;
        case 29: diceRolled((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 30: sanctionned((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 31: clientJoined((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 32: clientLeft((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 33: playSound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 34: syncLibs((*reinterpret_cast< QList<SoundLibInformations>(*)>(_a[1]))); break;
        case 35: syncLanguagesList((*reinterpret_cast< QList<QPair<QString,QString> >(*)>(_a[1]))); break;
        case 36: syncDictionariesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 37: syncScriptList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 38: updateCharacterList((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 39: send((*reinterpret_cast< Packet*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 40: send((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        case 41: send((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 42: send((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 43: ping(); break;
        case 44: { qint32 _r = getPing();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 45: { QString _r = serverIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 46: { quint16 _r = serverPort();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        case 47: flush(); break;
        case 48: connection(); break;
        case 49: disconnection(); break;
        case 50: { bool _r = setServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 51: connected(); break;
        case 52: disconnected(); break;
        case 53: dataReceived(); break;
        case 54: socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 55: operatePacket((*reinterpret_cast< Packet*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 56;
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
void ClientNetwork::mapChanged(MapPtr _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ClientNetwork::mapFlare(QPoint _t1, CLID _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ClientNetwork::scriptToGMMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ClientNetwork::scriptToOwnerMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ClientNetwork::scriptActionMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ClientNetwork::scriptToPlayerMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ClientNetwork::scriptMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ClientNetwork::scriptError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ClientNetwork::updateEntities(const QList<EntityInformations> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void ClientNetwork::updateEntity(const EntityInformations & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void ClientNetwork::entityDeleted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void ClientNetwork::scriptReceived(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void ClientNetwork::ressourcesUpdated(const QMap<QString,RSID> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void ClientNetwork::connectionEtablished()
{
    QMetaObject::activate(this, &staticMetaObject, 27, 0);
}

// SIGNAL 28
void ClientNetwork::connectionLost()
{
    QMetaObject::activate(this, &staticMetaObject, 28, 0);
}

// SIGNAL 29
void ClientNetwork::diceRolled(CLID _t1, quint16 _t2, quint16 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void ClientNetwork::sanctionned(CLID _t1, ENUM_TYPE _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void ClientNetwork::clientJoined(CLID _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void ClientNetwork::clientLeft(CLID _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void ClientNetwork::playSound(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void ClientNetwork::syncLibs(QList<SoundLibInformations> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void ClientNetwork::syncLanguagesList(QList<QPair<QString,QString> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void ClientNetwork::syncDictionariesList(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void ClientNetwork::syncScriptList(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void ClientNetwork::updateCharacterList(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}
QT_END_MOC_NAMESPACE
