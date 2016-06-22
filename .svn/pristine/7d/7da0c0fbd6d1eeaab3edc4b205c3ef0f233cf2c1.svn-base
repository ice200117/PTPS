cmake_minimum_required(VERSION 2.6)

include (../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCOMMON_LIB)
endif()


set(Qhdrs DispatcherInterface.h ConditionInterface.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( common SHARED Task.cpp Serialization.cpp ${moc_srcs} DBInterface.cpp)
target_link_libraries(common ${QT_LIBRARIES})

