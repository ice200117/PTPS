
include ( ../qt.cmake ) 
include (../zmq.cmake)
include (../dyncall.cmake)
include (../common.cmake )
include (../sqlite3.cmake)

set(LOCAL_LIBRARIES 
    common
    ConditionTrigger
    CZMQ_Worker
    Displayer
    JobDispatcher
    SQLITE_wrapper
    JobManager
    JobResolver
    JobScheduler
    Logger
    InterfaceSingle4Master
    InterfaceSingle4Slave
    MsgReceiver
    PTPS_Master
    PTPS_Slave
    Supporter_BSH
    TaskController
    TaskExecutor
    )
 
IF(SINGLE)
    add_executable( PTPS main.cpp)
    target_link_libraries(PTPS ${QT_LIBRARIES} ${LOCAL_LIBRARIES})
ENDIF(SINGLE)
