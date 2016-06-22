/****************************************************************************
** Meta object code from reading C++ file 'DispatcherInterface.h'
**
** Created: Fri Jul 4 16:28:30 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DispatcherInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DispatcherInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Master2SlaveInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   31,   23,   22, 0x05,
      81,   31,   23,   22, 0x05,
     142,   22,   23,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     185,   31,   23,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Master2SlaveInterface[] = {
    "Master2SlaveInterface\0\0QString\0,\0"
    "signalHandleResult2JobDispatcher(Task,Resource)\0"
    "signalSendRes2JobDispatcher(std::string,std::list<Resource>)\0"
    "signalRemoveRes2JobDispatcher(std::string)\0"
    "slotDispatcherTask2Slave(Task,Resource)\0"
};

void Master2SlaveInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Master2SlaveInterface *_t = static_cast<Master2SlaveInterface *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalHandleResult2JobDispatcher((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->signalSendRes2JobDispatcher((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->signalRemoveRes2JobDispatcher((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->slotDispatcherTask2Slave((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Master2SlaveInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Master2SlaveInterface::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Master2SlaveInterface,
      qt_meta_data_Master2SlaveInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Master2SlaveInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Master2SlaveInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Master2SlaveInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Master2SlaveInterface))
        return static_cast<void*>(const_cast< Master2SlaveInterface*>(this));
    return QThread::qt_metacast(_clname);
}

int Master2SlaveInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
QString Master2SlaveInterface::signalHandleResult2JobDispatcher(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
QString Master2SlaveInterface::signalSendRes2JobDispatcher(std::string _t1, std::list<Resource> _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
QString Master2SlaveInterface::signalRemoveRes2JobDispatcher(std::string _t1)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}
static const uint qt_meta_data_Slave2MasterInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   31,   23,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   31,   23,   22, 0x0a,
     135,  123,   23,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Slave2MasterInterface[] = {
    "Slave2MasterInterface\0\0QString\0,\0"
    "signalDispatcherTask2TaskController(Task,Resource)\0"
    "slotHandleResult2Master(Task,Resource)\0"
    "nodeName,lr\0slotSendRes2Master(QString,std::list<Resource>)\0"
};

void Slave2MasterInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Slave2MasterInterface *_t = static_cast<Slave2MasterInterface *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalDispatcherTask2TaskController((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->slotHandleResult2Master((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->slotSendRes2Master((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Slave2MasterInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Slave2MasterInterface::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Slave2MasterInterface,
      qt_meta_data_Slave2MasterInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Slave2MasterInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Slave2MasterInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Slave2MasterInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Slave2MasterInterface))
        return static_cast<void*>(const_cast< Slave2MasterInterface*>(this));
    return QThread::qt_metacast(_clname);
}

int Slave2MasterInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
QString Slave2MasterInterface::signalDispatcherTask2TaskController(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
