#include <time.h>
#include <string.h>
#include "Task.hpp"
#include  <QByteArray>
#include  <assert.h>
#include  <iostream>

/************ Tasko define *****************/


Task::Task()
{
    memset(beginTime, 0, 20) ;
    memset(endTime, 0, 20) ;
    memset(host, 0, DEFAULT_LEN) ;
    mpiPid = -1;
    pid = -1;
    threadId = -1;
    status = WAITING;
    //memset(&taskInfo, 0 ,sizeof(TaskInfo));

    m_seconds = time(NULL);

}

Task::Task(TaskInfo ti)
{
    //taskID = getuuid(); 
    memset(beginTime, 0, 20) ;
    memset(endTime, 0, 20) ;
    memset(host, 0, DEFAULT_LEN) ;
    mpiPid = -1;
    pid = -1;
    threadId = -1;
    status = WAITING;
    taskInfo = ti;
    m_seconds = time(NULL);
}

Task::~Task()
{
}

bool Task::operator<( const Task &t) const 
{ 
    return ( this->taskId < t.taskId);
}

bool Task::operator==( const Task &t)
{ 
    return this->taskId == t.taskId;
}

bool Task::operator()( Task *t1, Task *t2)
{	
    return (t1->calWeight()) < (t2->calWeight());
}

Task& Task::operator=( const Task &t)
{ 
    if ( this != &t) {

        this->taskId = t.taskId;
        strcpy(this->beginTime,t.beginTime);
        strcpy(this->endTime,t.endTime);
        strcpy(this->host,t.host);
        this->mpiPid = t.mpiPid; //mpi process id
        this->pid = t.pid; //process id
        this->threadId = t.threadId;
        this->status = t.status; //  1 waiting, 2 running , 3 finished ok, -1: failed  	
        this->taskInfo = t.taskInfo; // specified by user.
        this->m_seconds = t.m_seconds; //任务创建的时间（秒）
    }
    return *this; 
}

QDataStream & operator<< (QDataStream &dataStream, const Task &t)
{
    dataStream << t.taskId << t.beginTime << t.endTime << t.host << t.mpiPid
        << t.pid << t.threadId << t.status << t.taskInfo <<  t.m_seconds;
    return dataStream;
}

QDataStream & operator>> (QDataStream &dataStream, Task &t)
{
    char *tmp;
    dataStream >> t.taskId ;
    dataStream >> tmp; strcpy(t.beginTime, tmp); delete[] tmp;
    dataStream >> tmp; strcpy(t.endTime, tmp); delete[] tmp;
    dataStream >> tmp; strcpy(t.host, tmp); delete[] tmp;

    dataStream >> t.mpiPid
        >> t.pid >> t.threadId;
    int stat;
    dataStream >> stat; t.status = (TaskStatus)stat;
    dataStream >> t.taskInfo >>  t.m_seconds;
    return dataStream;
}


int Task::calWeight()
{
    int wait_secs = time(NULL) - m_seconds;
    int weight = taskInfo.priority - wait_secs/10;
    std::cout << "weight: " << weight << std::endl;
    return weight;
}



/************ TaskInfo define *****************/

TaskInfo::TaskInfo(){
    execType = 0;
    cmd = 0;
    timeout = 30000; // -1 表示任务运行时间不受限。
    priority = 0; // 优先级 //
    memset(libName, 0, PATH_LEN);
    memset(funName,0,DEFAULT_LEN);
    memset(paraType,0,PARA_CNT);
    memset(paraValue, 0, PARA_CNT * PARA_LEN);
    for(int i = 0; i< PARA_CNT; i++){
        inputValues[i] = NULL; 
    }
    retLen = 0;
    retValue = NULL;
};

TaskInfo::TaskInfo( const TaskInfo &ti )
{
    this->execType = ti.execType;
    this->cmd= ti.cmd;
    this->timeout = ti.timeout;
    this->priority = ti.priority;
    strcpy(this->libName, ti.libName);
    strcpy(this->funName , ti.funName);
    strcpy(this->paraType , ti.paraType);
    for(int i = 0; i< PARA_CNT; i++){
        strcpy(this->paraValue[i], ti.paraValue[i]);
    }       

    for(int i = 0; i< PARA_CNT; i++){
        if(ti.inputValues[i] && ti.inputLens[i] > 0){
            inputLens[i] = ti.inputLens[i];
            inputValues[i] = (char*) calloc(ti.inputLens[i], sizeof(char));
            memcpy(inputValues[i], (char*)ti.inputValues[i], ti.inputLens[i]);
        }else{
            inputLens[i] = 0;
            inputValues[i] = NULL;
        }
    }
    if(ti.retValue && ti.retLen > 0){
        this->retLen = ti.retLen;
        retValue  = (char*) calloc(ti.retLen, sizeof(char));
        memcpy(retValue, (char*)ti.retValue, ti.retLen);
    }else{
        this->retLen = 0;
        this->retValue = NULL;
    }

}

TaskInfo::~TaskInfo(){
    if(this->retValue && this->retLen > 0){
        retLen = 0;
        free(this->retValue);
        this->retValue = NULL;
    }
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        if(inputValues[i] != NULL && inputLens[i] > 0) {
            inputLens[i] = 0;
            free(this->inputValues[i]);
            this->inputValues[i] = NULL;
        }
    }
}

QDataStream & operator<< (QDataStream &dataStream, const TaskInfo &ti)
{
    dataStream << ti.execType << ti.cmd << ti.timeout << ti.priority 
        << ti.libName << ti.funName << ti.paraType ;
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        dataStream << ti.paraValue[i];
    }

    //2014年 05月 19日 星期一 16:40:06 CST 增加通用参数支持
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        dataStream << ti.inputLens[i];
    }
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        if( ti.inputValues[i] && ti.inputLens[i] > 0) {
            QByteArray qba((char*)ti.inputValues[i], ti.inputLens[i]);
            dataStream  << qba;
        }
    }
    dataStream << ti.retLen;
    if(ti.retValue && ti.retLen > 0) {
        QByteArray qba((char*)ti.retValue, ti.retLen);
        dataStream  << qba;
    }
    return dataStream;
}

QDataStream & operator>> (QDataStream &dataStream, TaskInfo &ti)
{    
    char *lb; // ti.libName;
    char *fn; // ti.funName;
    char *pt;  // ti.paraType;
    char *pv;  // ti.paraValue[i];
    dataStream >> ti.execType >> ti.cmd >> ti.timeout >> ti.priority 
        >> lb >> fn >> pt ;
    strcpy(ti.libName, lb);
    strcpy(ti.funName, fn);
    strcpy(ti.paraType, pt);
    delete[] lb;
    delete[] fn;
    delete[] pt;

    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        dataStream >> pv;
        strcpy(ti.paraValue[i], pv);
        delete[] pv;
    }
    //2014年 05月 19日 星期一 16:40:06 CST 增加通用参数支持
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        dataStream >> ti.inputLens[i];
    }
    for( int i = 0  ; i < PARA_CNT ; i++ )
    {
        if( ti.inputLens[i] > 0) {
            //dataStream << ti.inputValues[i];
            QByteArray qba;
            dataStream >> qba;
            assert(qba.size() == ti.inputLens[i]);
            if(ti.inputValues[i]) {
                free(ti.inputValues[i]);
                ti.inputValues[i] =  NULL;
            }
            ti.inputValues[i] = (char*) calloc(ti.inputLens[i], sizeof(char));
            memcpy(ti.inputValues[i], qba.data(), ti.inputLens[i]);
        }
    }

    dataStream >> ti.retLen;
    if(ti.retLen > 0){
        QByteArray qba;
        dataStream >> qba;
        assert(qba.size() == ti.retLen);
        if(ti.retValue) {
            free(ti.retValue);
            ti.retValue =  NULL;
        }
        ti.retValue  = (char*) calloc(ti.retLen, sizeof(char));
        memcpy(ti.retValue, qba.data(), ti.retLen);
    }

    return dataStream;
}


TaskInfo& TaskInfo::operator=( const TaskInfo &ti)
{ 
    if ( this != &ti) {
        this->execType = ti.execType;
        this->cmd= ti.cmd;
        this->timeout = ti.timeout;
        this->priority = ti.priority;
        strcpy(this->libName, ti.libName);
        strcpy(this->funName , ti.funName);
        strcpy(this->paraType , ti.paraType);
        for(int i = 0; i< PARA_CNT; i++){
            strcpy(this->paraValue[i], ti.paraValue[i]);
        }       
        for(int i = 0; i< PARA_CNT; i++){
            if(inputValues[i] && inputLens[i] > 0) {
                inputLens[i] = 0;
                free(inputValues[i]);
                inputValues[i] =  NULL;
            }

            if(ti.inputValues[i] && ti.inputLens[i] > 0){
                inputLens[i] = ti.inputLens[i];
                inputValues[i] = (char*) calloc(ti.inputLens[i], sizeof(char));
                memcpy(inputValues[i], (char*)ti.inputValues[i], ti.inputLens[i]);
            }
        }
        if(this->retValue && this->retLen > 0) {
            free(this->retValue);
            this->retValue =  NULL;
            retLen = 0;
        }
        if(ti.retValue && ti.retLen > 0){
            this->retLen = ti.retLen;
            retValue  = (char*) calloc(ti.retLen, sizeof(char));
            memcpy(retValue, ti.retValue, ti.retLen);
        }    
    }
    return *this; 
}


int TaskInfo::setRetValue(void* p, int len)
{
    if(p){
        if(this->retValue && this->retLen > 0){
            this->retLen = 0;
            free(this->retValue);
            this->retValue = NULL;
        }
        retLen = len;
        retValue = (char*) calloc ( (size_t)(retLen), sizeof(char) );
        if ( retValue==NULL ) {
            fprintf ( stderr, "\ndynamic memory allocation failed\n" );
            exit (1);
        }
        memcpy(retValue, p, retLen);
    }
    return retLen;
}


int TaskInfo::setInputValues(void* pIn[PARA_CNT], int len[PARA_CNT])
{
    for ( int i = 0; i < PARA_CNT; i += 1 ) {
        if(pIn[i]){
            if(inputValues[i] && inputLens[i] > 0){
                inputLens[i] = 0;
                free(inputValues[i]);
                inputValues[i] = NULL;
            }
            inputLens[i] = len[i];
            inputValues[i] = (char*) calloc ( (size_t)(inputLens[i]), sizeof(char) );
            if ( inputValues[i]==NULL ) {
                fprintf ( stderr, "\ndynamic memory allocation failed\n" );
                exit (1);
            }
            memcpy(inputValues[i], pIn[i], inputLens[i]);
        }
    }
    return 0;
}


void** TaskInfo::getInputValues(int (&len)[PARA_CNT])
{ 
    for ( int i = 0; i < PARA_CNT; i += 1 ) {
        len[i] = inputLens[i]; 
    }
    return inputValues; 
}


int TaskInfo::setInputValue(void* pIn, int len, int i)
{
    if(pIn){
        if(inputValues[i] && inputLens[i] > 0){
            inputLens[i] = 0;
            free(inputValues[i]);
            inputValues[i] = NULL;
        }
        inputLens[i] = len;
        inputValues[i] = (char*) calloc ( (size_t)(inputLens[i]), sizeof(char) );
        if ( inputValues[i]==NULL ) {
            fprintf ( stderr, "\ndynamic memory allocation failed\n" );
            exit (1);
        }
        memcpy(inputValues[i], pIn, inputLens[i]);
    }
    return 0;
}

/************ TaskInfo define *****************/
Resource::Resource()
{
}

bool Resource::operator==(const  Resource &t)
{
    return (this->rank == t.rank) && this->nodeName == t.nodeName;
}

bool Resource::operator<( const Resource &t) const 
{
    return (this->rank < t.rank);
}

QDataStream & operator<< (QDataStream &dataStream, const Resource &re)
{
    dataStream << re.nodeName << re.rank;
    return dataStream;
}

QDataStream & operator>> (QDataStream &dataStream, Resource &re)
{
    dataStream >> re.nodeName >> re.rank;
    return dataStream;
}

Resource& Resource::operator=( const Resource& r){ 
    if ( this != &r) {
        this->rank = r.rank;
        this->nodeName = r.nodeName;
    }
    return *this; 
}


