#pragma once

#include <QThread>
#include <map>
#include <list>
#include <string>
#include <QMutexLocker>
#include <QMutex>

#include "JobDispatcher_Global.h"
#include "../JobScheduler/JobScheduler.h"

using namespace std;

class QMutex;
class QMutexLocker;

#include <QThread>

class JOBDISPATCHER_IMPEXP JobDispatcher : public QThread
{
	Q_OBJECT

public:
	JobDispatcher(void);
	virtual ~JobDispatcher(void);
	void run();

public slots:
	QString slotHandleNewTask(QString);
	QString slotHandleResult(Task t, Resource re);
	QString slotPushNodeRes(std::string nodeName , std::list<Resource> resList); //�ӽڵ�����ʱ�����ӽڵ����Դ�����ӵ����ڵ����Դ�б���
    QString slotRemoveRes(std::string nodeName);
	
signals:
	QString signalDispatcherTaskOnDispatcher(Task, Resource);
	QString signalChangeTaskState(Task t);
	Task* signalApplyNewTask(QString);
    QString signalRedoTask(std::list<Task*>);

private:
	void freeRes(string nodeName, Resource re); //�ӽڵ�����ִ����Ϻ�֪ͨ���ڵ��ͷ�ʹ�õ���Դ
	void freeRes(Resource re);
	Resource getRes(); //���ڵ��������ʱ���ȴ���Դ�б���Ѱ�ҿ��е��ӽڵ���Դ�������һ����Դ��û�п����򷵻ص�Resource��rank����-1��
	string getNodeName(Resource);

	map<string, list<Resource> > MAP_NODE_PROCS;
	map<string, list<Resource> > MAP_NODE_FREE_PROCS;
	QMutex mutex4MAP_NODE;

	std::list<Task*> m_runningTasks;
    QMutex runListMutex;
};