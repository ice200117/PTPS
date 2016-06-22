


if(MSVC)
    include_directories(F:/Lice/work/Scheduler/PTPS/dyncall-0.8/include)
    link_directories(F:/Lice/work/Scheduler/PTPS/dyncall-0.8/lib)
    link_libraries( libdyncall_s libdynload_s )
else()
    include_directories(/mnt/disk/soft/dyncall/include )
    link_directories(/mnt/disk/soft/dyncall/lib )
    link_libraries( dyncall_s dynload_s )
endif()
