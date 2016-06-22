/**
 *          @file:  MasterInterfaceMPI.cpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月04日 16时20分36秒
 *       @version:  none
 *          @note:  
 */

#include "MasterInterfaceMPI.hpp"

#include <QSettings>
#include <QApplication>
#include <QStringList> 

#include "../common/Task.hpp"
#include "../common/global_def.hpp"

#include "mpi.h"

#include    "SlaveCommnicator.hpp"
#include <fstream>
#include <iostream>



MasterInterfaceMPI::MasterInterfaceMPI()
{
    memset(m_portName, 0, 1024);
    memset(m_servName, 0, 256);
    memset(m_errmsg, 0, 1024);

    strcpy(m_servName,"MyTest");

    QString exePath = QCoreApplication::applicationDirPath();
    QString mpiCPath = exePath + "/Config/MPIConfig.ini";
    QSettings mpiIniRead (mpiCPath, QSettings::IniFormat);
    m_argc = mpiIniRead.value("MPI_Arg/argc").toInt();
    QStringList argvStrLst = mpiIniRead.value("MPI_Arg/argv").toString().split(" ");
    m_argv  = (char**)calloc(m_argc, sizeof(char*));
    for (int i = 0;i < m_argc;i++)
    {
        std::string tmpStr = argvStrLst[i].toStdString();
        char *tmpChar = (char *)tmpStr.c_str();
        m_argv[i] = tmpChar;
    }
}

MasterInterfaceMPI::~MasterInterfaceMPI()
{
    free(m_argv);
}


QString MasterInterfaceMPI::initialize()
{
    int provided, rank, size, merr;

    idebug("thread is : %d\n", QThread::currentThreadId());

    MPI_Init_thread(&m_argc,&m_argv,MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(size!=1)
    {
        fprintf(stderr,"this MPI serve program only run with 1 process\n");
        fflush(stderr);
        return QString("MasterInterfaceMPI OBJ init failed, size must be one!");
    }

    //为通信子对象设置一个预定义的错误处理函数
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

    // 打开端口
    fprintf(stdout,"process:%d,opening port...\n",rank);
    merr=MPI_Open_port(MPI_INFO_NULL,m_portName);
    // 发布服务
    fprintf(stdout,"process:%d,port opend,at<%s>\n",rank,m_portName);

#ifdef _WINDOWS
    ofstream outputStream("port.txt");
    if(!outputStream) {
        std::cout << "Error opening output stream" << std::endl;
        return "Error opening output stream";
    }
    outputStream << m_portName;
    outputStream.close();

#else
    merr=MPI_Publish_name(m_servName,MPI_INFO_NULL,m_portName);
    idebug("merr = %d\n", merr);
    if(merr)
    {
        MPI_Error_string(merr,m_errmsg,&m_msglen);
        printf("Error in publish_name:\"%s\"\n",m_errmsg);
        fflush(stdout);
        return QString("MasterInterfaceMPI OBJ init failed! ") + QString(m_errmsg);
    }
#endif
    MPI_Barrier(MPI_COMM_WORLD);


    start();
    return QString("Successful");
}


void MasterInterfaceMPI::uninitialize()
{
    std::map<string, SlaveCommnicator*>::iterator it = m_mapNodeName2Comm.begin();
    for(   ; it != m_mapNodeName2Comm.end() ; it++ )
    {
        MPI_Comm_disconnect(&((*it).second->m_mc));
        delete (*it).second;
        m_mapNodeName2Comm.erase(it);
    }

    MPI_Close_port(m_portName);
    int merr=MPI_Unpublish_name(m_servName,MPI_INFO_NULL,m_portName);
    MPI_Finalize();
}

void MasterInterfaceMPI::run(){
    while( true )
    {
        acceptSlave();
    }
}



QString MasterInterfaceMPI::slotDispatcherTask2Slave(Task* t, Resource r)
{
    map<string, SlaveCommnicator*>::iterator it =  m_mapNodeName2Comm.find(r.nodeName.toStdString());
    if(it != m_mapNodeName2Comm.end()){
        (*it).second->send(*t, r);    
    }
    return "Successful";
}


void MasterInterfaceMPI::acceptSlave()
{
    idebug("thread is : %d\n", QThread::currentThreadId());

    std::map<string, SlaveCommnicator*>::iterator it = m_mapNodeName2Comm.begin();
    for(   ; it != m_mapNodeName2Comm.end() ; it++ )
    {
        idebug("size = %d\n", m_mapNodeName2Comm.size());
        int flag;
        //MPI_Comm_test_inter((*it).second->m_mc, &flag);
        //if(flag){ idebug(" flag is true, %d\n", flag);}
        //else{ idebug(" flag is false, %d\n", flag);}
        idebug("comm : %d\n" , (int)(*it).second->m_mc);
    }

    MPI_Comm newcomm;
    int merr;
    QThread * thread = new QThread;
    merr=MPI_Comm_accept(m_portName,MPI_INFO_NULL,0,MPI_COMM_SELF,&newcomm);
    SlaveCommnicator *psc = new SlaveCommnicator(newcomm, this);
    idebug("Accept %d\n", (int)newcomm);
    psc->start();
    psc->startHeartBeat();
    psc->moveToThread(thread);
    psc->setSlotThread(thread);
    thread->start();
}

QString MasterInterfaceMPI::slotRemoveSlave(std::string nodeName)
{
    SlaveCommnicator *psc = m_mapNodeName2Comm[nodeName]; 
    QThread *t = psc->getSlotThread();
    t->quit();
    t->wait();
    psc->stopRun();
    psc->wait();
    idebug("disconnect:  %d\n", (int)psc->m_mc);
    MPI_Comm_disconnect(&(psc->m_mc));
    delete psc;
    delete t;
    
    m_mapNodeName2Comm.erase(nodeName);
    emit signalRemoveRes2JobDispatcher(nodeName);
    idebug("remove Slave %s\n", "!");
    return "Successful";
}

