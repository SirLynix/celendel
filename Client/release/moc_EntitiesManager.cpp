/****************************************************************************
** Meta object code from reading C++ file 'EntitiesManager.h'
**
** Created: Thu 14. Apr 16:02:23 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EntitiesManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EntitiesManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EntitiesManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   17,   16,   16, 0x05,
      61,   57,   16,   16, 0x05,
      83,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   57,   16,   16, 0x0a,
     134,  126,   16,   16, 0x0a,
     173,   57,   16,   16, 0x0a,
     198,  196,   16,   16, 0x0a,
     210,   16,   16,   16, 0x08,
     219,   16,   16,   16, 0x08,
     243,   16,   16,   16, 0x08,
     259,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EntitiesManager[] = {
    "EntitiesManager\0\0entity,code\0"
    "injectCode(QString,QString)\0ent\0"
    "deleteEntity(QString)\0updated()\0"
    "updateEntity(EntityInformations)\0"
    "entList\0setEntities(QList<EntityInformations>)\0"
    "entityDeleted(QString)\0m\0setGM(bool)\0"
    "update()\0openContextMenu(QPoint)\0"
    "ac_injectCode()\0ac_deleteEntity()\0"
};

const QMetaObject EntitiesManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EntitiesManager,
      qt_meta_data_EntitiesManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EntitiesManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EntitiesManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EntitiesManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EntitiesManager))
        return static_cast<void*>(const_cast< EntitiesManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int EntitiesManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: injectCode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: deleteEntity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: updated(); break;
        case 3: updateEntity((*reinterpret_cast< const EntityInformations(*)>(_a[1]))); break;
        case 4: setEntities((*reinterpret_cast< const QList<EntityInformations>(*)>(_a[1]))); break;
        case 5: entityDeleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: setGM((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: update(); break;
        case 8: openContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 9: ac_injectCode(); break;
        case 10: ac_deleteEntity(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void EntitiesManager::injectCode(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EntitiesManager::deleteEntity(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EntitiesManager::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
