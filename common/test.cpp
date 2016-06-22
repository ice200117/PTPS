/**
 *          @file  test.cpp
 *         @brief  
 *        @author  liubin , ice200117@126.com
 *          @date  2014年05月20日 16时18分29秒
 *       @version  none
 *          @note  
 */

#include    "Task.hpp"
#include    "Serialization.hpp"
#include  <QByteArray>
#include  <QBuffer>
#include  <QString>
#include  <QByteArray>
#include  <list>

int main(int argc, char *argv[])
{
    TaskInfo ti;
    char * tmps = "lice";
    char s[5] = "lice";
    printf("strlen = %d\n", strlen(tmps));
    printf("sizeof = %d\n", sizeof(s));
    ti.setRetValue((void*)tmps, (strlen(tmps)+1));
    char *gv; int gi;
    gv = (char*)ti.getRetValue(gi);
    printf ( "%d\n", gi );
    printf ( "%s\n", gv );

    Task t(ti);
    Resource r;
    Serialization se;
    QByteArray qba;
    qba = se.serialize(t, r);
    printf ( "qba.size() = %d\n", qba.size() );


    Task tt;
    Serialization de;
    de.deserialize(qba.data(), qba.size());
    tt = de.t();
    char *v; int i;
    v = (char*)tt.taskInfo.getRetValue(i);
    printf ( "%d\n", i );

    if(v != NULL)printf ( "%s\n", v );


    //Task t3;
    int ini = 12;
    char *ins = "DangDang";
    double ind = 123.123;
    int inVectorInt[3] = {3,4,5};
    void *invalues[PARA_CNT];
    int len[PARA_CNT];
    
    for ( int i = 0; i < PARA_CNT; i += 1 ) {
        invalues[i] = NULL;
        len[i] = 0;
    }
    invalues[0] = &ini;
    invalues[1] = ins;;
    invalues[2] = &ind;
    invalues[3] = &inVectorInt;
    len[0] = sizeof(int);
    len[1] = strlen(ins)+1;
    len[2] = sizeof(double);
    len[3] = sizeof(int)*3;
    t.taskInfo.setInputValues(invalues, len);

    qba = se.serialize(t, r);
    printf ( "--qba.size() = %d\n", qba.size() );


    de.deserialize(qba.data(), qba.size());
    tt = de.t();
    v = (char*)tt.taskInfo.getRetValue(i);
    printf ( "%d\n", i );

    if(v != NULL)printf ( "%s\n", v );
    
    ////Method 1.
    //int lenO[PARA_CNT];
    //void *invaluesO[PARA_CNT];
    //for ( int i = 0; i < PARA_CNT; i += 1 ) {
        //lenO[i] = 0;
        //invaluesO[i] = NULL;
    //}
    //invaluesO[0] = t.taskInfo.getInputValue(lenO[0], 0);
    //invaluesO[1] = t.taskInfo.getInputValue(lenO[1], 1);
    //invaluesO[2] = t.taskInfo.getInputValue(lenO[2], 2);
    //invaluesO[3] = t.taskInfo.getInputValue(lenO[3], 3);
    //printf ( "len 0 = %d\n", lenO[0] );
    //printf ( "in 0 =%d\n",*( (int*)invaluesO[0]));
    //printf ( "len 1 = %d\n", lenO[1] );
    //printf ( "in 1 =%s\n", invaluesO[1] );
    //printf ( "len 2 = %d\n", lenO[2] );
    //printf ( "in 2 =%f\n",*((double*) (invaluesO[2])) );
    //printf ( "len 3 = %d\n", lenO[3] );
    //int *pi = (int*)(invaluesO[3]);
    //for(int i = 0; i< 3; i++){
        //printf ( "in 3 =%d\n", *pi+i);
    //}

    // Method 2.
    int lenO[PARA_CNT];
    void **invaluesO;
    invaluesO  = t.taskInfo.getInputValues(lenO);
    printf ( "len 0 = %d\n", (lenO)[0] );
    printf ( "in 0 =%d\n",*((int*) invaluesO[0]) );
    printf ( "len 1 = %d\n", (lenO)[1] );
    printf ( "in 1 =%s\n", (char*)*(invaluesO+1) );
    printf ( "len 2 = %d\n", (lenO)[2] );
    printf ( "in 2 =%f\n",*((double*) *(invaluesO+2)) );
    printf ( "len 3 = %d\n", (lenO)[3] );
    int *pi = (int*)(invaluesO[3]);
    for(int i = 0; i< 3; i++){
        printf ( "in 3 =%d\n", *pi+i);
    }

    Task* pt1 = &t;
    Task* pt2 = &tt;
    std::list<Task*> lpt;
    lpt.push_back(pt1);
    lpt.push_back(pt2);
    std::list<Task*>::iterator it = find(lpt.begin(), lpt.end(), pt2);

    v = (char*)(*it)->taskInfo.getRetValue(i);
    printf ( "-------%d\n", i );

    if(v != NULL)printf ( "-----------%s\n", v );
    return 0;
}
