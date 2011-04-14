/****************************************************************************
** Meta object code from reading C++ file 'ClientInterface.h'
**
** Created: Thu 14. Apr 16:31:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      77,   14, // methods
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
     334,  331,   16,   16, 0x08,
     367,  331,   16,   16, 0x08,
     403,   16,   16,   16, 0x08,
     414,   16,   16,   16, 0x08,
     432,   16,   16,   16, 0x08,
     452,   16,   16,   16, 0x08,
     473,   16,   16,   16, 0x08,
     488,   16,   16,   16, 0x08,
     508,  499,   16,   16, 0x08,
     535,   16,   16,   16, 0x08,
     558,  554,   16,   16, 0x08,
     585,   16,   16,   16, 0x08,
     602,   16,   16,   16, 0x08,
     618,   16,   16,   16, 0x08,
     639,   16,  634,   16, 0x08,
     662,  653,  634,   16, 0x08,
     695,  691,   16,   16, 0x08,
     725,  720,  634,   16, 0x08,
     749,   16,   16,   16, 0x08,
     770,   16,   16,   16, 0x08,
     791,   16,   16,   16, 0x08,
     819,  815,  810,   16, 0x08,
     843,   16,   16,   16, 0x08,
     867,   16,   16,   16, 0x08,
     882,   16,   16,   16, 0x08,
     898,   16,   16,   16, 0x08,
     908,   16,   16,   16, 0x08,
     922,   16,   16,   16, 0x08,
     938,   16,   16,   16, 0x08,
     955,   16,   16,   16, 0x08,
     976,  967,   16,   16, 0x08,
     992,   16,   16,   16, 0x28,
    1006, 1001,   16,   16, 0x08,
    1028,   16,   16,   16, 0x28,
    1043,  691,   16,   16, 0x08,
    1069,  691,   16,   16, 0x08,
    1092,   16,   16,   16, 0x08,
    1105,   16,   16,   16, 0x08,
    1117,   16,   16,   16, 0x08,
    1132,   16,   16,   16, 0x08,
    1149,   16,   16,   16, 0x08,
    1159,   16,   16,   16, 0x08,
    1173,   16,   16,   16, 0x08,
    1199,   16,   16,   16, 0x08,
    1242,   16,   16,   16, 0x08,
    1297, 1292,   16,   16, 0x08,
    1336, 1331,   16,   16, 0x08,
    1380, 1367,   16,   16, 0x08,
    1416, 1331,   16,   16, 0x08,
    1451, 1438,   16,   16, 0x08,
    1497, 1481,   16,   16, 0x08,
    1525, 1331,   16,   16, 0x08,
    1563, 1547,   16,   16, 0x08,
    1599, 1591,   16,   16, 0x08,
    1630, 1591,   16,   16, 0x08,
    1664, 1591,   16,   16, 0x08,
    1697, 1591,   16,   16, 0x08,
    1732, 1591,   16,   16, 0x08,
    1759, 1591,   16,   16, 0x08,
    1797, 1788,   16,   16, 0x08,
    1855,   16,   16,   16, 0x08,
    1872,   16,   16,   16, 0x08,
    1883,   16,   16,   16, 0x08,
    1894,   16,   16,   16, 0x08,
    1913,   16,   16,   16, 0x08,
    1929,   16,   16,   16, 0x08,
    1950, 1948,   16,   16, 0x08,

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
    "connectionLost()\0,,\0"
    "diceRolled(CLID,quint16,quint16)\0"
    "sanctionned(CLID,ENUM_TYPE,QString)\0"
    "rollDice()\0rollSpecialDice()\0"
    "serverName(QString)\0motdChanged(QString)\0"
    "gameLaunched()\0setTitle()\0lid,rsid\0"
    "playSound(QString,QString)\0"
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
    "openMapEditor()\0clearMapEditor()\0"
    "resetData()\0fileName\0setCSS(QString)\0"
    "setCSS()\0path\0setInterface(QString)\0"
    "setInterface()\0characterListMenu(QPoint)\0"
    "playerListMenu(QPoint)\0actionKick()\0"
    "actionBan()\0actionVoteGM()\0actionChangeGM()\0"
    "refresh()\0textChanged()\0"
    "narrationChanged(QString)\0"
    "syncSoundLibs(QList<SoundLibInformations>)\0"
    "syncLanguagesList(QList<QPair<QString,QString> >)\0"
    "list\0syncDictionariesList(QStringList)\0"
    "name\0requestScriptDownload(QString)\0"
    "name,content\0sendScriptToServer(QString,QString)\0"
    "deleteScript(QString)\0name,newName\0"
    "renameScript(QString,QString)\0"
    "name,scriptName\0makeEntity(QString,QString)\0"
    "deleteEntity(QString)\0entityName,code\0"
    "injectCode(QString,QString)\0ent,txt\0"
    "scriptToGMMsg(QString,QString)\0"
    "scriptToOwnerMsg(QString,QString)\0"
    "scriptActionMsg(QString,QString)\0"
    "scriptToPlayerMsg(QString,QString)\0"
    "scriptMsg(QString,QString)\0"
    "scriptError(QString,QString)\0map,ress\0"
    "sendMapToServer(MapInformations*const,QMap<QString,RSID>)\0"
    "addDictionnary()\0saveGame()\0loadGame()\0"
    "VOIPRemoveClient()\0VOIPAddClient()\0"
    "VOIPClientVolume()\0,\0dataPerSecond(int,int)\0"
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
        case 10: diceRolled((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 11: sanctionned((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< ENUM_TYPE(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: rollDice(); break;
        case 13: rollSpecialDice(); break;
        case 14: serverName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: motdChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: gameLaunched(); break;
        case 17: setTitle(); break;
        case 18: playSound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: updatePlayerList(); break;
        case 20: clientJoined((*reinterpret_cast< CLID(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 21: clientLeft((*reinterpret_cast< CLID(*)>(_a[1]))); break;
        case 22: updateGMLabel(); break;
        case 23: updateGMPanel(); break;
        case 24: { bool _r = addLanguage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: { bool _r = addLanguage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: languageListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 27: { bool _r = removeLanguage((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 28: removeLanguageMenu(); break;
        case 29: importLanguageList(); break;
        case 30: sendLanguageList(); break;
        case 31: { CLID _r = CLIDFromString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< CLID*>(_a[0]) = _r; }  break;
        case 32: switchConnectionState(); break;
        case 33: openSettings(); break;
        case 34: openSoundsGUI(); break;
        case 35: aboutUs(); break;
        case 36: aboutServer(); break;
        case 37: openMapEditor(); break;
        case 38: clearMapEditor(); break;
        case 39: resetData(); break;
        case 40: setCSS((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: setCSS(); break;
        case 42: setInterface((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: setInterface(); break;
        case 44: characterListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 45: playerListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 46: actionKick(); break;
        case 47: actionBan(); break;
        case 48: actionVoteGM(); break;
        case 49: actionChangeGM(); break;
        case 50: refresh(); break;
        case 51: textChanged(); break;
        case 52: narrationChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 53: syncSoundLibs((*reinterpret_cast< QList<SoundLibInformations>(*)>(_a[1]))); break;
        case 54: syncLanguagesList((*reinterpret_cast< QList<QPair<QString,QString> >(*)>(_a[1]))); break;
        case 55: syncDictionariesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 56: requestScriptDownload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 57: sendScriptToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 58: deleteScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 59: renameScript((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 60: makeEntity((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 61: deleteEntity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 62: injectCode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 63: scriptToGMMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 64: scriptToOwnerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 65: scriptActionMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 66: scriptToPlayerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 67: scriptMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 68: scriptError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 69: sendMapToServer((*reinterpret_cast< const MapInformations*const(*)>(_a[1])),(*reinterpret_cast< const QMap<QString,RSID>(*)>(_a[2]))); break;
        case 70: addDictionnary(); break;
        case 71: saveGame(); break;
        case 72: loadGame(); break;
        case 73: VOIPRemoveClient(); break;
        case 74: VOIPAddClient(); break;
        case 75: VOIPClientVolume(); break;
        case 76: dataPerSecond((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 77;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
