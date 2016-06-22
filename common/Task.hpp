/**
 *          @file:  Task.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014��01��08�� 10ʱ59��59��
 *       @version:  none
 *          @note:  
 */
#ifndef  TASK_HPP
#define  TASK_HPP

#include  <string.h>
#include  <string>
#include  <QString>
#include  <QObject>
#include  <QDataStream>

#include "common_global.h"
#include    "global_def.hpp"

#define	DEFAULT_LEN 64
#define	PATH_LEN 512
#define PARA_CNT 20
#define PARA_LEN 128


typedef char DateTime[20];  //YYYYMMDDHHMiSS.sss
enum TaskStatus
{
    WAITING = 1,
    RUNNING,
    FINISHED,
    FAILED,
    PAUSED
};
typedef enum TaskStatus TaskStatus;


typedef struct ReturnGenType ReturnGenType;
struct ReturnGenType {
    int len; // void* p ��ָ��ַ���������ݳ��ȣ�������len������4���ֽڡ�
    void* p;
};				/* ----------  end of struct ReturnGenType  ---------- */


/**************paraType�����ж�Ӧ�����ͼ�д�������������������Ϊshort��float����paratypeӦ��"sf", �����ͷ���ֵ֮����')'�ָ�
c:char
S:short
i:integer
l:long
L:long long
f:float
d:double
s:cstring == char* 
p:void* //ͨ������
):��������ͷ���ֵ�ķָ���
v:void //û�з���ֵ��������ֵ�п���
 ***************/

class COMMON_EXPORT TaskInfo// 1
{

public:
    TaskInfo();
    TaskInfo( const TaskInfo &ti );
    ~TaskInfo();
    
    TaskInfo& operator=( const TaskInfo &ti);
    friend QDataStream & operator << (QDataStream &dataStream, const TaskInfo &ti);
    friend QDataStream & operator >> (QDataStream &dataStream, TaskInfo &ti);

    int setRetValue(void* str, int len);
    void* getRetValue(int &len){ len = retLen; return retValue; }
    int setInputValues(void* pIn[PARA_CNT], int len[PARA_CNT]);
    void** getInputValues(int (&len)[PARA_CNT]); 
    int setInputValue(void* pIn, int len, int index);
    void* getInputValue(int &len, int index) { len = inputLens[index]; return inputValues[index] ; }


    int execType; // 0=dll, 1=exe
    int cmd; // 0=start&continue, 1=stop
    int timeout; //�������е����ʱ�� ,��λΪ��
    int priority; // ���ȼ� //
    char libName[PATH_LEN];
    char funName[DEFAULT_LEN];
    char paraType[PARA_CNT];
    char paraValue[PARA_CNT][PARA_LEN];

private:
    int inputLens[PARA_CNT]; //ָ��inputValues��Ӧindex�Ĳ�������
    void* inputValues[PARA_CNT]; //�������еĲ�������
    int retLen;  //ָ��retValue�ĳ���
    void* retValue; //�������еķ�������
};

/**
 *        @class:  Task
 *        @brief:  A job include one or many tasks.
 *       @author:  liu bin , ice200117@126.com
 *         @note:  
 */
class COMMON_EXPORT Task
{
    public:
        Task();
        Task (TaskInfo ti);                             /* constructor */
        ~Task();

        bool operator<( const Task &t) const; 
        bool operator==( const Task &t);
        bool operator()( Task *t1, Task *t2);
        Task& operator=( const Task &t); 

        friend QDataStream & operator << (QDataStream &dataStream, const Task &t);
        friend QDataStream & operator >> (QDataStream &dataStream, Task &t);
        
        int calWeight();

        long long taskId;
        DateTime beginTime;
        DateTime endTime;
        char host[DEFAULT_LEN];
        int mpiPid; //mpi process id
        int pid; //process id
        int threadId;
        TaskStatus status; //  1 waiting, 2 running , 3 finished ok, -1: failed  	
        TaskInfo taskInfo; // specified by user.
        int m_seconds; //���񴴽���ʱ�䣨�룩
}; /* -----  end of class Task  ----- */

class COMMON_EXPORT Resource
{
    public:
        Resource();
        int rank;
        QString nodeName;
        bool operator==(const  Resource &t);
        bool operator<( const Resource &t) const;
        friend QDataStream & operator << (QDataStream &dataStream, const Resource &re);
        friend QDataStream & operator >> (QDataStream &dataStream, Resource &re);

        Resource& operator=( const Resource& r); 
};

#endif   /* ----- #ifndef TASK_HPP  ----- */