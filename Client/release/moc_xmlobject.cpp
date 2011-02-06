/****************************************************************************
** Meta object code from reading C++ file 'xmlobject.h'
**
** Created: Sun 6. Feb 14:59:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Shared/XML/xmlobject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xmlobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XMLObject[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,
      36,   11,   10,   10, 0x05,
      71,   56,   10,   10, 0x05,
     106,   11,   10,   10, 0x05,
     138,  131,   10,   10, 0x05,
     169,  162,   10,   10, 0x05,
     184,  162,   10,   10, 0x05,
     206,  197,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_XMLObject[] = {
    "XMLObject\0\0message\0alertGM(QString)\0"
    "alertOwner(QString)\0message,patern\0"
    "alertPlayers(QString,PlayerPatern)\0"
    "alertAllPlayers(QString)\0patern\0"
    "useObject(ObjectPatern)\0damage\0"
    "destroyed(int)\0damaged(int)\0isScript\0"
    "used(bool)\0"
};

const QMetaObject XMLObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XMLObject,
      qt_meta_data_XMLObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLObject))
        return static_cast<void*>(const_cast< XMLObject*>(this));
    return QObject::qt_metacast(_clname);
}

int XMLObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: alertGM((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: alertOwner((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: alertPlayers((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< PlayerPatern(*)>(_a[2]))); break;
        case 3: alertAllPlayers((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: useObject((*reinterpret_cast< ObjectPatern(*)>(_a[1]))); break;
        case 5: destroyed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: damaged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: used((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void XMLObject::alertGM(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XMLObject::alertOwner(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XMLObject::alertPlayers(QString _t1, PlayerPatern _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XMLObject::alertAllPlayers(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XMLObject::useObject(ObjectPatern _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void XMLObject::destroyed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void XMLObject::damaged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void XMLObject::used(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
