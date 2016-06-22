/****************************************************************************
** Meta object code from reading C++ file 'Condition4CycleTimer.h'
**
** Created: Fri Jul 4 16:27:25 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Condition4CycleTimer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Condition4CycleTimer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Condition4CycleTimer[] = {

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
      22,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Condition4CycleTimer[] = {
    "Condition4CycleTimer\0\0handleOnTime()\0"
};

void Condition4CycleTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Condition4CycleTimer *_t = static_cast<Condition4CycleTimer *>(_o);
        switch (_id) {
        case 0: _t->handleOnTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Condition4CycleTimer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Condition4CycleTimer::staticMetaObject = {
    { &ConditionInterface::staticMetaObject, qt_meta_stringdata_Condition4CycleTimer,
      qt_meta_data_Condition4CycleTimer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Condition4CycleTimer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Condition4CycleTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Condition4CycleTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Condition4CycleTimer))
        return static_cast<void*>(const_cast< Condition4CycleTimer*>(this));
    return ConditionInterface::qt_metacast(_clname);
}

int Condition4CycleTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
