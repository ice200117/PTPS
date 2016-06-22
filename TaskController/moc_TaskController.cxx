/****************************************************************************
** Meta object code from reading C++ file 'TaskController.h'
**
** Created: Fri Jul 4 16:27:44 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TaskController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TaskController[] = {

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
      26,   24,   16,   15, 0x05,
      58,   24,   16,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,  101,   16,   15, 0x0a,
     140,  138,   16,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TaskController[] = {
    "TaskController\0\0QString\0,\0"
    "signalSendResult(Task,Resource)\0"
    "signalSendRes(QString,std::list<Resource>)\0"
    "t,r\0slotHandleNewTask(Task,Resource)\0"
    "t\0slotHandleResult(Task)\0"
};

void TaskController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TaskController *_t = static_cast<TaskController *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalSendResult((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->signalSendRes((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->slotHandleNewTask((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->slotHandleResult((*reinterpret_cast< Task(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TaskController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TaskController::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TaskController,
      qt_meta_data_TaskController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TaskController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TaskController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TaskController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TaskController))
        return static_cast<void*>(const_cast< TaskController*>(this));
    return QThread::qt_metacast(_clname);
}

int TaskController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QString TaskController::signalSendResult(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
QString TaskController::signalSendRes(QString _t1, std::list<Resource> _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
