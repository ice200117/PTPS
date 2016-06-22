include ( ../qt.cmake )
include (../common.cmake )
include (../mpi.cmake)

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DSLAVEINTERFACEMPI_EXPORTS)
endif()

set(Qhdrs SlaveInterfaceMPI.hpp)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( SlaveInterfaceMPI SHARED SlaveInterfaceMPI.cpp ${moc_srcs})
target_link_libraries(SlaveInterfaceMPI ${QT_LIBRARIES} common)
