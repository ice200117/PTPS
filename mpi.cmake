

#include_directories(  C:\\Program\ Files\\Microsoft\ MPI\\Inc )
#link_directories( C:\\Program\ Files\\Microsoft\ MPI\\Lib\\i386 )
##link_libraries(mpichcxx mpich opa mpl pthread)
#link_libraries(msmpi msmpifec msmpifes msmpifmc msmpifms )


if(MSVC) 
    include_directories(  C:/Program\ Files/MPICH2/include )
    link_directories( C:/Program\ Files/MPICH2/lib )
    #link_libraries(mpichcxx mpich opa mpl pthread)
    link_libraries( cxx fmpich2 fmpich2g fmpich2s mpe mpi )
else()

    find_package(MPI)
    #message(${MPI_CXX_INCLUDE_PATH})
    #message(${MPI_CXX_COMPILER})
    #message(${MPI_CXX_LIBRARIES})
    #message(${CMAKE_CXX_COMPILER})
    #message(${CMAKE_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
    set(CMAKE_C_COMPILER ${MPI_C_COMPILER})
    #message("______________________")
    #message(${CMAKE_CXX_COMPILER})
    #message(${CMAKE_C_COMPILER})
endif()


