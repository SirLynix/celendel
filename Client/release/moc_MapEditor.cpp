/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created: Sat 9. Apr 12:01:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x05,
      75,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     102,   89,   84,   10, 0x0a,
     131,  127,   84,   10, 0x2a,
     148,   10,   84,   10, 0x2a,
     158,   10,   84,   10, 0x0a,
     177,  168,   84,   10, 0x0a,
     196,   10,   84,   10, 0x2a,
     208,   10,   84,   10, 0x0a,
     217,  168,   84,   10, 0x0a,
     246,   10,   84,   10, 0x2a,
     268,   10,   84,   10, 0x0a,
     288,   10,   84,   10, 0x0a,
     315,  302,   84,   10, 0x0a,
     338,   10,   84,   10, 0x0a,
     365,  348,   84,   10, 0x0a,
     400,  392,   84,   10, 0x2a,
     419,   10,   84,   10, 0x2a,
     431,   10,   10,   10, 0x0a,
     442,  438,   10,   10, 0x0a,
     456,   10,   10,   10, 0x0a,
     472,  464,   10,   10, 0x08,
     502,  494,   10,   10, 0x08,
     530,  464,   10,   10, 0x08,
     556,  464,   10,   10, 0x08,
     586,   10,   10,   10, 0x08,
     606,   10,   10,   10, 0x08,
     638,  632,   84,   10, 0x08,
     657,  632,   84,   10, 0x08,
     684,   10,   10,   10, 0x08,
     699,   10,   84,   10, 0x08,
     719,  717,   10,   10, 0x08,
     746,   10,   10,   10, 0x08,
     778,  769,   10,   10, 0x08,
     812,   10,   10,   10, 0x08,
     825,   10,   10,   10, 0x08,
     841,   10,   10,   10, 0x08,
     854,   10,   10,   10, 0x08,
     865,   10,   10,   10, 0x08,
     878,   10,   10,   10, 0x08,
     892,  890,   10,   10, 0x08,
     945,  914,   84,   10, 0x08,
     989,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapEditor[] = {
    "MapEditor\0\0,\0"
    "mapSendingRequested(MapInformations*const,QMap<QString,RSID>)\0"
    "closed()\0bool\0map,ressPack\0"
    "loadMap(QString,QString)\0map\0"
    "loadMap(QString)\0loadMap()\0saveMap()\0"
    "fileName\0saveMapAs(QString)\0saveMapAs()\0"
    "newMap()\0saveRessourcePackAs(QString)\0"
    "saveRessourcePackAs()\0saveRessourcePack()\0"
    "replaceRSID()\0before,after\0"
    "replaceRSID(RSID,RSID)\0saveAll()\0"
    "mapName,ressName\0saveAllAs(QString,QString)\0"
    "mapName\0saveAllAs(QString)\0saveAllAs()\0"
    "copy()\0pos\0paste(QPoint)\0paste()\0"
    "newCase\0changeCasePos(QPoint)\0newArea\0"
    "changeSelectedArea(MapArea)\0"
    "changeCurrentCase(QPoint)\0"
    "refreshMapObjectsList(QPoint)\0"
    "refreshObjetsList()\0refreshGlobalObjetsList()\0"
    "index\0selectMapItem(int)\0"
    "selectMapItem(QModelIndex)\0addMapObject()\0"
    "removeMapObject()\0n\0changeCurrentCaseRSID(int)\0"
    "updateRessourcesList()\0curr,max\0"
    "ressourceLoadingProgress(int,int)\0"
    "btnMapSend()\0modifyRssMngr()\0addRssMngr()\0"
    "modified()\0unmodified()\0resetCopy()\0"
    "b\0enableMapSystem(bool)\0"
    "size,name,ressPack,defaultRSID\0"
    "createEmptyMap(QPoint,QString,QString,RSID)\0"
    "changeRsMngrFilter(QString)\0"
};

const QMetaObject MapEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MapEditor,
      qt_meta_data_MapEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditor))
        return static_cast<void*>(const_cast< MapEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MapEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mapSendingRequested((*reinterpret_cast< const MapInformations*const(*)>(_a[1])),(*reinterpret_cast< const QMap<QString,RSID>(*)>(_a[2]))); break;
        case 1: closed(); break;
        case 2: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = loadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = saveMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = saveMapAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = saveMapAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = newMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = saveRessourcePackAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = saveRessourcePackAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = saveRessourcePack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = replaceRSID();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = replaceRSID((*reinterpret_cast< RSID(*)>(_a[1])),(*reinterpret_cast< RSID(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = saveAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = saveAllAs((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = saveAllAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = saveAllAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: copy(); break;
        case 19: paste((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 20: paste(); break;
        case 21: changeCasePos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 22: changeSelectedArea((*reinterpret_cast< MapArea(*)>(_a[1]))); break;
        case 23: changeCurrentCase((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 24: refreshMapObjectsList((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 25: refreshObjetsList(); break;
        case 26: refreshGlobalObjetsList(); break;
        case 27: { bool _r = selectMapItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 28: { bool _r = selectMapItem((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 29: addMapObject(); break;
        case 30: { bool _r = removeMapObject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 31: changeCurrentCaseRSID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: updateRessourcesList(); break;
        case 33: ressourceLoadingProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: btnMapSend(); break;
        case 35: modifyRssMngr(); break;
        case 36: addRssMngr(); break;
        case 37: modified(); break;
        case 38: unmodified(); break;
        case 39: resetCopy(); break;
        case 40: enableMapSystem((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: { bool _r = createEmptyMap((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< RSID(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 42: changeRsMngrFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void MapEditor::mapSendingRequested(const MapInformations * const _t1, const QMap<QString,RSID> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapEditor::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
