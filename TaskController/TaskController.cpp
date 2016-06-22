#include "TaskController.h"
#include <QHostInfo>
#include <iostream>
#include <QMetaType>
#include  <QDateTime>
#include <QSettings>
#include <QApplication>
#include    "../common/global_def.hpp"
#include    "../Logger/Logger.h"


TaskController::TaskController(void)
{
	
}

TaskController::~TaskController(void)
{

}

void TaskController::initRes()
{
	//��ȡ�ӽڵ�Ļ�������
	m_nodeName = QHostInfo::localHostName();
    QDateTime dt = QDateTime::currentDateTime();
    QTime t = dt.time();
    QString timestamp = dt.toString(Qt::ISODate) + t.toString(".zzz");
    m_nodeName += "_" + timestamp;
	//���������Դ����Ҳ�����ӽڵ�������е��������
    QString exePath = QCoreApplication::applicationDirPath();
    QString ConfigPath = exePath + "/Config/SysConfig.ini";
    QSettings ConfigIniRead (ConfigPath, QSettings::IniFormat);
    m_maxNumRes = ConfigIniRead.value("SubNode/ResourceNum").toInt();
    idebug("%d\n",m_maxNumRes);
    //m_maxNumRes = 1;
	//��ʼ���ӽڵ����Դ�б�
	for(int i=0; i<m_maxNumRes; i++){
		Resource r;
        r.nodeName = m_nodeName;
		r.rank = i;
		m_listRes.push_back(r);
	}
	emit signalSendRes(m_nodeName, m_listRes);
}

QString TaskController::slotHandleNewTask( Task t, Resource r)
{
	QMutexLocker locker(&mutex);
	if(m_mapTaskRes.find(t) == m_mapTaskRes.end()) {
		//Task������
		if(m_mapResTask.find(r) == m_mapResTask.end()){
			//��Դrû�б�ռ��
			strcpy(t.host, m_nodeName.toLocal8Bit());
			t.mpiPid = r.rank;

            if(t.taskInfo.cmd == 0 ){
                TaskExecutor *pte = new TaskExecutor(t);
                qRegisterMetaType<Task>("Task");
                QObject::connect(pte, SIGNAL(signalSendResult2Cont(Task)), this, SLOT(slotHandleResult(Task)),Qt::QueuedConnection);
                m_mapTaskpTaskExe[t] = pte;
                m_mapTaskRes[t] = r;
                m_mapResTask[r] = t;
                pte->start();
            }else{
                printf("taskId %lld is not running, taskInfo.cmd %d is error!\n", t.taskId, t.taskInfo.cmd);
                t.status = FAILED;
	            emit signalSendResult(t, r);
                log(" is not running, taskInfo.cmd is error", t);
            }

		}else{
			//��Դ��ռ�ã��������ڵ�������书��ģ�飬��Դ����������
			std::cout << "Resoucre is busy, Please check JobDispatcher" << std::endl;
            t.status = FAILED;
	        emit signalSendResult(t, r);
            log(" Resource is busy, please check JobDispatcher", t);
			return "failed";
		}
	}else{
		//Task�Ѿ�����
        if(t.taskInfo.cmd == 1){
            // Stop task.
	        TaskExecutor *pte = m_mapTaskpTaskExe[t];
            pte->slotStopTask();
        }else{
            printf("taskId %lld has exist, taskInfo.cmd %d is error!\n", t.taskId, t.taskInfo.cmd);
            log(" has exist, taskInfo.cmd is error", t);
        }
	}
    return "Successful";
}



QString TaskController::slotHandleResult(Task tsk)
{
	QMutexLocker locker(&mutex);
    Task t = tsk;
	TaskExecutor *pte = m_mapTaskpTaskExe[t];
	Resource r = m_mapTaskRes[t];
	emit signalSendResult(t, r);
	if(t.status != RUNNING ){
		pte->disconnect();
		pte->wait();
        delete pte;
		log(" TaskExecutor'Obj delete!",t);

		m_mapTaskpTaskExe.erase(t);
		m_mapTaskRes.erase(t);
		m_mapResTask.erase(r);
	}
    
	return "Successful";
}

void TaskController::log(QString stat, Task &t)
{
    Logger *l = &(Logger::getInstance());
    QString logStr;
    logStr = t.taskInfo.libName;
    logStr += " taskId "; logStr += QString("%1  ").arg(t.taskId);
    logStr += stat;
    l->writeInfo(logStr);
}