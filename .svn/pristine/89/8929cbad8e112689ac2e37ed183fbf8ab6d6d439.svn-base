cmake_minimum_required(VERSION 2.6)

include( ../qt.cmake )
include( ../common.cmake )


if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITION4DIRMONITOR_EXPORTS )
  #add_definitions(-DCOMMON_LIB)
  #add_definitions(-DJOBRESOLVER_EXPORTS )
endif()

set(Qhdrs Condition4DirMonitor.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Condition4DirMonitor SHARED Condition4DirMonitor.cpp  ${moc_srcs})

target_link_libraries(Condition4DirMonitor ${QT_LIBRARIES} common JobResolver)

