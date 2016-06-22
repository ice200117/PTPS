

if(MSVC) 
    include_directories ( F:\\Lice\\work\\Scheduler\\VS_props\\zeromq-3.2.2\\include F:\\Lice\\work\\Scheduler\\VS_props\\czmq-1.3.2\\include)
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        #message("Debug--------")
        link_directories( F:\\Lice\\work\\Scheduler\\VS_props\\zeromq-3.2.2\\lib\\Win32  F:\\Lice\\work\\Scheduler\\VS_props\\czmq-1.3.2\\Debug )
        link_libraries(libzmq_d czmq-1.3.2_d )
    else(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        #message("Release--------")
        link_directories( F:\\Lice\\work\\Scheduler\\VS_props\\zeromq-3.2.2\\lib\\Win32 F:\\Lice\\work\\Scheduler\\VS_props\\czmq-1.3.2\\Release)
        link_libraries(libzmq czmq-1.3.2 )
    endif(${CMAKE_BUILD_TYPE} STREQUAL Debug)

else()

    include_directories ( /mnt/disk/soft/zmq/include /mnt/disk/soft/czmq/include) 
    link_directories( /mnt/disk/soft/zmq/lib /mnt/disk/soft/czmq/lib )
    link_libraries(zmq czmq)
endif()

