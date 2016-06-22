
include( ../qt.cmake )
include( ../common.cmake )


if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITION4DIRMONITORALL_EXPORTS )
endif()

set(Qhdrs Condition4DirMonitorAll.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Condition4DirMonitorAll SHARED Condition4DirMonitorAll.cpp  ${moc_srcs})
target_link_libraries(Condition4DirMonitorAll ${QT_LIBRARIES} common JobResolver)


