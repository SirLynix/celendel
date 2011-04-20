/****************************************************************************
** Meta object code from reading C++ file 'TableEditor.h'
**
** Created: Wed 20. Apr 12:17:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TableEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TableEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableLine[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TableLine[] = {
    "TableLine\0\0suicide()\0"
};

const QMetaObject TableLine::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TableLine,
      qt_meta_data_TableLine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TableLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TableLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TableLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableLine))
        return static_cast<void*>(const_cast< TableLine*>(this));
    return QWidget::qt_metacast(_clname);
}

int TableLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: suicide(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TableLine::suicide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_TableEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x0a,
      43,   12,   12,   12, 0x08,
      62,   56,   12,   12, 0x08,
      90,   87,   12,   12, 0x28,
     107,   12,   12,   12, 0x28,
     117,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TableEditor[] = {
    "TableEditor\0\0list\0setList(QStringPairList)\0"
    "deleteLine()\0s1,s2\0addLine(QString,QString)\0"
    "s1\0addLine(QString)\0addLine()\0newLine()\0"
};

const QMetaObject TableEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableEditor,
      qt_meta_data_TableEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TableEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TableEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TableEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableEditor))
        return static_cast<void*>(const_cast< TableEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setList((*reinterpret_cast< const QStringPairList(*)>(_a[1]))); break;
        case 1: deleteLine(); break;
        case 2: addLine((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: addLine((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: addLine(); break;
        case 5: newLine(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
