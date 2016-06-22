include ( ../qt.cmake )
include (../common.cmake )
include (../dyncall.cmake)

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DTASKCONTROLLER_EXPORTS)
endif()

set(Qhdrs TaskController.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( TaskController SHARED TaskController.cpp ${moc_srcs})
target_link_libraries(TaskController ${QT_LIBRARIES} common TaskExecutor)
