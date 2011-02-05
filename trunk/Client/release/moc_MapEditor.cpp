/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created: Sat 5. Feb 21:35:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapEditor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
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
     180,  178,   10,   10, 0x08,
     202,  200,   10,   10, 0x08,
     230,  222,   10,   10, 0x08,
     252,  222,   10,   10, 0x08,
     280,  278,   10,   10, 0x08,
     307,   10,   10,   10, 0x08,
     330,   10,   10,   10, 0x08,
     343,   10,   10,   10, 0x08,
     359,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapEditor[] = {
    "MapEditor\0\0mapSendingRequested(MapInformations*const)\0"
    "bool\0map,ressPack\0loadMap(QString,QString)\0"
    "map\0loadMap(QString)\0loadMap()\0saveMap()\0"
    "fileName\0saveMapAs(QString)\0saveMapAs()\0"
    "x\0changeMapSizeX(int)\0y\0changeMapSizeY(int)\0"
    "newCase\0changeCasePos(QPoint)\0"
    "changeCurrentCase(QPoint)\0n\0"
    "changeCurrentCaseRSID(int)\0"
    "updateRessourcesList()\0btnMapSend()\0"
    "modifyRssMngr()\0addRssMngr()\0"
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
        case 7: changeMapSizeX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: changeMapSizeY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: changeCasePos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: changeCurrentCase((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 11: changeCurrentCaseRSID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: updateRessourcesList(); break;
        case 13: btnMapSend(); break;
        case 14: modifyRssMngr(); break;
        case 15: addRssMngr(); break;
        default: ;
        }
        _id -= 16;
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
