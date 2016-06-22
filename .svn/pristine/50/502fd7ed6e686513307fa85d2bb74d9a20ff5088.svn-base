include ( ../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DJOBRESOLVER_EXPORTS )
endif()


set(Qhdrs JobResolver.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( JobResolver SHARED JobResolver.cpp ${moc_srcs})
target_link_libraries(JobResolver ${QT_LIBRARIES} Logger common)
