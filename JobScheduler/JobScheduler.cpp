#include "JobScheduler.h"


JobScheduler::JobScheduler(void)
{
    m_waitTDList.clear();
}

JobScheduler::~JobScheduler(void)
{
}

void JobScheduler::pushTasksAndSort(list<Task*> lt)
{
    QMutexLocker locker(&mutex4waitTDList);

    list<Task*>::iterator it;
    for(it = lt.begin(); it != lt.end(); it++){
        if((*it)->status == WAITING){
            idebug("taskId = %lld\n", (*it)->taskId);
            m_waitTDList.push_back(*it);
        }
    }
	if (m_waitTDList.size() > 0)
		m_waitTDList.sort(Task());
}

void JobScheduler::pushTask2Wait(Task *pt)
{
    QMutexLocker locker(&mutex4waitTDList);

    if( pt->status == WAITING) m_waitTDList.push_back(pt);
	if (m_waitTDList.size() > 0)
		m_waitTDList.sort(Task());
}

void JobScheduler::sortWaitList()
{
    QMutexLocker locker(&mutex4waitTDList);

	if (m_waitTDList.size() > 0)
		m_waitTDList.sort(Task());
}


Task* JobScheduler::getWaitTask()
{
	{
		QMutexLocker locker(&mutex4cmdTDList);

		if(m_cmdTDList.size() > 0){
			Task *pt = m_cmdTDList.front(); 
			m_cmdTDList.pop_front();
			idebug( "have taskId %lld\n", pt->taskId);
			return pt;
		}
	}

	{
		QMutexLocker locker(&mutex4waitTDList);

		if(m_waitTDList.size() > 0){
			Task *pt = m_waitTDList.front();
			m_waitTDList.pop_front();
			idebug( "have taskId %lld\n", pt->taskId);
			return pt;
		}else{
			return NULL;
		}
	}
}

void JobScheduler::stopTask(Task *pt)
{
	QMutexLocker locker(&mutex4cmdTDList);

    if(pt->status == RUNNING){
        pt->taskInfo.cmd = 1;
	    m_cmdTDList.push_back(pt);
    }else{
        printf("taskId %lld is not running, can not stop!", pt->taskId);
    }
}

void JobScheduler::removeTaskFromWaitList(Task *pt)
{
    QMutexLocker locker(&mutex4waitTDList);

    if( pt->status == WAITING) {
        list<Task*>::iterator it = find(m_waitTDList.begin(), m_waitTDList.end(), pt);
        if(it != m_waitTDList.end()){
            m_waitTDList.erase(it);
        }
    }
}
