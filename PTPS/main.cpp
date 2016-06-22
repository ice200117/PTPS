#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTime>
#include  <QMetaType>
#include <QFile>

#include "../PTPS_Master/PTPS_Master.h"
#include "../PTPS_Slave/PTPS_Slave.h"
#include "../common/Task.hpp"
#include "../common/DispatcherInterface.h"
#include "../Logger/Logger.h"

#ifdef DEBUG
    #include    "../JobManager/JobManager.h"
    #include    "../JobScheduler/JobScheduler.h"
#endif


Q_DECLARE_METATYPE(Resource);
Q_DECLARE_METATYPE(TaskInfo);
Q_DECLARE_METATYPE(Task);

int main(int argc, char **argv)
{
	{
		QApplication app(argc, argv);

		//初始化编码
		QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
		QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
		QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

		//国际化
		QTranslator myQtTranslator;
		myQtTranslator.load(QCoreApplication::applicationDirPath()+"/language/qt_zh_CN.qm");
		app.installTranslator(&myQtTranslator);

		//加载驱动
		//QString pluginsDir = QCoreApplication::applicationDirPath()+"/ksplugins";
		//qApp->addLibraryPath(pluginsDir);


		qRegisterMetaType<Resource>("Resource");
		qRegisterMetaType<TaskInfo>("TaskInfo");
		qRegisterMetaType<Task>("Task");

		Logger *p = &(Logger::getInstance());
		if (!p) return 0;

		QString resLogger = p->createFirstLoggerFile(QApplication::applicationDirPath() + "/Logger");
		if ("Successful" != resLogger)
		{
			return 0;
		}

		PTPS_Master pMaster;
		QString resMaster = pMaster.initSystem();
		if ("Successful" != resMaster)
		{
			pMaster.write2Logger(resMaster); //记录日志
			return 0;
		}
		else
		{
			pMaster.write2Logger("MasterSystem strated."); //记录日志
		}

		PTPS_Slave* pSlave = new PTPS_Slave;
		QString resSlave = pSlave->initSystem();
		if ("Successful" != resSlave)
		{
			pSlave->write2Logger(resSlave); //记录日志
			return 0;
		}
		else
		{
			pSlave->write2Logger("SlaveSystem strated."); //记录日志
		}

		Master2SlaveInterface* pDisMaster = pMaster.getMaster2SlaveInterface();
		Slave2MasterInterface* pDisSlave = pSlave->getSlave2MasterInterface();
		if ( pDisMaster && pDisSlave ){
			QObject::connect(pDisMaster, SIGNAL(signalDispatcherTask2TaskController(Task, Resource)), pDisSlave, SIGNAL(signalDispatcherTask2TaskController(Task, Resource)),Qt::DirectConnection);
			QObject::connect(pDisSlave, SIGNAL(signalHandleResult2JobDispatcher(Task, Resource)), pDisMaster, SIGNAL(signalHandleResult2JobDispatcher(Task, Resource)),Qt::DirectConnection);
			QObject::connect(pDisSlave, SIGNAL(signalSendRes2JobDispatcher(std::string, std::list<Resource>)), pDisMaster, SIGNAL(signalSendRes2JobDispatcher(std::string, std::list<Resource>)),Qt::DirectConnection);
		}

		pSlave->start();

		QString qstrJobIniFile = QCoreApplication::applicationDirPath() + "/Config/" + "WorkJobList.ini";
		QFile qfJobIni(qstrJobIniFile);
		if (!qfJobIni.exists())
		{
			p->writeInfo("WorkJobList.ini not exists! using default.");
		}
		else
		{
			QSettings settingsJobRead(qstrJobIniFile, QSettings::IniFormat);
			QStringList lstStrJobALLKEY = settingsJobRead.allKeys();
			foreach (QString strCurKey,lstStrJobALLKEY)
			{
				QString qsJobName = settingsJobRead.value(strCurKey).toString();
				if (!qsJobName.isEmpty())
				{
					pMaster.testJob( QString("START#") + qsJobName);
				}
			}
		}

#ifdef DEBUG
		Task *pt = new Task;
		pt->taskId = 2141438647111;
		strcpy(pt->taskInfo.libName, "/mnt/disk/radar/job_frame/lib/alg.so");
		strcpy(pt->taskInfo.funName, "alg1");
		strcpy(pt->taskInfo.paraType, "ifpd)p");
		//strcpy(pt->taskInfo.paraValue[0], "123");
		int i = 123;
		pt->taskInfo.setInputValue(&i, sizeof(int), 0);
		//strcpy(pt->taskInfo.paraValue[1], "2.32");
		float f = 2.32;
		pt->taskInfo.setInputValue(&f, sizeof(float), 1);
		//strcpy(pt->taskInfo.paraValue[2], "abcde");
		char* s = "abcde";
		//pt->taskInfo.setInputValue(s, strlen(s)+1, 2);
		pt->taskInfo.setInputValue(s, 6, 2);
		//strcpy(pt->taskInfo.paraValue[3], "22.3333333333333");
		double d = 22.333333333333;
		pt->taskInfo.setInputValue(&d, sizeof(double), 3);
		pt->status = WAITING;

		pMaster.getJobManager()->addJobTask("testJob", pt);


#endif


		//QString sRes = pMaster.setNewTask2Slave_Master("hehe","haha");
		//QString mRes = pSlave->setTaskFree2Master_Slave("haha","hehe");

		//QObject::connect(&app, SIGNAL(aboutToQuit()), pQuitEnt, SLOT(slotHandleQuit()));

		app.exec();
	}

	return 0;
}