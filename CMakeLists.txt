cmake_minimum_required(VERSION 2.6)

include( common.cmake)

project(PTPS)

#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CONFIGURATION_TYPES Debug;Release)
#SET(CMAKE_INSTALL_PREFIX bin)

add_subdirectory( common )
add_subdirectory( Logger)
add_subdirectory( JobResolver)
add_subdirectory( Condition4DirMonitor)
add_subdirectory( Condition4DirMonitorAll)
add_subdirectory( Condition4Once)
add_subdirectory( Condition4Timer)
add_subdirectory( Condition4CycleTimer)
add_subdirectory( ConditionTrigger)
add_subdirectory( CZMQ_Worker)
add_subdirectory( Displayer)
add_subdirectory( JobDispatcher)
add_subdirectory( JobScheduler)
add_subdirectory( SQLITE_wrapper)
add_subdirectory( JobManager)

IF(SINGLE)
    add_subdirectory( InterfaceSingle4Master)
    add_subdirectory( InterfaceSingle4Slave)
ENDIF(SINGLE)

add_subdirectory( MsgReceiver)
add_subdirectory( TaskExecutor)
add_subdirectory( TaskController)
add_subdirectory( Supporter_BSH)

IF(USE_MPI)
    add_subdirectory( MasterInterfaceMPI)
    add_subdirectory( SlaveInterfaceMPI)
ENDIF(USE_MPI)

add_subdirectory( PTPS_Master)
add_subdirectory( PTPS_Slave)
IF(SINGLE)
    add_subdirectory( PTPS)
ENDIF(SINGLE)

IF(USE_MPI)
    add_subdirectory( PTPS4Master)
    add_subdirectory( PTPS4Slave)
ENDIF(USE_MPI)

add_subdirectory( ZMQ_BROKER )
