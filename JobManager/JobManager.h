#pragma once
#include "JobManager_Global.h"

#include <QThread>
#include <QString>
#include <QMutexLocker>
#include <QMutex>

#include "../common/Task.hpp"
#include "../common/Job.hpp"

#include "../JobScheduler/JobScheduler.h"
#include "../JobResolver/JobResolver.h"
#include "../ConditionTrigger/ConditionTrigger.h"
#include    "../SQLITE_wrapper/SQLITE_wrapper.hpp"

#include <map>

class QMutex;
class QMutexLocker;

class JOBMANAGER_IMPEXP JobManager : public QThread
{
	Q_OBJECT

public:
	JobManager(void);
	virtual ~JobManager(void);
    QString addJobTask(string, Task*);
    QString addJobTasks(string JobId, list<Task*> lpt);
    QString deleteJob(string JobId);

    int pauseJob(string JobId);
    int continueJob(string JobId);
public slots:
	QString slotHandleNewCommand(QString);
	QString slotExecJob(QString);
	QString slotChangeTaskState(Task);
	Task* slotApplyNewTask(QString);
    QString slotRedoTask(std::list<Task*>);


signals:
	QString signalSendNewTask(QString);

private:
    map<std::string, list<Task*> > recoverTasks();
	Task * findTask(const Task& t, string &JobId);

	JobScheduler *m_pJobScheduler;
	JobResolver *m_pJobResolver;
	ConditionTrigger *m_pConditionTrigger;
    SQLITE_wrapper *m_SQLITE_wrapper;

	QMutex m_mutex_MAP_JOBID_LISTTASK;
	map<std::string, list<Task*> > MAP_JOBID_LISTTASK;
};
