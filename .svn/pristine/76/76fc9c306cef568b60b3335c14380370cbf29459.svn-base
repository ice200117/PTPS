
include( ../qt.cmake )
include( ../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITION4CYCLETIMER_EXPORTS)
endif()

set(Qhdrs Condition4CycleTimer.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Condition4CycleTimer SHARED Condition4CycleTimer.cpp  ${moc_srcs})

target_link_libraries(Condition4CycleTimer ${QT_LIBRARIES} common JobResolver)

