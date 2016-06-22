#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTime>

#include "../PTPS_Slave/PTPS_Slave.h"
#include    "../common/Task.hpp"

#include    "../common/global_def.hpp"

#ifdef DEBUG
    #include    "../JobManager/JobManager.h"
    #include    "../JobScheduler/JobScheduler.h"
#endif


int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	//��ʼ������
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	//���ʻ�
	QTranslator myQtTranslator;
	myQtTranslator.load(QCoreApplication::applicationDirPath()+"/language/qt_zh_CN.qm");
	app.installTranslator(&myQtTranslator);

	//��������
	//QString pluginsDir = QCoreApplication::applicationDirPath()+"/ksplugins";
	//qApp->addLibraryPath(pluginsDir);
    
    qRegisterMetaType<Task>("Task");
    qRegisterMetaType<Resource>("Resource");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::list<Resource> >("std::list<Resource>");

	PTPS_Slave* pSlave = new PTPS_Slave;
	QString resSlave = pSlave->initSystem();
	if ("Successful" != resSlave)
	{
		pSlave->write2Logger(resSlave); //��¼��־
		return 0;
	}
	else
	{
		pSlave->write2Logger("SlaveSystem strated on " + QDateTime::currentDateTime().toString()); //��¼��־
	}
    pSlave->start();

#ifdef DEBUG
    Task t;
    t.taskId = 1;
    strcpy(t.taskInfo.libName, "/mnt/disk/radar/job_frame/lib/alg.so");
    strcpy(t.taskInfo.funName, "alg1");
    strcpy(t.taskInfo.paraType, "ifsd");
    strcpy(t.taskInfo.paraValue[0], "123");
    strcpy(t.taskInfo.paraValue[1], "2.32");
    strcpy(t.taskInfo.paraValue[2], "abcde");
    strcpy(t.taskInfo.paraValue[3], "22.3333333333333");
    //pMaster->getJobManager()->getJobScheduler()->pushTask2Wait(&t);
#endif


	//QString sRes = pMaster->setNewTask2Slave_Master("hehe","haha");
	//QString mRes = pSlave->setTaskFree2Master_Slave("haha","hehe");

	//QObject::connect(&app, SIGNAL(aboutToQuit()), this, SLOT(shutdown()));

	return app.exec();
}
