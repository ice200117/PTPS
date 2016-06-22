/****************************************************************************
** Meta object code from reading C++ file 'InterfaceSingle4Slave.h'
**
** Created: Fri Jul 4 16:27:39 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "InterfaceSingle4Slave.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterfaceSingle4Slave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterfaceSingle4Slave[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   31,   23,   22, 0x05,
      81,   31,   23,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     142,   31,   23,   22, 0x0a,
     193,  181,   23,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InterfaceSingle4Slave[] = {
    "InterfaceSingle4Slave\0\0QString\0,\0"
    "signalHandleResult2JobDispatcher(Task,Resource)\0"
    "signalSendRes2JobDispatcher(std::string,std::list<Resource>)\0"
    "slotHandleResult2Master(Task,Resource)\0"
    "nodeName,lr\0slotSendRes2Master(QString,std::list<Resource>)\0"
};

void InterfaceSingle4Slave::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InterfaceSingle4Slave *_t = static_cast<InterfaceSingle4Slave *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalHandleResult2JobDispatcher((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->signalSendRes2JobDispatcher((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->slotHandleResult2Master((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->slotSendRes2Master((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InterfaceSingle4Slave::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InterfaceSingle4Slave::staticMetaObject = {
    { &Slave2MasterInterface::staticMetaObject, qt_meta_stringdata_InterfaceSingle4Slave,
      qt_meta_data_InterfaceSingle4Slave, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InterfaceSingle4Slave::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InterfaceSingle4Slave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InterfaceSingle4Slave::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceSingle4Slave))
        return static_cast<void*>(const_cast< InterfaceSingle4Slave*>(this));
    return Slave2MasterInterface::qt_metacast(_clname);
}

int InterfaceSingle4Slave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Slave2MasterInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
QString InterfaceSingle4Slave::signalHandleResult2JobDispatcher(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
QString InterfaceSingle4Slave::signalSendRes2JobDispatcher(std::string _t1, std::list<Resource> _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
