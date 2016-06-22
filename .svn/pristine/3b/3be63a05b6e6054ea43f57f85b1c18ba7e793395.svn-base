#include "PTPS_Master.h"

#include <QMenu>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QObject>
#include <QWidget>
#include <QCloseEvent>
#include <QAction>
#include <QPointer>
#include <QCoreApplication>
#include <QString>
#include <QSettings>
#include <QProcess>

#include "../MsgReceiver/MsgReceiver.h"
#include "../JobManager/JobManager.h"
#include "../JobDispatcher/JobDispatcher.h"

#ifdef SINGLE
#include "../InterfaceSingle4Master/InterfaceSingle4Master.h"
#endif

#ifdef USE_MPI
#include "../MasterInterfaceMPI/MasterInterfaceMPI.hpp"
#endif

#include "../Logger/Logger.h"
#include    "../common/global_def.hpp"

PTPS_Master::PTPS_Master( QWidget *parent /*= 0*/ ) : 
													m_MsgReceiver(0), 
													m_JobManager(0),
													m_JobDispatcher(0)
{
	m_pQuitAction = new QAction(QString::fromLocal8Bit("&退出系统程序"), this);
	connect(m_pQuitAction, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()),Qt::QueuedConnection);

	m_pTrayIconMenu = new QMenu((QWidget*)QApplication::desktop());
	//m_pTrayIconMenu->addAction(m_pMinimizeAction);
	//m_pTrayIconMenu->addAction(m_pRestoreAction);
	m_pTrayIconMenu->addSeparator();
	m_pTrayIconMenu->addAction(m_pQuitAction);
	m_pTrayIconMenu->addSeparator();

	m_pTrayIcon = new QSystemTrayIcon(this);
	m_pTrayIcon->setToolTip(tr("批量解码程序"));
	m_pTrayIcon->setIcon(QIcon(":/images/logo.png"));
	m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
	//m_pTrayIcon->showMessage(tr("批量解码程序"),tr("右键查看详细！"),QSystemTrayIcon::Information);
	m_pTrayIcon->show();

	m_ProcessBroker = 0;
	//QString exePath = QCoreApplication::applicationDirPath();
	//QString sysCPath = exePath + "/Config/SysConfig.ini";
	//QSettings sysIniRead (sysCPath, QSettings::IniFormat);
	//m_strConnectType = sysIniRead.value("ConnectType/Type").toString();

}

PTPS_Master::~PTPS_Master(void)
{
	Logger *p = &(Logger::getInstance());
	if (!p) return;
	p->writeInfo("~PTPS_Master");

	if (m_pQuitAction)
	{
		delete m_pQuitAction;
	}
	if (m_pTrayIconMenu)
	{
		delete m_pTrayIconMenu;
	}
	if (m_pTrayIcon)
	{
		delete m_pTrayIcon;
	}

	if (m_MsgReceiver)
	{
		delete m_MsgReceiver;
	}
	if (m_JobManager)
	{
		delete m_JobManager;
	}
	if (m_JobDispatcher)
	{
		delete m_JobDispatcher;
	}

	if (m_ProcessBroker)
	{
		m_ProcessBroker->close();
		delete m_ProcessBroker;
	}
}

QString PTPS_Master::killEveryBroker()
{
#ifdef _WINDOWS
	QProcess myKillProcess;
	myKillProcess.setEnvironment(QProcess::systemEnvironment());
	myKillProcess.start("tasklist");
	if (!myKillProcess.waitForStarted()) return "myKillProcess Error!";
	myKillProcess.waitForReadyRead();
	myKillProcess.waitForFinished();
	QByteArray readAllStandardOutput = myKillProcess.readAllStandardOutput();
	myKillProcess.close();

	QString strTemp = QString(readAllStandardOutput);
	QStringList strListTemp = strTemp.split("\n");
	for (int i = 4;i < strListTemp.size();i++)
	{
		QStringList singleProcInfo = strListTemp[i].split(QRegExp("\\s+"));
		if (singleProcInfo.size()>2 && ( "ZMQ_BROKER.exe" == singleProcInfo[0] ))
		{
			QString strCommand = "taskkill /f /pid " + singleProcInfo[1];
			myKillProcess.start(strCommand);
			myKillProcess.waitForFinished();
			myKillProcess.close();
		}
	}
#else
	QProcess myKillProcess;
	myKillProcess.setEnvironment(QProcess::systemEnvironment());
    myKillProcess.start("pkill -9 ZMQ_BROKER");
    //myKillProcess.start("ps -eo comm,pid");
	if (!myKillProcess.waitForStarted()) return "myKillProcess Error!";
	myKillProcess.waitForReadyRead();
	myKillProcess.waitForFinished();
    QByteArray readAllStandardOutput = myKillProcess.readAllStandardOutput();
	myKillProcess.close();

    //QString strTemp = QString(readAllStandardOutput);
    //QStringList strListTemp = strTemp.split("\n");

    ////printf("%s\n", strListTemp[1].toStdString().c_str());
    //for (int i = 1;i < strListTemp.size();i++)
    //{
        //QStringList singleProcInfo = strListTemp[i].split(QRegExp("\\s+"));
        ////if (singleProcInfo.size()==2 && ( "ZMQ_BROKER.exe" == singleProcInfo[0] ))
        //if ( "ZMQ_BROKER.exe" == singleProcInfo[0] )
        //{
            //printf("%s\n", singleProcInfo[1].toStdString().c_str());
            //QString strCommand = "kill  -9 " + singleProcInfo[1];
            //myKillProcess.start(strCommand);
            //myKillProcess.waitForFinished();
            //myKillProcess.close();
        //}
    //}
#endif

	return "Successful";
}

QString PTPS_Master::startNewBroker()
{
	QString strBrokerPath = QCoreApplication::applicationDirPath();
	strBrokerPath = strBrokerPath + "/" + "ZMQ_BROKER.exe";
	m_ProcessBroker = new QProcess(this);
	m_ProcessBroker->start(strBrokerPath);
	QByteArray  res = m_ProcessBroker->readAllStandardOutput();
	if (!m_ProcessBroker->waitForStarted()){
		return "startBroker fail!";
    }
	return "Successful";
}

QString PTPS_Master::initSystem()
{
	QString strRes = "";
	strRes = killEveryBroker();
	if ( "Successful" != strRes)
	{
		return strRes;
	}
    strRes = startNewBroker();
	if ( "Successful" != strRes)
	{
        idebug("%s\n", strRes.toStdString().c_str());
		return strRes;
	}
    strRes = initMSGRecvier();
    if ( "Successful" != strRes)
    {
        return strRes;
    }
	strRes = initJobManager();
	if ( "Successful" != strRes)
	{
		return strRes;
	}
	strRes = initJobDispather();
	if ( "Successful" != strRes)
	{
		return strRes;
	}
	strRes = initDispatcherInterface();
	if ( "Successful" != strRes)
	{
		return strRes;
	}
	strRes = initConnect();
	if ( "Successful" != strRes)
	{
		return strRes;
	}

	return "Successful";
}

QString PTPS_Master::initMSGRecvier()
{
	m_MsgReceiver = new MsgReceiver();
	//if(1 == m_ArgList.size())
	{
        m_MsgReceiver->m_WorkerIP = "localhost";
        m_MsgReceiver->m_WorkerPort = "5555";
        m_MsgReceiver->m_WorkerID = "echo";
	}
	//else
	//{
	//	if (m_ArgList.size()>=2 && !m_ArgList.at(1).isEmpty()) m_MsgReceiver->m_WorkerIP = m_ArgList.at(1);
	//	if (m_ArgList.size()>=3 && !m_ArgList.at(2).isEmpty()) m_MsgReceiver->m_WorkerPort = m_ArgList.at(2);
	//	if (m_ArgList.size()>=4 && !m_ArgList.at(3).isEmpty()) m_MsgReceiver->m_WorkerID = m_ArgList.at(3);
	//}
    m_MsgReceiver->start();

	//这是一个假的判断，无法判断连接是否成功（连接有时间差）！
	//while(true){
		//QCoreApplication::processEvents();
		//if (m_MsgReceiver->isRunning())
		//{
			//return m_MsgReceiver->getLastError();
		//}
	//}
    return "Successful";
}

QString PTPS_Master::initJobManager()
{
	m_JobManager = new JobManager();
	return "Successful";
}

QString PTPS_Master::initJobDispather()
{
	m_JobDispatcher = new JobDispatcher();
	m_JobDispatcher->start();
	return "Successful";
}

QString PTPS_Master::initDispatcherInterface()
{

#ifdef SINGLE
	m_DispatcherInterface = new InterfaceSingle4Master;
	if (!m_DispatcherInterface) return "InterfaceSingle4Master'OBJ is NULL!";
	return "Successful";
#endif		/* -----  SINGLE  ----- */

#ifdef USE_MPI
    m_DispatcherInterface =  new MasterInterfaceMPI;
    if (!m_DispatcherInterface) return "MasterInterfaceMPI'OBJ is NULL!";
    QString retStr = m_DispatcherInterface->initialize();
    return retStr;
#endif     /* -----  USE_MPI  ----- */

}

QString PTPS_Master::write2Logger( QString strInfo )
{
	Logger *p = &(Logger::getInstance());
	if (!p) return "Logger'OBJ is NULL!";
	return p->writeInfo(strInfo);
}

QString PTPS_Master::initConnect()
{
	if (!m_MsgReceiver || !m_JobManager || !m_JobDispatcher || !m_DispatcherInterface )
	{
		return "Obj is NULL!";
    }

	QString strRes = "connect Fail!";
	if (!connect(m_MsgReceiver,SIGNAL(signalSendNewCommand(QString)),m_JobManager,SLOT(slotHandleNewCommand(QString)),Qt::QueuedConnection))
	{
		return strRes;
	}
    //if (!connect(m_JobManager,SIGNAL(signalSendNewTask(QString)),m_JobDispatcher,SLOT(slotHandleNewTask(QString))))
    //{
        //return strRes;
    //}
	if (!connect(m_JobDispatcher,SIGNAL(signalApplyNewTask(QString)),m_JobManager,SLOT(slotApplyNewTask(QString)), Qt::BlockingQueuedConnection))
	{
		return strRes;
	}
	if (!connect(m_JobDispatcher,SIGNAL(signalChangeTaskState(Task)),m_JobManager,SLOT(slotChangeTaskState(Task)), Qt::DirectConnection))
	{
		return strRes;
	}
	if (!connect(m_JobDispatcher,SIGNAL(signalDispatcherTaskOnDispatcher(Task, Resource)),m_DispatcherInterface,SLOT(slotDispatcherTask2Slave(Task, Resource)), Qt::QueuedConnection))
	{
		return strRes;
	}
    if (!connect(m_DispatcherInterface,SIGNAL(signalHandleResult2JobDispatcher(Task, Resource )),m_JobDispatcher,SLOT(slotHandleResult(Task, Resource )), Qt::DirectConnection))
    {
        return strRes;
    }
    if (!connect(m_DispatcherInterface,SIGNAL(signalSendRes2JobDispatcher(std::string, std::list<Resource>)),m_JobDispatcher,SLOT(slotPushNodeRes(std::string, std::list<Resource>)), Qt::DirectConnection))
    {
        return strRes;
    }
    if (!connect(m_DispatcherInterface,SIGNAL(signalRemoveRes2JobDispatcher(std::string)),m_JobDispatcher,SLOT(slotRemoveRes(std::string)), Qt::DirectConnection))
    {
        return strRes;
    }
	if (!connect(m_JobDispatcher,SIGNAL(signalRedoTask(std::list<Task*>)),m_JobManager,SLOT(slotRedoTask(std::list<Task*>)), Qt::DirectConnection))
	{
		return strRes;
	}
    return "Successful";
}

void PTPS_Master::testJob( QString execJob )
{
	m_JobManager->slotHandleNewCommand(execJob);
}

