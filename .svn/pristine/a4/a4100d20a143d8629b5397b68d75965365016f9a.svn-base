include (../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DINTERFACESINGLE4MASTER_EXPORTS)
endif()

set(Qhdrs InterfaceSingle4Master.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( InterfaceSingle4Master SHARED InterfaceSingle4Master.cpp ${moc_srcs})

target_link_libraries(InterfaceSingle4Master ${QT_LIBRARIES} common)

