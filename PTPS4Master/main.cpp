#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTime>
#include  <list>

#include "../common/Task.hpp"
#include "../PTPS_Master/PTPS_Master.h"

#ifdef DEBUG
    #include    "../JobManager/JobManager.h"
    #include    "../JobScheduler/JobScheduler.h"
#endif

int main(int argc, char **argv)
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
    
    qRegisterMetaType<Task>("Task");
    qRegisterMetaType<Resource>("Resource");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::list<Resource> >("std::list<Resource>");

	PTPS_Master* pMaster = new PTPS_Master;
	QString resMaster = pMaster->initSystem();
	if ("Successful" != resMaster)
	{
		pMaster->write2Logger(resMaster); //记录日志
		return 0;
	}
	else
	{
		pMaster->write2Logger("MasterSystem strated on " + QDateTime::currentDateTime().toString()); //记录日志
	}


	pMaster->testJob("START#Job_FJ_Debug");
	
#ifdef DEBUG
    Task t;
    t.taskId = 1;
    strcpy(t.taskInfo.libName, "/mnt/disk/radar/job_frame/lib/alg.so");
    strcpy(t.taskInfo.funName, "alg1");
    strcpy(t.taskInfo.paraType, "ifpd)p");
    //strcpy(t.taskInfo.paraValue[0], "123");
    int i = 123;
    t.taskInfo.setInputValue(&i, sizeof(int), 0);
    //strcpy(t.taskInfo.paraValue[1], "2.32");
    float f = 2.32;
    t.taskInfo.setInputValue(&f, sizeof(float), 1);
    //strcpy(t.taskInfo.paraValue[2], "abcde");
    char* s = "abcde";
    //t.taskInfo.setInputValue(s, strlen(s)+1, 2);
    t.taskInfo.setInputValue(s, 6, 2);
    //strcpy(t.taskInfo.paraValue[3], "22.3333333333333");
    double d = 22.333333333333;
    t.taskInfo.setInputValue(&d, sizeof(double), 3);
    t.status = WAITING;

    //pMaster->getJobManager()->getJobScheduler()->pushTask2Wait(&t);
#endif


	//QString sRes = pMaster->setNewTask2Slave_Master("hehe","haha");
	//QString mRes = pSlave->setTaskFree2Master_Slave("haha","hehe");

	//QObject::connect(&app, SIGNAL(aboutToQuit()), this, SLOT(shutdown()));

	return app.exec();
}
