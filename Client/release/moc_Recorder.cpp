/****************************************************************************
** Meta object code from reading C++ file 'Recorder.h'
**
** Created: Wed 1. Dec 14:20:43 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VOIP/Recorder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Recorder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOIPSystem__Recorder[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   21,   21,   21, 0x0a,
      61,   21,   21,   21, 0x0a,
      84,   74,   21,   21, 0x0a,
     102,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VOIPSystem__Recorder[] = {
    "VOIPSystem::Recorder\0\0readyRead(ALshortVector)\0"
    "startRecord()\0stopRecord()\0frameSize\0"
    "setFrameSize(int)\0capture()\0"
};

const QMetaObject VOIPSystem::Recorder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOIPSystem__Recorder,
      qt_meta_data_VOIPSystem__Recorder, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOIPSystem::Recorder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOIPSystem::Recorder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOIPSystem::Recorder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOIPSystem__Recorder))
        return static_cast<void*>(const_cast< Recorder*>(this));
    return QObject::qt_metacast(_clname);
}

int VOIPSystem::Recorder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead((*reinterpret_cast< ALshortVector(*)>(_a[1]))); break;
        case 1: startRecord(); break;
        case 2: stopRecord(); break;
        case 3: setFrameSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: capture(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VOIPSystem::Recorder::readyRead(ALshortVector _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
