# Install script for directory: /mnt/disk/PTPS

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/mnt/disk/PTPS/common/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Logger/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/JobResolver/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Condition4DirMonitor/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Condition4DirMonitorAll/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Condition4Once/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Condition4Timer/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Condition4CycleTimer/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/ConditionTrigger/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/CZMQ_Worker/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Displayer/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/JobDispatcher/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/JobScheduler/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/SQLITE_wrapper/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/JobManager/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/InterfaceSingle4Master/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/InterfaceSingle4Slave/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/MsgReceiver/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/TaskExecutor/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/TaskController/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/Supporter_BSH/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/PTPS_Master/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/PTPS_Slave/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/PTPS/cmake_install.cmake")
  INCLUDE("/mnt/disk/PTPS/ZMQ_BROKER/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/mnt/disk/PTPS/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/mnt/disk/PTPS/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
