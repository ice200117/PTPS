/**
 *          @file:  SlaveCommnicator.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月17日 15时11分56秒
 *       @version:  none
 *          @note:  
 */
#ifndef  SLAVECOMMNICATOR_HPP
#define  SLAVECOMMNICATOR_HPP

#include <QMutex>
#include  <QThread>
#include "mpi.h"
#include  <string>
#include  <QTimer>
#include  <QTime>

#include    "MasterInterfaceMPI.hpp"
#include    "../common/Task.hpp"

class SlaveCommnicator: public QThread
{
    Q_OBJECT 
    public: 
        SlaveCommnicator(MPI_Comm mc);
        SlaveCommnicator(MPI_Comm mc, MasterInterfaceMPI *pmi);
        ~SlaveCommnicator();

        void startHeartBeat();

        void setMasterInterfaceMPIObj( MasterInterfaceMPI * pmi){ m_pmi = pmi; };
        void setSlotThread(QThread* t) { m_thread = t; };
        QThread* getSlotThread( ){ return m_thread; };

        void send(Task t, Resource re);
        void run();
        void listenSlave();
        void send();
        int recv();
        void stopRun() { m_runnable = false; };

        MPI_Comm m_mc;
        std::string m_nodeName;
        char m_rb[1024];
        char m_sb[1024];
        int m_smsglen;
        int m_rmsglen;
        int m_msglen;
        MasterInterfaceMPI *m_pmi;

    public slots:
        void slotHeartBeat();

    signals:
        QString signalRemoveSlave(std::string);


    private:
        QThread *m_thread;
        QTimer *m_timer;
        QTime m_t;
        QMutex mutex;
        static const int m_timeval = 2000; // ms
        bool m_runnable;
};
#endif   /* ----- #ifndef SLAVECOMMNICATOR_HPP  ----- */

