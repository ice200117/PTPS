/**
 *          @file  testDB.cpp
 *         @brief  
 *        @author  liubin , ice200117@126.com
 *          @date  2014年05月08日 14时27分34秒
 *       @version  none
 *          @note  
 */

#include    "../common/Task.hpp"
#include    "SQLITE_wrapper.hpp"
#include  <string.h>
#include  <stdio.h>

int main(int argc, char *argv[])
{
    Task t;
    memset(&t, 0, sizeof(Task));
    SQLITE_wrapper db;
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  WAITING;
    db.insertTask("Job1", &t);

    t.taskId = 21414386471;
    printf("===== %lld\n", t.taskId);
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  RUNNING;
    db.insertTask("Job1", &t);

    t.taskId = 2;
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  RUNNING;
    db.insertTask("Job2", &t);


    t.taskId = 3;
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  FAILED;
    db.insertTask("Job2", &t);


    t.taskId = 5;
    strcpy(t.beginTime , "20101101082030.333");
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  FAILED;
    db.insertTask("Job2", &t);

    memset(&t, 0, sizeof(Task));
    t.taskId = 4;
    strcpy(t.taskInfo.paraType, "ss");
    strcpy(t.taskInfo.paraValue[0], "/mnt/disk/");
    strcpy(t.taskInfo.paraValue[1], "cmek.txt");
    t.status =  FINISHED;
    db.insertTask("Job3", &t);

    //JOBID2LISTTASK j2lt = db.queryUnfinishedTasks();
    //JOBID2LISTTASK j2lt = db.queryFailedTasks();
    JOBID2LISTTASK j2lt = db.queryAllTasks();
    //JOBID2LISTTASK j2lt = db.queryTasksByJobId("Job2");
    JOBID2LISTTASK::iterator it = j2lt.begin();
    for(  ; it != j2lt.end() ; it++ )
    {
        list<Task*> lpt = it->second;
        list<Task*>::iterator itl;
        printf("---------------------------------%s\n", it->first.c_str());
        for( itl = lpt.begin() ; itl != lpt.end() ; itl++ )
        {
            long long ll = (*itl)->taskId;
                //printf("===== %lld\n", (*itl)->taskId);
            printf("===== %lld\n", ll);
            printf("===== %s\n", (*itl)->beginTime);
            printf("===== %s\n", (*itl)->taskInfo.paraType);
            printf("===== %s\n", (*itl)->taskInfo.paraValue[0]);
            printf("===== %s\n", (*itl)->taskInfo.paraValue[1]);
        }
        
    }

    return 0;
}
