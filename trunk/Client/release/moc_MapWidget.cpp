/****************************************************************************
** Meta object code from reading C++ file 'MapWidget.h'
**
** Created: Sat 5. Feb 21:33:40 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,
      38,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   10,   10,   10, 0x0a,
      89,   10,   10,   10, 0x0a,
     112,  104,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapWidget[] = {
    "MapWidget\0\0newCase\0mapClicked(QPoint)\0"
    "highlightedCaseChanged(QPoint)\0"
    "openMapInfoDialog()\0setMap(MapPtr)\0"
    "x,y,w,h\0setView(int,int,int,int)\0"
};

const QMetaObject MapWidget::staticMetaObject = {
    { &QSFMLCanvas::staticMetaObject, qt_meta_stringdata_MapWidget,
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
    return QSFMLCanvas::qt_metacast(_clname);
}

int MapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSFMLCanvas::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mapClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: highlightedCaseChanged((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: openMapInfoDialog(); break;
        case 3: setMap((*reinterpret_cast< MapPtr(*)>(_a[1]))); break;
        case 4: setView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
        _id -= 5;
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
static const uint qt_meta_data_MapWidgetScroll[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      23,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapWidgetScroll[] = {
    "MapWidgetScroll\0\0ref()\0sizeUpdate()\0"
};

const QMetaObject MapWidgetScroll::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_MapWidgetScroll,
      qt_meta_data_MapWidgetScroll, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapWidgetScroll::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapWidgetScroll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapWidgetScroll::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapWidgetScroll))
        return static_cast<void*>(const_cast< MapWidgetScroll*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int MapWidgetScroll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ref(); break;
        case 1: sizeUpdate(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
