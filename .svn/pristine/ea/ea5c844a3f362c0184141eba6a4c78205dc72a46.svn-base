include ( ../qt.cmake )
include (../common.cmake )
include (../mpi.cmake)


if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DMASTERINTERFACEMPI_EXPORTS )
endif()

set(Qhdrs MasterInterfaceMPI.hpp SlaveCommnicator.hpp)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( MasterInterfaceMPI SHARED MasterInterfaceMPI.cpp  SlaveCommnicator.cpp ${moc_srcs})
target_link_libraries(MasterInterfaceMPI ${QT_LIBRARIES} common JobDispatcher)
