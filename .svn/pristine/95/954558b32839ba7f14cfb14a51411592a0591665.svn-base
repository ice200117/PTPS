#pragma once
#include "TaskExecutor_Global.h"
#include "../common/Task.hpp"
#include <QObject>
#include <QThread>
#include <QProcess>
#include <QTimerEvent>
#include <QMutex>
#include <QTimer>

class TASKEXECUTOR_IMPEXP TaskExecutor : public QThread
{
	Q_OBJECT

public:
	TaskExecutor();
	TaskExecutor(Task t);
	virtual ~TaskExecutor(void);
	void run();
	int alg(Task &t);
	int alg1(Task &t);
    void setTask(Task t){ m_task = t; }
    Task getTask() { return m_task; }
public slots:
    void slotStopTask();
	void slotHandleTimer();
signals:
	void signalSendResult2Cont(Task t);

private:
    void log(QString s);
    int startProcess();
    int loadLib();
	void setTaskBegin();
	void setTaskEnd(int ret);

	int waitForProcessDone();
	void killProcess();
	bool ProcessExist();

	Task m_task;
    int m_childPid;

	qint64 * m_pRunProPID;
	int m_iTimeOutNum;
	bool m_bTimeOut;
	QTimer *m_qTimer;
};

