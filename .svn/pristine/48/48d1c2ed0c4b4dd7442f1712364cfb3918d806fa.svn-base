
include( ../qt.cmake )
include( ../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITIONTRIGGER_EXPORTS)
endif()

set(Qhdrs ConditionTrigger.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( ConditionTrigger SHARED ConditionTrigger.cpp  ${moc_srcs})

target_link_libraries(ConditionTrigger ${QT_LIBRARIES} common JobResolver Condition4DirMonitorAll Condition4Timer Condition4Once Condition4DirMonitor Condition4CycleTimer)

