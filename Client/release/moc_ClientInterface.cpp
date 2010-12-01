/****************************************************************************
** Meta object code from reading C++ file 'ClientInterface.h'
**
** Created: Wed 1. Dec 14:45:27 2010
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
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      49,   31,   16,   16, 0x08,
      81,   78,   16,   16, 0x08,
     129,  126,   16,   16, 0x08,
     158,  150,   16,   16, 0x08,
     199,  193,   16,   16, 0x08,
     228,  126,   16,   16, 0x08,
     255,  251,   16,   16, 0x08,
     278,   16,   16,   16, 0x08,
     301,   16,   16,   16, 0x08,
     320,  318,   16,   16, 0x08,
     348,  345,   16,   16, 0x08,
     384,   16,   16,   16, 0x08,
     395,   16,   16,   16, 0x08,
     415,   16,   16,   16, 0x08,
     436,   16,   16,   16, 0x08,
     451,   16,   16,   16, 0x08,
     471,  462,   16,   16, 0x08,
     498,   16,   16,   16, 0x08,
     521,  517,   16,   16, 0x08,
     548,   16,   16,   16, 0x08,
     565,   16,   16,   16, 0x08,
     590,  586,  581,   16, 0x08,
     614,   16,   16,   16, 0x08,
     638,   16,   16,   16, 0x08,
     653,   16,   16,   16, 0x08,
     669,   16,   16,   16, 0x08,
     679,   16,   16,   16, 0x08,
     693,   16,   16,   16, 0x08,
     714,  705,   16,   16, 0x08,
     730,   16,   16,   16, 0x28,
     744,  739,   16,   16, 0x08,
     766,   16,   16,   16, 0x28,
     785,  781,   16,   16, 0x08,
     808,   16,   16,   16, 0x08,
     821,   16,   16,   16, 0x08,
     833,   16,   16,   16, 0x08,
     848,   16,   16,   16, 0x08,
     865,   16,   16,   16, 0x08,
     875,   16,   16,   16, 0x08,
     889,   16,   16,   16, 0x08,
     915,   16,   16,   16, 0x08,
     958,   16,   16,   16, 0x08,
     969,   16,   16,   16, 0x08,
     980,   16,   16,   16, 0x08,
     999,   16,   16,   16, 0x08,
    1015,   16,   16,   16, 0x08,
    1034,  318,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClientInterface[] = {
    "ClientInterface\0\0sendMessage()\0"
    "sender,text,canal\0chat(CLID,QString,ENUM_TYPE)\0"
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
        case 1: chat((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[3]))); break;
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
        case 42: saveGame(); break;
        case 43: loadGame(); break;
        case 44: VOIPRemoveClient(); break;
        case 45: VOIPAddClient(); break;
        case 46: VOIPClientVolume(); break;
        case 47: dataPerSecond((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 48;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
