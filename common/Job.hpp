/**
 *          @file:  Job.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年01月08日 10时59分59秒
 *       @version:  none
 *          @note:  
 */
#ifndef  JOB_HPP
#define  JOB_HPP

#include "common_global.h"

#include <QDateTime>

/**************paraType参数中对应的类型简写，比如参数从左到右依次为short，float，则paratype应是"sf"
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
    int priority; // 优先级 //
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

	int m_seconds; //任务创建的时间（秒）
	//int m_weight; //根据优先级和等待的时间计算出的权重，用来对任务等待队列进行排序
}; /* -----  end of class Job  ----- */

#endif   /* ----- #ifndef TASK_HPP  ----- */