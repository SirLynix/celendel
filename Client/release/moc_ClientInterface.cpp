/****************************************************************************
** Meta object code from reading C++ file 'ClientInterface.h'
**
** Created: Wed 19. Jan 18:02:28 2011
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
      64,   14, // methods
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
     594,   16,   16,   16, 0x08,
     615,   16,  610,   16, 0x08,
     638,  629,  610,   16, 0x08,
     671,  667,   16,   16, 0x08,
     701,  696,  610,   16, 0x08,
     725,   16,   16,   16, 0x08,
     746,   16,   16,   16, 0x08,
     767,   16,   16,   16, 0x08,
     795,  791,  786,   16, 0x08,
     819,   16,   16,   16, 0x08,
     843,   16,   16,   16, 0x08,
     858,   16,   16,   16, 0x08,
     874,   16,   16,   16, 0x08,
     884,   16,   16,   16, 0x08,
     898,   16,  610,   16, 0x08,
     939,  922,  610,   16, 0x08,
     981,  973,  610,   16, 0x28,
    1007,   16,  610,   16, 0x28,
    1026,   16,   16,   16, 0x08,
    1047, 1038,   16,   16, 0x08,
    1063,   16,   16,   16, 0x28,
    1077, 1072,   16,   16, 0x08,
    1099,   16,   16,   16, 0x28,
    1114,  667,   16,   16, 0x08,
    1140,  667,   16,   16, 0x08,
    1163,   16,   16,   16, 0x08,
    1176,   16,   16,   16, 0x08,
    1188,   16,   16,   16, 0x08,
    1203,   16,   16,   16, 0x08,
    1220,   16,   16,   16, 0x08,
    1230,   16,   16,   16, 0x08,
    1244,   16,   16,   16, 0x08,
    1270,   16,   16,   16, 0x08,
    1313,   16,   16,   16, 0x08,
    1368, 1363,   16,   16, 0x08,
    1402,   16,   16,   16, 0x08,
    1419,   16,   16,   16, 0x08,
    1430,   16,   16,   16, 0x08,
    1441,   16,   16,   16, 0x08,
    1460,   16,   16,   16, 0x08,
    1476,   16,   16,   16, 0x08,
    1495,  331,   16,   16, 0x08,

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
    "updateGMLabel()\0updateGMPanel()\0bool\0"
    "addLanguage()\0lang,dic\0"
    "addLanguage(QString,QString)\0pos\0"
    "languageListMenu(QPoint)\0lang\0"
    "removeLanguage(QString)\0removeLanguageMenu()\0"
    "importLanguageList()\0sendLanguageList()\0"
    "CLID\0str\0CLIDFromString(QString)\0"
    "switchConnectionState()\0openSettings()\0"
    "openSoundsGUI()\0aboutUs()\0aboutServer()\0"
    "loadRessourcesListGUI()\0mapName,ressList\0"
    "openRenderWindow(QString,QString)\0"
    "mapName\0openRenderWindow(QString)\0"
    "openRenderWindow()\0resetData()\0fileName\0"
    "setCSS(QString)\0setCSS()\0path\0"
    "setInterface(QString)\0setInterface()\0"
    "characterListMenu(QPoint)\0"
    "playerListMenu(QPoint)\0actionKick()\0"
    "actionBan()\0actionVoteGM()\0actionChangeGM()\0"
    "refresh()\0textChanged()\0"
    "narrationChanged(QString)\0"
    "syncSoundLibs(QList<SoundLibInformations>)\0"
    "syncLanguagesList(QList<QPair<QString,QString> >)\0"
    "list\0syncDictionariesList(QStringList)\0"
    "addDictionnary()\0saveGame()\0loadGame()\0"
    "VOIPRemoveClient()\0VOIPAddClient()\0"
    "VOIPClientVolume()\0dataPerSecond(int,int)\0"
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
        case 22: updateGMPanel(); break;
        case 23: { bool _r = addLanguage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 24: { bool _r = addLanguage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: languageListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 26: { bool _r = removeLanguage((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: removeLanguageMenu(); break;
        case 28: importLanguageList(); break;
        case 29: sendLanguageList(); break;
        case 30: { CLID _r = CLIDFromString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< CLID*>(_a[0]) = _r; }  break;
        case 31: switchConnectionState(); break;
        case 32: openSettings(); break;
        case 33: openSoundsGUI(); break;
        case 34: aboutUs(); break;
        case 35: aboutServer(); break;
        case 36: { bool _r = loadRessourcesListGUI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 37: { bool _r = openRenderWindow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 38: { bool _r = openRenderWindow((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 39: { bool _r = openRenderWindow();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 40: resetData(); break;
        case 41: setCSS((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: setCSS(); break;
        case 43: setInterface((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 44: setInterface(); break;
        case 45: characterListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 46: playerListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 47: actionKick(); break;
        case 48: actionBan(); break;
        case 49: actionVoteGM(); break;
        case 50: actionChangeGM(); break;
        case 51: refresh(); break;
        case 52: textChanged(); break;
        case 53: narrationChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 54: syncSoundLibs((*reinterpret_cast< QList<SoundLibInformations>(*)>(_a[1]))); break;
        case 55: syncLanguagesList((*reinterpret_cast< QList<QPair<QString,QString> >(*)>(_a[1]))); break;
        case 56: syncDictionariesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 57: addDictionnary(); break;
        case 58: saveGame(); break;
        case 59: loadGame(); break;
        case 60: VOIPRemoveClient(); break;
        case 61: VOIPAddClient(); break;
        case 62: VOIPClientVolume(); break;
        case 63: dataPerSecond((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 64;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
