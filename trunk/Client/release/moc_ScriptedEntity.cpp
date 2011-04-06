/****************************************************************************
** Meta object code from reading C++ file 'ScriptedEntity.h'
**
** Created: Wed 6. Apr 16:38:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Shared/LuaSystem/ScriptedEntity.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptedEntity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptedEntity[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      35,   15,   15,   15, 0x05,
      57,   15,   15,   15, 0x05,
      85,   74,   15,   15, 0x05,
     120,  116,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     138,   15,   15,   15, 0x0a,
     146,   15,   15,   15, 0x0a,
     156,   15,   15,   15, 0x0a,
     167,   15,   15,   15, 0x0a,
     176,   15,   15,   15, 0x0a,
     207,  190,  186,   15, 0x0a,
     242,  237,   15,   15, 0x0a,
     262,  257,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptedEntity[] = {
    "ScriptedEntity\0\0sendGMMsg(QString)\0"
    "sendOwnerMsg(QString)\0sendMsg(QString)\0"
    "msg,regexp\0sendPlayerMsg(QString,QString)\0"
    "msg\0doAction(QString)\0pause()\0unpause()\0"
    "onUpdate()\0onInit()\0onDeath()\0int\0"
    "amount,type,from\0onDamage(int,QString,QString)\0"
    "user\0onUse(QString)\0name\0"
    "callSimpleMethod(QString)\0"
};

const QMetaObject ScriptedEntity::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptedEntity,
      qt_meta_data_ScriptedEntity, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptedEntity::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptedEntity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptedEntity::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptedEntity))
        return static_cast<void*>(const_cast< ScriptedEntity*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptedEntity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendGMMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: sendOwnerMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: sendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: sendPlayerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: doAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: pause(); break;
        case 6: unpause(); break;
        case 7: onUpdate(); break;
        case 8: onInit(); break;
        case 9: onDeath(); break;
        case 10: { int _r = onDamage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: onUse((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: callSimpleMethod((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ScriptedEntity::sendGMMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScriptedEntity::sendOwnerMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScriptedEntity::sendMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScriptedEntity::sendPlayerMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScriptedEntity::doAction(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
