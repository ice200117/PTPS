include ( ../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DSUPPORTER_BSH_EXPORTS)
endif()

set(Qhdrs Supporter_BSH.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Supporter_BSH SHARED Supporter_BSH.cpp ${moc_srcs})
target_link_libraries(Supporter_BSH ${QT_LIBRARIES})
