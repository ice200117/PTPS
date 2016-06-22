/****************************************************************************
** Meta object code from reading C++ file 'MasterInterfaceMPI.hpp'
**
** Created: Fri May 23 16:35:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MasterInterfaceMPI.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MasterInterfaceMPI.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MasterInterfaceMPI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   28,   20,   19, 0x0a,
      80,   71,   20,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MasterInterfaceMPI[] = {
    "MasterInterfaceMPI\0\0QString\0,\0"
    "slotDispatcherTask2Slave(Task*,Resource)\0"
    "nodeName\0slotRemoveSlave(std::string)\0"
};

void MasterInterfaceMPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MasterInterfaceMPI *_t = static_cast<MasterInterfaceMPI *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->slotDispatcherTask2Slave((*reinterpret_cast< Task*(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->slotRemoveSlave((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MasterInterfaceMPI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MasterInterfaceMPI::staticMetaObject = {
    { &Master2SlaveInterface::staticMetaObject, qt_meta_stringdata_MasterInterfaceMPI,
      qt_meta_data_MasterInterfaceMPI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MasterInterfaceMPI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MasterInterfaceMPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MasterInterfaceMPI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MasterInterfaceMPI))
        return static_cast<void*>(const_cast< MasterInterfaceMPI*>(this));
    return Master2SlaveInterface::qt_metacast(_clname);
}

int MasterInterfaceMPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
