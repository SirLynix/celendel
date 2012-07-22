/****************************************************************************
** Meta object code from reading C++ file 'CharactersManager.h'
**
** Created: Sun 22. Jul 20:25:55 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CharactersManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharactersManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CharactersManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   19,   18,   18, 0x0a,
      57,   18,   18,   18, 0x0a,
      81,   18,   18,   18, 0x0a,
      95,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CharactersManager[] = {
    "CharactersManager\0\0list\0"
    "updateCharacterList(QStringList)\0"
    "openContextMenu(QPoint)\0ac_stuffEdi()\0"
    "update()\0"
};

const QMetaObject CharactersManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CharactersManager,
      qt_meta_data_CharactersManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CharactersManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CharactersManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CharactersManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CharactersManager))
        return static_cast<void*>(const_cast< CharactersManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int CharactersManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateCharacterList((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: openContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: ac_stuffEdi(); break;
        case 3: update(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
