/**
 *          @file:  SlaveInterfaceMPI.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月11日 11时59分26秒
 *       @version:  none
 *          @note:  
 */
#ifndef  SLAVEINTERFACEMPI_HPP
#define  SLAVEINTERFACEMPI_HPP
#include <QtCore/qglobal.h>
#include  <QObject>
#include  <QThread>
#include  <QMutex>

#include    "../common/Task.hpp"
#include    "../common/DispatcherInterface.h"

#ifdef SLAVEINTERFACEMPI_EXPORTS
# define SLAVEINTERFACEMPI_IMPEXP Q_DECL_EXPORT
#else
# define SLAVEINTERFACEMPI_IMPEXP Q_DECL_IMPORT
#endif

class SLAVEINTERFACEMPI_IMPEXP SlaveInterfaceMPI : public Slave2MasterInterface
{
    Q_OBJECT
public:
    SlaveInterfaceMPI(void);
	~SlaveInterfaceMPI(void);

	void run();

    void  waitTasks();
    QString initialize();
    void uninitialize();
    void send();
    void recv();
    void responseHeartBeat();
    

public slots:
	QString slotHandleResult2Master(Task, Resource);
	QString slotSendRes2Master(QString nodeName, std::list<Resource> lr);

signals:
	QString signalDispatcherTask2TaskController(Task, Resource);

private:
    char m_portName[1024];
    char m_servName[256];
    char m_errmsg[1024];
    int m_msglen;
    int m_smsglen;
    int m_rmsglen;
    int m_argc;
    char ** m_argv;
	char m_sb[1024];
	char m_rb[1024];
    QMutex mutex;
    QString m_host;
};

#endif   /* ----- #ifndef SLAVEINTERFACEMPI_HPP  ----- */

