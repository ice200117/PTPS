/****************************************************************************
** Meta object code from reading C++ file 'InterfaceSingle4Master.h'
**
** Created: Fri Jul 4 16:27:37 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "InterfaceSingle4Master.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterfaceSingle4Master.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterfaceSingle4Master[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   32,   24,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   32,   24,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InterfaceSingle4Master[] = {
    "InterfaceSingle4Master\0\0QString\0,\0"
    "signalDispatcherTask2TaskController(Task,Resource)\0"
    "slotDispatcherTask2Slave(Task,Resource)\0"
};

void InterfaceSingle4Master::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InterfaceSingle4Master *_t = static_cast<InterfaceSingle4Master *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalDispatcherTask2TaskController((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->slotDispatcherTask2Slave((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InterfaceSingle4Master::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InterfaceSingle4Master::staticMetaObject = {
    { &Master2SlaveInterface::staticMetaObject, qt_meta_stringdata_InterfaceSingle4Master,
      qt_meta_data_InterfaceSingle4Master, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InterfaceSingle4Master::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InterfaceSingle4Master::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InterfaceSingle4Master::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceSingle4Master))
        return static_cast<void*>(const_cast< InterfaceSingle4Master*>(this));
    return Master2SlaveInterface::qt_metacast(_clname);
}

int InterfaceSingle4Master::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Master2SlaveInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
QString InterfaceSingle4Master::signalDispatcherTask2TaskController(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
