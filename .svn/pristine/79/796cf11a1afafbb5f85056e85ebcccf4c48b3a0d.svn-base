
include ( ../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DDISPLAYER_EXPORTS)
endif()

set(Qhdrs Displayer.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})

add_library( Displayer SHARED Displayer.cpp ${moc_srcs})
target_link_libraries(Displayer ${QT_LIBRARIES})

