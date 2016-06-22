/****************************************************************************
** Meta object code from reading C++ file 'JobDispatcher.h'
**
** Created: Tue Jul 29 10:20:43 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "JobDispatcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JobDispatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JobDispatcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   23,   15,   14, 0x05,
      75,   73,   15,   14, 0x05,
     109,   14,  103,   14, 0x05,
     137,   14,   15,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     170,   14,   15,   14, 0x0a,
     202,  197,   15,   14, 0x0a,
     251,  234,   15,   14, 0x0a,
     309,  300,   15,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JobDispatcher[] = {
    "JobDispatcher\0\0QString\0,\0"
    "signalDispatcherTaskOnDispatcher(Task,Resource)\0"
    "t\0signalChangeTaskState(Task)\0Task*\0"
    "signalApplyNewTask(QString)\0"
    "signalRedoTask(std::list<Task*>)\0"
    "slotHandleNewTask(QString)\0t,re\0"
    "slotHandleResult(Task,Resource)\0"
    "nodeName,resList\0"
    "slotPushNodeRes(std::string,std::list<Resource>)\0"
    "nodeName\0slotRemoveRes(std::string)\0"
};

void JobDispatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        JobDispatcher *_t = static_cast<JobDispatcher *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalDispatcherTaskOnDispatcher((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->signalChangeTaskState((*reinterpret_cast< Task(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { Task* _r = _t->signalApplyNewTask((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Task**>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->signalRedoTask((*reinterpret_cast< std::list<Task*>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->slotHandleNewTask((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->slotHandleResult((*reinterpret_cast< Task(*)>(_a[1])),(*reinterpret_cast< Resource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->slotPushNodeRes((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::list<Resource>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: { QString _r = _t->slotRemoveRes((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData JobDispatcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject JobDispatcher::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_JobDispatcher,
      qt_meta_data_JobDispatcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JobDispatcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JobDispatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JobDispatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JobDispatcher))
        return static_cast<void*>(const_cast< JobDispatcher*>(this));
    return QThread::qt_metacast(_clname);
}

int JobDispatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
QString JobDispatcher::signalDispatcherTaskOnDispatcher(Task _t1, Resource _t2)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
QString JobDispatcher::signalChangeTaskState(Task _t1)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
Task * JobDispatcher::signalApplyNewTask(QString _t1)
{
    Task* _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
QString JobDispatcher::signalRedoTask(std::list<Task*> _t1)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
