
include ( ../qt.cmake ) 
include (../zmq.cmake)
include (../common.cmake )
include (../mpi.cmake)
include ( ../dyncall.cmake )



IF(USE_MPI)
    add_executable( PTPS4SLAVE main.cpp)
    target_link_libraries(PTPS4SLAVE ${QT_LIBRARIES}
    common
    Logger
    SlaveInterfaceMPI
    PTPS_Slave
    TaskController
    TaskExecutor
    )
ENDIF(USE_MPI)
