/****************************************************************************
** Meta object code from reading C++ file 'colorpickerwidget.h'
**
** Created: Mon 7. Feb 22:21:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QColorPicker/colorpickerwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colorpickerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorPickerWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   19,   18,   18, 0x0a,
      61,   18,   18,   18, 0x08,
      72,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ColorPickerWidget[] = {
    "ColorPickerWidget\0\0col\0colorChanged(QColor)\0"
    "setColor(QColor)\0pickMode()\0colorChgd()\0"
};

const QMetaObject ColorPickerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ColorPickerWidget,
      qt_meta_data_ColorPickerWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorPickerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorPickerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorPickerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorPickerWidget))
        return static_cast<void*>(const_cast< ColorPickerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ColorPickerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: colorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: pickMode(); break;
        case 3: colorChgd(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ColorPickerWidget::colorChanged(const QColor & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
