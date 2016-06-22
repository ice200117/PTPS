/****************************************************************************
** Meta object code from reading C++ file 'JobManager.h'
**
** Created: Fri Jul 4 16:27:35 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "JobManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JobManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JobManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   12,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   11,   12,   11, 0x0a,
      77,   11,   12,   11, 0x0a,
      98,   11,   12,   11, 0x0a,
     130,   11,  124,   11, 0x0a,
     156,   11,   12,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JobManager[] = {
    "JobManager\0\0QString\0signalSendNewTask(QString)\0"
    "slotHandleNewCommand(QString)\0"
    "slotExecJob(QString)\0slotChangeTaskState(Task)\0"
    "Task*\0slotApplyNewTask(QString)\0"
    "slotRedoTask(std::list<Task*>)\0"
};

void JobManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        JobManager *_t = static_cast<JobManager *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->signalSendNewTask((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->slotHandleNewCommand((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->slotExecJob((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->slotChangeTaskState((*reinterpret_cast< Task(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { Task* _r = _t->slotApplyNewTask((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Task**>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->slotRedoTask((*reinterpret_cast< std::list<Task*>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData JobManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject JobManager::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_JobManager,
      qt_meta_data_JobManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JobManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JobManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JobManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JobManager))
        return static_cast<void*>(const_cast< JobManager*>(this));
    return QThread::qt_metacast(_clname);
}

int JobManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
QString JobManager::signalSendNewTask(QString _t1)
{
    QString _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
