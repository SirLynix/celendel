/****************************************************************************
** Meta object code from reading C++ file 'ClientInterface.h'
**
** Created: Mon 6. Dec 20:03:05 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientInterface[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      54,   31,   16,   16, 0x08,
      94,   91,   16,   16, 0x08,
     142,  139,   16,   16, 0x08,
     171,  163,   16,   16, 0x08,
     212,  206,   16,   16, 0x08,
     241,  139,   16,   16, 0x08,
     268,  264,   16,   16, 0x08,
     291,   16,   16,   16, 0x08,
     314,   16,   16,   16, 0x08,
     333,  331,   16,   16, 0x08,
     361,  358,   16,   16, 0x08,
     397,   16,   16,   16, 0x08,
     408,   16,   16,   16, 0x08,
     428,   16,   16,   16, 0x08,
     449,   16,   16,   16, 0x08,
     464,   16,   16,   16, 0x08,
     484,  475,   16,   16, 0x08,
     511,   16,   16,   16, 0x08,
     534,  530,   16,   16, 0x08,
     561,   16,   16,   16, 0x08,
     578,   16,   16,   16, 0x08,
     603,  599,  594,   16, 0x08,
     627,   16,   16,   16, 0x08,
     651,   16,   16,   16, 0x08,
     666,   16,   16,   16, 0x08,
     682,   16,   16,   16, 0x08,
     692,   16,   16,   16, 0x08,
     706,   16,   16,   16, 0x08,
     727,  718,   16,   16, 0x08,
     743,   16,   16,   16, 0x28,
     757,  752,   16,   16, 0x08,
     779,   16,   16,   16, 0x28,
     798,  794,   16,   16, 0x08,
     821,   16,   16,   16, 0x08,
     834,   16,   16,   16, 0x08,
     846,   16,   16,   16, 0x08,
     861,   16,   16,   16, 0x08,
     878,   16,   16,   16, 0x08,
     888,   16,   16,   16, 0x08,
     902,   16,   16,   16, 0x08,
     928,   16,   16,   16, 0x08,
     971,   16,   16,   16, 0x08,
    1002,   16,   16,   16, 0x08,
    1013,   16,   16,   16, 0x08,
    1024,   16,   16,   16, 0x08,
    1043,   16,   16,   16, 0x08,
    1059,   16,   16,   16, 0x08,
    1078,  331,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientInterface[] = {
    "ClientInterface\0\0sendMessage()\0"
    "sender,lang,text,canal\0"
    "chat(CLID,QString,QString,ENUM_TYPE)\0"
    "si\0changeServerInformations(ServerInformations)\0"
    "ID\0changeClientID(CLID)\0ID,nick\0"
    "changeClientNickname(CLID,QString)\0"
    "e,txt\0showError(ENUM_TYPE,QString)\0"
    "changeGameMaster(CLID)\0f,t\0"
    "clientVoted(CLID,CLID)\0connectionEtablished()\0"
    "connectionLost()\0,\0diceRolled(CLID,quint16)\0"
    ",,\0sanctionned(CLID,ENUM_TYPE,QString)\0"
    "rollDice()\0serverName(QString)\0"
    "motdChanged(QString)\0gameLaunched()\0"
    "setTitle()\0lid,rsid\0playSound(QString,QString)\0"
    "updatePlayerList()\0,IP\0"
    "clientJoined(CLID,QString)\0clientLeft(CLID)\0"
    "updateGMLabel()\0CLID\0str\0"
    "CLIDFromString(QString)\0switchConnectionState()\0"
    "openSettings()\0openSoundsGUI()\0aboutUs()\0"
    "aboutServer()\0resetData()\0fileName\0"
    "setCSS(QString)\0setCSS()\0path\0"
    "setInterface(QString)\0setInterface()\0"
    "pos\0playerListMenu(QPoint)\0actionKick()\0"
    "actionBan()\0actionVoteGM()\0actionChangeGM()\0"
    "refresh()\0textChanged()\0"
    "narrationChanged(QString)\0"
    "syncSoundLibs(QList<SoundLibInformations>)\0"
    "syncLanguagesList(QStringList)\0"
    "saveGame()\0loadGame()\0VOIPRemoveClient()\0"
    "VOIPAddClient()\0VOIPClientVolume()\0"
    "dataPerSecond(int,int)\0"
};

const QMetaObject ClientInterface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ClientInterface,
      qt_meta_data_ClientInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientInterface))
        return static_cast<void*>(const_cast< ClientInterface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ClientInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendMessage(); break;
        case 1: chat((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[4]))); break;
        case 2: changeServerInformations((*reinterpret_cast< ServerInformations(*)>(_a[1]))); break;
        case 3: changeClientID((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 4: changeClientNickname((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: showError((*reinterpret_cast< ENUM_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: changeGameMaster((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 7: clientVoted((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< CLID(*)>(_a[2]))); break;
        case 8: connectionEtablished(); break;
        case 9: connectionLost(); break;
        case 10: diceRolled((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 11: sanctionned((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: rollDice(); break;
        case 13: serverName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: motdChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: gameLaunched(); break;
        case 16: setTitle(); break;
        case 17: playSound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: updatePlayerList(); break;
        case 19: clientJoined((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: clientLeft((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 21: updateGMLabel(); break;
        case 22: { CLID _r = CLIDFromString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< CLID*>(_a[0]) = _r; }  break;
        case 23: switchConnectionState(); break;
        case 24: openSettings(); break;
        case 25: openSoundsGUI(); break;
        case 26: aboutUs(); break;
        case 27: aboutServer(); break;
        case 28: resetData(); break;
        case 29: setCSS((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: setCSS(); break;
        case 31: setInterface((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: setInterface(); break;
        case 33: playerListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 34: actionKick(); break;
        case 35: actionBan(); break;
        case 36: actionVoteGM(); break;
        case 37: actionChangeGM(); break;
        case 38: refresh(); break;
        case 39: textChanged(); break;
        case 40: narrationChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: syncSoundLibs((*reinterpret_cast< QList<SoundLibInformations>(*)>(_a[1]))); break;
        case 42: syncLanguagesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 43: saveGame(); break;
        case 44: loadGame(); break;
        case 45: VOIPRemoveClient(); break;
        case 46: VOIPAddClient(); break;
        case 47: VOIPClientVolume(); break;
        case 48: dataPerSecond((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 49;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
