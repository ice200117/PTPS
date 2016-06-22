/**
 *          @file:  Job.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014��01��08�� 10ʱ59��59��
 *       @version:  none
 *          @note:  
 */
#ifndef  JOB_HPP
#define  JOB_HPP

#include "common_global.h"

#include <QDateTime>

/**************paraType�����ж�Ӧ�����ͼ�д�������������������Ϊshort��float����paratypeӦ��"sf"
b:bool
c:char
S:short
i:integer
l:long
L:long long
f:float
d:double
s:cstring
***************/

typedef enum JobStatus
{
	JOB_WAITING = 1,
	JOB_RUNNING,
	JOB_FINISHED,
	JOB_FAILED
}JobStatus;

typedef struct Jobinfo// 1
{
    int execType;
    int priority; // ���ȼ� //
    //int timer;
    //int templateType;
	QString libName;
	QString funName;
	QString paraType;
	QString paraValue;
    //void* algPara;
    //void* IOPath;
}Jobinfo;

/**
 *        @class:  Job
 *        @brief:  A job include one or many tasks.
 *       @author:  liu bin , ice200117@126.com
 *         @note:  
 */
class COMMON_EXPORT Job
{
public:
	Job(){};									/* constructor */

	inline int calWeight(){return 1;};

//	TaskStatus getStatus() const { return status;}
//	void setStatus(TaskStatus ts){ status = ts;}
//	int gettaskId() const {return taskId;}

// private:
    int taskId;
    QDateTime beginTime;
    QDateTime endTime;
    QString host;
    int mpiPid; //mpi process id
    int pid; //process id
	JobStatus status; //  1 waiting, 2 running , 3 finished ok, -1: failed  	

	Jobinfo taskInfo; // specified by user.

	int m_seconds; //���񴴽���ʱ�䣨�룩
	//int m_weight; //�������ȼ��͵ȴ���ʱ��������Ȩ�أ�����������ȴ����н�������
}; /* -----  end of class Job  ----- */

#endif   /* ----- #ifndef TASK_HPP  ----- */