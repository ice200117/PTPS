#pragma once
#include "PTPS_Slave_Global.h"

#include <QObject>

class TaskController;
class Slave2MasterInterface;

class PTPS_SLAVE_IMPEXP PTPS_Slave : public QObject
{
	Q_OBJECT

public:
	PTPS_Slave(void);
	virtual ~PTPS_Slave(void);

	//QString setNewTask_Slave(QString strTask, QString strSlave);
	//QString setTaskFree2Master_Slave(QString strTask, QString strSlave);

	QString initSystem();
	QString write2Logger(QString strInfo);
    Slave2MasterInterface* getSlave2MasterInterface(){ return m_Slave2MasterInterface; }
    void start();

private:
	QString initTaskController();			//启动消息接收器
	QString initDispatcherInterface();	//启动作业分配器

	QString initConnect();				//初始化连接

private:
	TaskController *m_TaskController;
	Slave2MasterInterface *m_Slave2MasterInterface;
};