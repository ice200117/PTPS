/****************************************************************************
** Meta object code from reading C++ file 'SlaveCommnicator.hpp'
**
** Created: Fri May 23 16:35:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SlaveCommnicator.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SlaveCommnicator.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SlaveCommnicator[] = {

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
      26,   17,   18,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SlaveCommnicator[] = {
    "SlaveCommnicator\0\0QString\0"
    "signalRemoveSlave(std::string)\0"
    "slotHeartBeat()\0"
};

void SlaveCommnicator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SlaveCommnicator *_t = static_cast<SlaveCommnicator *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalRemoveSlave((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: _t->slotHeartBeat(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SlaveCommnicator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SlaveCommnicator::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SlaveCommnicator,
      qt_meta_data_SlaveCommnicator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SlaveCommnicator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SlaveCommnicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SlaveCommnicator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SlaveCommnicator))
        return static_cast<void*>(const_cast< SlaveCommnicator*>(this));
    return QThread::qt_metacast(_clname);
}

int SlaveCommnicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
QString SlaveCommnicator::signalRemoveSlave(std::string _t1)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
