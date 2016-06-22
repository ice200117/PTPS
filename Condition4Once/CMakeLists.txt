
include( ../qt.cmake )
include( ../common.cmake )

if(MSVC) 
  enable_language(ASM_MASM)
  add_definitions(-DCONDITION4ONCE_EXPORTS)
endif()

set(Qhdrs Condition4Once.h)
QT4_WRAP_CPP(moc_srcs ${Qhdrs})
add_library( Condition4Once SHARED Condition4Once.cpp  ${moc_srcs})

target_link_libraries(Condition4Once ${QT_LIBRARIES} common JobResolver)

