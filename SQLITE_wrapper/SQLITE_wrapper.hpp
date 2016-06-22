/**
 *          @file  SQLITE_wrapper.hpp
 *         @brief  
 *        @author  liubin , ice200117@126.com
 *          @date  2014年05月08日 10时29分18秒
 *       @version  none
 *          @note  
 */
#ifndef  SQLITE_WRAPPER_HPP
#define  SQLITE_WRAPPER_HPP


#include <QtCore/qglobal.h>

#include    "../common/DBInterface.hpp"

#ifdef SQLITE_WRAPPER_EXPORTS
# define SQLITE_WRAPPER_IMPEXP Q_DECL_EXPORT
#else
# define SQLITE_WRAPPER_IMPEXP Q_DECL_IMPORT
#endif

class SQLITE_WRAPPER_IMPEXP SQLITE_wrapper : public DBInterface
{
public:
    SQLITE_wrapper();
    ~SQLITE_wrapper();

    string initialize();
    void	uninitialize();

    int openDB();
    int createTaskTable();
    int closeDB();

    int insertTasks(string JobId, list<Task*> lpt);
    int insertTask(string JobId, Task* pt);
    JOBID2LISTTASK queryUnfinishedTasks();
    JOBID2LISTTASK queryFailedTasks();
    JOBID2LISTTASK queryAllTasks();
    JOBID2LISTTASK queryTasksByJobId(string JobId);
};
#endif   /* ----- #ifndef SQLITE_WRAPPER_HPP  ----- */

