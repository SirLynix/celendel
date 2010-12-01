/****************************************************************************
** Meta object code from reading C++ file 'Sound.h'
**
** Created: Wed 1. Dec 14:20:44 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VOIP/Sound.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Sound.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOIPSystem__Sound[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      26,   18,   18,   18, 0x0a,
      33,   18,   18,   18, 0x0a,
      49,   41,   18,   18, 0x0a,
      72,   70,   18,   18, 0x0a,
      99,   18,   91,   18, 0x0a,
     113,   18,  108,   18, 0x0a,
     121,   18,   18,   18, 0x0a,
     128,   18,   18,   18, 0x0a,
     137,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VOIPSystem__Sound[] = {
    "VOIPSystem::Sound\0\0stop()\0play()\0"
    "pause()\0samples\0queue(ALshortVector)\0"
    "v\0setVolume(ALfloat)\0ALfloat\0volume()\0"
    "bool\0muted()\0mute()\0unmute()\0testPlaying()\0"
};

const QMetaObject VOIPSystem::Sound::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOIPSystem__Sound,
      qt_meta_data_VOIPSystem__Sound, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOIPSystem::Sound::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOIPSystem::Sound::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOIPSystem::Sound::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOIPSystem__Sound))
        return static_cast<void*>(const_cast< Sound*>(this));
    return QObject::qt_metacast(_clname);
}

int VOIPSystem::Sound::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stop(); break;
        case 1: play(); break;
        case 2: pause(); break;
        case 3: queue((*reinterpret_cast< const ALshortVector(*)>(_a[1]))); break;
        case 4: setVolume((*reinterpret_cast< const ALfloat(*)>(_a[1]))); break;
        case 5: { ALfloat _r = volume();
            if (_a[0]) *reinterpret_cast< ALfloat*>(_a[0]) = _r; }  break;
        case 6: { bool _r = muted();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: mute(); break;
        case 8: unmute(); break;
        case 9: testPlaying(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
