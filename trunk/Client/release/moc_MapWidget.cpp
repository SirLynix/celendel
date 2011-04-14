/****************************************************************************
** Meta object code from reading C++ file 'MapWidget.h'
**
** Created: Thu 14. Apr 12:13:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,
      38,   11,   10,   10, 0x05,
      74,   69,   10,   10, 0x05,
     108,   99,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     142,   10,   10,   10, 0x0a,
     162,   10,   10,   10, 0x0a,
     182,   10,   10,   10, 0x0a,
     202,  197,   10,   10, 0x0a,
     239,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapWidget[] = {
    "MapWidget\0\0newCase\0mapClicked(QPoint)\0"
    "highlightedCaseChanged(QPoint)\0area\0"
    "mapAreaSelected(MapArea)\0curr,max\0"
    "ressourceLoadingProgress(int,int)\0"
    "repaintBackground()\0openMapInfoDialog()\0"
    "setMap(MapPtr)\0list\0"
    "updateRessources(QMap<QString,RSID>)\0"
    "onUpdate()\0"
};

const QMetaObject MapWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MapWidget,
      qt_meta_data_MapWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapWidget))
        return static_cast<void*>(const_cast< MapWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mapClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: highlightedCaseChanged((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: mapAreaSelected((*reinterpret_cast< MapArea(*)>(_a[1]))); break;
        case 3: ressourceLoadingProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: repaintBackground(); break;
        case 5: openMapInfoDialog(); break;
        case 6: setMap((*reinterpret_cast< MapPtr(*)>(_a[1]))); break;
        case 7: updateRessources((*reinterpret_cast< const QMap<QString,RSID>(*)>(_a[1]))); break;
        case 8: onUpdate(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MapWidget::mapClicked(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapWidget::highlightedCaseChanged(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MapWidget::mapAreaSelected(MapArea _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapWidget::ressourceLoadingProgress(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
