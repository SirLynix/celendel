/****************************************************************************
** Meta object code from reading C++ file 'ScriptManager.h'
**
** Created: Sun 10. Apr 14:34:37 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ScriptManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      64,   51,   14,   14, 0x05,
     100,   15,   14,   14, 0x05,
     135,  122,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     170,  165,   14,   14, 0x0a,
     212,  200,   14,   14, 0x0a,
     244,   14,   14,   14, 0x0a,
     257,   51,   14,   14, 0x0a,
     287,  285,   14,   14, 0x0a,
     311,   14,   14,   14, 0x0a,
     325,   14,   14,   14, 0x0a,
     337,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptManager[] = {
    "ScriptManager\0\0name\0requestScriptDownload(QString)\0"
    "name,content\0sendScriptToServer(QString,QString)\0"
    "deleteScript(QString)\0name,newName\0"
    "renameScript(QString,QString)\0list\0"
    "updateScriptList(QStringList)\0script,text\0"
    "showScriptText(QString,QString)\0"
    "openEditor()\0sendScript(QString,QString)\0"
    "p\0openContextMenu(QPoint)\0ac_download()\0"
    "ac_rename()\0ac_delete()\0"
};

const QMetaObject ScriptManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScriptManager,
      qt_meta_data_ScriptManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptManager))
        return static_cast<void*>(const_cast< ScriptManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScriptManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: requestScriptDownload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: sendScriptToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: deleteScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: renameScript((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: updateScriptList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: showScriptText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: openEditor(); break;
        case 7: sendScript((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: openContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 9: ac_download(); break;
        case 10: ac_rename(); break;
        case 11: ac_delete(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ScriptManager::requestScriptDownload(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScriptManager::sendScriptToServer(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScriptManager::deleteScript(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScriptManager::renameScript(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
