#pragma once
#include "PTPS_Master_Global.h"

//#include <QMainWindow>
#include <QObject>
#include <QPointer>
#include <QList>
#include <QMutex>
#include <QProcess>

#include    "../common/DispatcherInterface.h"

class QWidget;
class QCloseEvent;
class QAction;
class QMenu;
class QSystemTrayIcon;

class MsgReceiver;
class JobManager;
class JobDispatcher;

class PTPS_MASTER_IMPEXP PTPS_Master: public QObject/* : public QMainWindow*/
{
	Q_OBJECT

public:
	PTPS_Master(QWidget *parent = 0);
	virtual ~PTPS_Master(void);

	QString initSystem();
	QString write2Logger(QString strInfo);
    JobManager* getJobManager(){return m_JobManager;}
    Master2SlaveInterface* getMaster2SlaveInterface() { return m_DispatcherInterface; }

	void testJob( QString execJob );

private:
	QString initMSGRecvier();			//启动消息接收器
	QString initJobManager();			//启动作业管理器
	QString initJobDispather();			//启动作业分配器
	QString initDispatcherInterface();	//启动作业分配器

	QString initConnect();				//初始化连接

	QString killEveryBroker();
	QString startNewBroker();

private:
	QPointer<QSystemTrayIcon> m_pTrayIcon;
	QPointer<QMenu> m_pTrayIconMenu;

	//QAction *m_pMinimizeAction;
	//QAction *m_pRestoreAction;
	QAction *m_pQuitAction;

private:
	//QList<QString> m_JobExecuteList;
	//QMutex m_JobExecuteMutex;
	//QList<QString> m_JobTemplateList;
	//QMutex m_JobTemplateMutex;
	//QList<QString> m_TaskWaitList;
	//QMutex m_TaskWaitMutex;
	//QList<QString> m_SlaveResList;
	//QMutex m_SlaveResMutex;
    
    //QString m_strConnectType;

	MsgReceiver *m_MsgReceiver;
	JobManager *m_JobManager;
	JobDispatcher *m_JobDispatcher;
    //DispatcherInterface_Master *m_DispatcherInterface;
    Master2SlaveInterface  *m_DispatcherInterface;

	QProcess *m_ProcessBroker;
};
