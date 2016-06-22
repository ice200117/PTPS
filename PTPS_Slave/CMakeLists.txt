include ( ../qt.cmake )
include (../common.cmake )
include (../dyncall.cmake)

IF(USE_MPI)
    include (../mpi.cmake)
ENDIF(USE_MPI)

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DPTPS_SLAVE_EXPORTS)
endif()

set(Qhdrs PTPS_Slave.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( PTPS_Slave SHARED PTPS_Slave.cpp ${moc_srcs})

IF(SINGLE)
    target_link_libraries(PTPS_Slave ${QT_LIBRARIES} TaskController Logger InterfaceSingle4Slave)
ENDIF(SINGLE)

IF(USE_MPI)
    target_link_libraries(PTPS_Slave ${QT_LIBRARIES} TaskController Logger SlaveInterfaceMPI)
ENDIF(USE_MPI)
