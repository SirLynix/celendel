/****************************************************************************
** Meta object code from reading C++ file 'EntityMaker.h'
**
** Created: Wed 27. Apr 15:26:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EntityMaker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EntityMaker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Line[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      16,    5,    5,    5, 0x08,
      29,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Line[] = {
    "Line\0\0suicide()\0cbChngd(int)\0tableEditor()\0"
};

const QMetaObject Line::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Line,
      qt_meta_data_Line, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Line::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Line::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Line::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Line))
        return static_cast<void*>(const_cast< Line*>(this));
    return QWidget::qt_metacast(_clname);
}

int Line::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: suicide(); break;
        case 1: cbChngd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: tableEditor(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Line::suicide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_EntityMaker[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   53,   12,   12, 0x08,
      90,   12,   12,   12, 0x08,
     100,   12,   12,   12, 0x08,
     113,   12,   12,   12, 0x08,
     121,   12,   12,   12, 0x08,
     131,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EntityMaker[] = {
    "EntityMaker\0\0name,script\0"
    "sendScript(QString,QString)\0name,ent\0"
    "addLine(QString,EntityData)\0newLine()\0"
    "deleteLine()\0toEdi()\0fromEdi()\0"
    "sndScrpt()\0"
};

const QMetaObject EntityMaker::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EntityMaker,
      qt_meta_data_EntityMaker, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EntityMaker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EntityMaker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EntityMaker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EntityMaker))
        return static_cast<void*>(const_cast< EntityMaker*>(this));
    return QDialog::qt_metacast(_clname);
}

int EntityMaker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendScript((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: addLine((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const EntityData(*)>(_a[2]))); break;
        case 2: newLine(); break;
        case 3: deleteLine(); break;
        case 4: toEdi(); break;
        case 5: fromEdi(); break;
        case 6: sndScrpt(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void EntityMaker::sendScript(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
