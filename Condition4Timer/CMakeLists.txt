
include( ../qt.cmake )
include( ../common.cmake )


if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITION4TIMER_EXPORTS )
endif()

set(Qhdrs Condition4Timer.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Condition4Timer SHARED Condition4Timer.cpp  ${moc_srcs})

target_link_libraries(Condition4Timer ${QT_LIBRARIES} common JobResolver)

