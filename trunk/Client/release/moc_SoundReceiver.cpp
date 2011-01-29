/****************************************************************************
** Meta object code from reading C++ file 'SoundReceiver.h'
**
** Created: Tue 25. Jan 18:45:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VOIP/SoundReceiver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SoundReceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOIPSystem__SoundReceiver[] = {

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
      35,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   63,   26,   26, 0x0a,
      85,   26,   26,   26, 0x08,
     108,   27,   26,   26, 0x08,
     131,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VOIPSystem__SoundReceiver[] = {
    "VOIPSystem::SoundReceiver\0\0samples\0"
    "dataReceived(ALshortVector)\0port\0"
    "setPort(quint16)\0readPendingDatagrams()\0"
    "decoded(ALshortVector)\0update()\0"
};

const QMetaObject VOIPSystem::SoundReceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOIPSystem__SoundReceiver,
      qt_meta_data_VOIPSystem__SoundReceiver, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOIPSystem::SoundReceiver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOIPSystem::SoundReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOIPSystem::SoundReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOIPSystem__SoundReceiver))
        return static_cast<void*>(const_cast< SoundReceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int VOIPSystem::SoundReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataReceived((*reinterpret_cast< const ALshortVector(*)>(_a[1]))); break;
        case 1: setPort((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: readPendingDatagrams(); break;
        case 3: decoded((*reinterpret_cast< const ALshortVector(*)>(_a[1]))); break;
        case 4: update(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VOIPSystem::SoundReceiver::dataReceived(const ALshortVector & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
