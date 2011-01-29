/****************************************************************************
** Meta object code from reading C++ file 'MapEditor.h'
**
** Created: Sat 29. Jan 19:05:57 2011
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   16,   11,   10, 0x0a,
      58,   54,   11,   10, 0x2a,
      75,   10,   11,   10, 0x2a,
      85,   10,   11,   10, 0x0a,
     104,   95,   11,   10, 0x0a,
     123,   10,   11,   10, 0x2a,
     137,  135,   10,   10, 0x08,
     159,  157,   10,   10, 0x08,
     187,  179,   10,   10, 0x08,
     209,  179,   10,   10, 0x08,
     237,  235,   10,   10, 0x08,
     264,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapEditor[] = {
    "MapEditor\0\0bool\0map,ressPack\0"
    "loadMap(QString,QString)\0map\0"
    "loadMap(QString)\0loadMap()\0saveMap()\0"
    "fileName\0saveMapAs(QString)\0saveMapAs()\0"
    "x\0changeMapSizeX(int)\0y\0changeMapSizeY(int)\0"
    "newCase\0changeCasePos(QPoint)\0"
    "changeCurrentCase(QPoint)\0n\0"
    "changeCurrentCaseRSID(int)\0"
    "updateRessourcesList()\0"
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
        case 0: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = loadMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = loadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = saveMapAs((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = saveMapAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: changeMapSizeX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: changeMapSizeY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: changeCasePos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 9: changeCurrentCase((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: changeCurrentCaseRSID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: updateRessourcesList(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
