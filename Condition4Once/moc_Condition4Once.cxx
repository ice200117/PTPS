/****************************************************************************
** Meta object code from reading C++ file 'Condition4Once.h'
**
** Created: Fri Jul 4 16:27:21 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Condition4Once.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Condition4Once.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Condition4Once[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Condition4Once[] = {
    "Condition4Once\0\0handleOnTime()\0"
};

void Condition4Once::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Condition4Once *_t = static_cast<Condition4Once *>(_o);
        switch (_id) {
        case 0: _t->handleOnTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Condition4Once::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Condition4Once::staticMetaObject = {
    { &ConditionInterface::staticMetaObject, qt_meta_stringdata_Condition4Once,
      qt_meta_data_Condition4Once, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Condition4Once::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Condition4Once::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Condition4Once::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Condition4Once))
        return static_cast<void*>(const_cast< Condition4Once*>(this));
    return ConditionInterface::qt_metacast(_clname);
}

int Condition4Once::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConditionInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
