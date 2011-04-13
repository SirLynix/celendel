/****************************************************************************
** Meta object code from reading C++ file 'ScriptEnvironnement.h'
**
** Created: Wed 13. Apr 18:53:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ScriptEnvironnement.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptEnvironnement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptEnvironnement[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   21,   20,   20, 0x05,
      63,   58,   20,   20, 0x05,
      90,   58,   20,   20, 0x05,
     120,   58,   20,   20, 0x05,
     160,  145,   20,   20, 0x05,
     199,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     233,   20,   20,   20, 0x08,
     247,   20,   20,   20, 0x08,
     268,   20,   20,   20, 0x08,
     292,   20,   20,   20, 0x08,
     322,  311,   20,   20, 0x08,
     355,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ScriptEnvironnement[] = {
    "ScriptEnvironnement\0\0entName\0"
    "entityRequireUpdate(QString)\0ent,\0"
    "sendGMMsg(QString,QString)\0"
    "sendOwnerMsg(QString,QString)\0"
    "sendMsg(QString,QString)\0ent,msg,regexp\0"
    "sendPlayerMsg(QString,QString,QString)\0"
    "characterListUpdated(QStringList)\0"
    "dataChanged()\0s_sendGMMsg(QString)\0"
    "s_sendOwnerMsg(QString)\0s_sendMsg(QString)\0"
    "msg,regexp\0s_sendPlayerMsg(QString,QString)\0"
    "s_registerCharacter()\0"
};

const QMetaObject ScriptEnvironnement::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptEnvironnement,
      qt_meta_data_ScriptEnvironnement, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptEnvironnement::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptEnvironnement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptEnvironnement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptEnvironnement))
        return static_cast<void*>(const_cast< ScriptEnvironnement*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptEnvironnement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: entityRequireUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: sendGMMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: sendOwnerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: sendPlayerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: characterListUpdated((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: dataChanged(); break;
        case 7: s_sendGMMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: s_sendOwnerMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: s_sendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: s_sendPlayerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: s_registerCharacter(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ScriptEnvironnement::entityRequireUpdate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScriptEnvironnement::sendGMMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScriptEnvironnement::sendOwnerMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScriptEnvironnement::sendMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScriptEnvironnement::sendPlayerMsg(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ScriptEnvironnement::characterListUpdated(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
