#pragma once
#include "JobScheduler_Global.h"

#include "../common/Task.hpp"
#include "../common/global_def.hpp"

#include <list>

#include <QAtomicPointer>
#include <QMutexLocker>
#include <QMutex>
#include  <iostream>
class QMutex;
class QMutexLocker;

using namespace std;

class JOBSCHEDULER_IMPEXP JobScheduler
{
public:
	JobScheduler(void);
	virtual ~JobScheduler(void);



	void pushTask2Wait(Task *pt);
	void sortWaitList();
	void pushTasksAndSort(list<Task*> lt);
	Task* getWaitTask();
    void stopTask(Task *pt);
    void removeTaskFromWaitList(Task *pt);

private:
	list< Task* > m_waitTDList;
	QMutex mutex4waitTDList;

	list< Task* > m_cmdTDList;
	QMutex mutex4cmdTDList;
	
};
