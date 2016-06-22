include ( ../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DJOBSCHEDULER_EXPORTS)
endif()

set(Qhdrs JobScheduler.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( JobScheduler SHARED JobScheduler.cpp ${moc_srcs})
target_link_libraries(JobScheduler ${QT_LIBRARIES} common)
