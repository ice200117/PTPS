include (../qt.cmake )
include (../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DINTERFACESINGLE4SLAVE_EXPORTS)
endif()

set(Qhdrs InterfaceSingle4Slave.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( InterfaceSingle4Slave  SHARED InterfaceSingle4Slave.cpp ${moc_srcs})

target_link_libraries(InterfaceSingle4Slave  ${QT_LIBRARIES} common)

