/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created: Mon 14. Feb 15:50:19 2011
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
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   59,   54,   10, 0x0a,
     101,   97,   54,   10, 0x2a,
     118,   10,   54,   10, 0x2a,
     128,   10,   54,   10, 0x0a,
     147,  138,   54,   10, 0x0a,
     166,   10,   54,   10, 0x2a,
     178,   10,   54,   10, 0x0a,
     187,  138,   54,   10, 0x0a,
     216,   10,   54,   10, 0x2a,
     238,   10,   54,   10, 0x0a,
     258,   10,   54,   10, 0x0a,
     285,  272,   54,   10, 0x0a,
     308,   10,   54,   10, 0x0a,
     335,  318,   54,   10, 0x0a,
     370,  362,   54,   10, 0x2a,
     389,   10,   54,   10, 0x2a,
     401,   10,   10,   10, 0x0a,
     412,  408,   10,   10, 0x0a,
     426,   10,   10,   10, 0x0a,
     442,  434,   10,   10, 0x08,
     472,  464,   10,   10, 0x08,
     500,  434,   10,   10, 0x08,
     526,  434,   10,   10, 0x08,
     556,   10,   10,   10, 0x08,
     576,   10,   10,   10, 0x08,
     608,  602,   54,   10, 0x08,
     627,  602,   54,   10, 0x08,
     654,   10,   10,   10, 0x08,
     671,  669,   10,   10, 0x08,
     698,   10,   10,   10, 0x08,
     721,   10,   10,   10, 0x08,
     734,   10,   10,   10, 0x08,
     750,   10,   10,   10, 0x08,
     763,   10,   10,   10, 0x08,
     774,   10,   10,   10, 0x08,
     787,   10,   10,   10, 0x08,
     801,  799,   10,   10, 0x08,
     854,  823,   54,   10, 0x08,
     898,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapEditor[] = {
    "MapEditor\0\0mapSendingRequested(MapInformations*const)\0"
    "bool\0map,ressPack\0loadMap(QString,QString)\0"
    "map\0loadMap(QString)\0loadMap()\0saveMap()\0"
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
    "n\0changeCurrentCaseRSID(int)\0"
    "updateRessourcesList()\0btnMapSend()\0"
    "modifyRssMngr()\0addRssMngr()\0modified()\0"
    "unmodified()\0resetCopy()\0b\0"
    "enableMapSystem(bool)\0"
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
        case 0: mapSendingRequested((*reinterpret_cast< const MapInformations*const(*)>(_a[1]))); break;
        case 1: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = loadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = saveMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = saveMapAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = saveMapAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = newMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = saveRessourcePackAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = saveRessourcePackAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = saveRessourcePack();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = replaceRSID();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = replaceRSID((*reinterpret_cast< RSID(*)>(_a[1])),(*reinterpret_cast< RSID(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = saveAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = saveAllAs((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = saveAllAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = saveAllAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: copy(); break;
        case 18: paste((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 19: paste(); break;
        case 20: changeCasePos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 21: changeSelectedArea((*reinterpret_cast< MapArea(*)>(_a[1]))); break;
        case 22: changeCurrentCase((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 23: refreshMapObjectsList((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 24: refreshObjetsList(); break;
        case 25: refreshGlobalObjetsList(); break;
        case 26: { bool _r = selectMapItem((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: { bool _r = selectMapItem((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 28: addMapObject(); break;
        case 29: changeCurrentCaseRSID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: updateRessourcesList(); break;
        case 31: btnMapSend(); break;
        case 32: modifyRssMngr(); break;
        case 33: addRssMngr(); break;
        case 34: modified(); break;
        case 35: unmodified(); break;
        case 36: resetCopy(); break;
        case 37: enableMapSystem((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: { bool _r = createEmptyMap((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< RSID(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 39: changeRsMngrFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void MapEditor::mapSendingRequested(const MapInformations * const _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
