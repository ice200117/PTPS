# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/disk/PTPS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/disk/PTPS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/disk/PTPS/CMakeFiles /mnt/disk/PTPS/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/disk/PTPS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named common

# Build rule for target.
common: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 common
.PHONY : common

# fast build rule for target.
common/fast:
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/build
.PHONY : common/fast

#=============================================================================
# Target rules for targets named Logger

# Build rule for target.
Logger: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Logger
.PHONY : Logger

# fast build rule for target.
Logger/fast:
	$(MAKE) -f Logger/CMakeFiles/Logger.dir/build.make Logger/CMakeFiles/Logger.dir/build
.PHONY : Logger/fast

#=============================================================================
# Target rules for targets named JobResolver

# Build rule for target.
JobResolver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 JobResolver
.PHONY : JobResolver

# fast build rule for target.
JobResolver/fast:
	$(MAKE) -f JobResolver/CMakeFiles/JobResolver.dir/build.make JobResolver/CMakeFiles/JobResolver.dir/build
.PHONY : JobResolver/fast

#=============================================================================
# Target rules for targets named Condition4DirMonitor

# Build rule for target.
Condition4DirMonitor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Condition4DirMonitor
.PHONY : Condition4DirMonitor

# fast build rule for target.
Condition4DirMonitor/fast:
	$(MAKE) -f Condition4DirMonitor/CMakeFiles/Condition4DirMonitor.dir/build.make Condition4DirMonitor/CMakeFiles/Condition4DirMonitor.dir/build
.PHONY : Condition4DirMonitor/fast

#=============================================================================
# Target rules for targets named Condition4DirMonitorAll

# Build rule for target.
Condition4DirMonitorAll: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Condition4DirMonitorAll
.PHONY : Condition4DirMonitorAll

# fast build rule for target.
Condition4DirMonitorAll/fast:
	$(MAKE) -f Condition4DirMonitorAll/CMakeFiles/Condition4DirMonitorAll.dir/build.make Condition4DirMonitorAll/CMakeFiles/Condition4DirMonitorAll.dir/build
.PHONY : Condition4DirMonitorAll/fast

#=============================================================================
# Target rules for targets named Condition4Once

# Build rule for target.
Condition4Once: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Condition4Once
.PHONY : Condition4Once

# fast build rule for target.
Condition4Once/fast:
	$(MAKE) -f Condition4Once/CMakeFiles/Condition4Once.dir/build.make Condition4Once/CMakeFiles/Condition4Once.dir/build
.PHONY : Condition4Once/fast

#=============================================================================
# Target rules for targets named Condition4Timer

# Build rule for target.
Condition4Timer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Condition4Timer
.PHONY : Condition4Timer

# fast build rule for target.
Condition4Timer/fast:
	$(MAKE) -f Condition4Timer/CMakeFiles/Condition4Timer.dir/build.make Condition4Timer/CMakeFiles/Condition4Timer.dir/build
.PHONY : Condition4Timer/fast

#=============================================================================
# Target rules for targets named Condition4CycleTimer

# Build rule for target.
Condition4CycleTimer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Condition4CycleTimer
.PHONY : Condition4CycleTimer

# fast build rule for target.
Condition4CycleTimer/fast:
	$(MAKE) -f Condition4CycleTimer/CMakeFiles/Condition4CycleTimer.dir/build.make Condition4CycleTimer/CMakeFiles/Condition4CycleTimer.dir/build
.PHONY : Condition4CycleTimer/fast

#=============================================================================
# Target rules for targets named ConditionTrigger

# Build rule for target.
ConditionTrigger: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ConditionTrigger
.PHONY : ConditionTrigger

# fast build rule for target.
ConditionTrigger/fast:
	$(MAKE) -f ConditionTrigger/CMakeFiles/ConditionTrigger.dir/build.make ConditionTrigger/CMakeFiles/ConditionTrigger.dir/build
.PHONY : ConditionTrigger/fast

#=============================================================================
# Target rules for targets named CZMQ_Worker

# Build rule for target.
CZMQ_Worker: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 CZMQ_Worker
.PHONY : CZMQ_Worker

# fast build rule for target.
CZMQ_Worker/fast:
	$(MAKE) -f CZMQ_Worker/CMakeFiles/CZMQ_Worker.dir/build.make CZMQ_Worker/CMakeFiles/CZMQ_Worker.dir/build
.PHONY : CZMQ_Worker/fast

#=============================================================================
# Target rules for targets named Displayer

# Build rule for target.
Displayer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Displayer
.PHONY : Displayer

# fast build rule for target.
Displayer/fast:
	$(MAKE) -f Displayer/CMakeFiles/Displayer.dir/build.make Displayer/CMakeFiles/Displayer.dir/build
.PHONY : Displayer/fast

#=============================================================================
# Target rules for targets named JobDispatcher

# Build rule for target.
JobDispatcher: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 JobDispatcher
.PHONY : JobDispatcher

# fast build rule for target.
JobDispatcher/fast:
	$(MAKE) -f JobDispatcher/CMakeFiles/JobDispatcher.dir/build.make JobDispatcher/CMakeFiles/JobDispatcher.dir/build
.PHONY : JobDispatcher/fast

#=============================================================================
# Target rules for targets named JobScheduler

# Build rule for target.
JobScheduler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 JobScheduler
.PHONY : JobScheduler

# fast build rule for target.
JobScheduler/fast:
	$(MAKE) -f JobScheduler/CMakeFiles/JobScheduler.dir/build.make JobScheduler/CMakeFiles/JobScheduler.dir/build
.PHONY : JobScheduler/fast

#=============================================================================
# Target rules for targets named SQLITE_wrapper

# Build rule for target.
SQLITE_wrapper: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SQLITE_wrapper
.PHONY : SQLITE_wrapper

# fast build rule for target.
SQLITE_wrapper/fast:
	$(MAKE) -f SQLITE_wrapper/CMakeFiles/SQLITE_wrapper.dir/build.make SQLITE_wrapper/CMakeFiles/SQLITE_wrapper.dir/build
.PHONY : SQLITE_wrapper/fast

#=============================================================================
# Target rules for targets named JobManager

# Build rule for target.
JobManager: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 JobManager
.PHONY : JobManager

# fast build rule for target.
JobManager/fast:
	$(MAKE) -f JobManager/CMakeFiles/JobManager.dir/build.make JobManager/CMakeFiles/JobManager.dir/build
.PHONY : JobManager/fast

#=============================================================================
# Target rules for targets named InterfaceSingle4Master

# Build rule for target.
InterfaceSingle4Master: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 InterfaceSingle4Master
.PHONY : InterfaceSingle4Master

# fast build rule for target.
InterfaceSingle4Master/fast:
	$(MAKE) -f InterfaceSingle4Master/CMakeFiles/InterfaceSingle4Master.dir/build.make InterfaceSingle4Master/CMakeFiles/InterfaceSingle4Master.dir/build
.PHONY : InterfaceSingle4Master/fast

#=============================================================================
# Target rules for targets named InterfaceSingle4Slave

# Build rule for target.
InterfaceSingle4Slave: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 InterfaceSingle4Slave
.PHONY : InterfaceSingle4Slave

# fast build rule for target.
InterfaceSingle4Slave/fast:
	$(MAKE) -f InterfaceSingle4Slave/CMakeFiles/InterfaceSingle4Slave.dir/build.make InterfaceSingle4Slave/CMakeFiles/InterfaceSingle4Slave.dir/build
.PHONY : InterfaceSingle4Slave/fast

#=============================================================================
# Target rules for targets named MsgReceiver

# Build rule for target.
MsgReceiver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 MsgReceiver
.PHONY : MsgReceiver

# fast build rule for target.
MsgReceiver/fast:
	$(MAKE) -f MsgReceiver/CMakeFiles/MsgReceiver.dir/build.make MsgReceiver/CMakeFiles/MsgReceiver.dir/build
.PHONY : MsgReceiver/fast

#=============================================================================
# Target rules for targets named TaskExecutor

# Build rule for target.
TaskExecutor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TaskExecutor
.PHONY : TaskExecutor

# fast build rule for target.
TaskExecutor/fast:
	$(MAKE) -f TaskExecutor/CMakeFiles/TaskExecutor.dir/build.make TaskExecutor/CMakeFiles/TaskExecutor.dir/build
.PHONY : TaskExecutor/fast

#=============================================================================
# Target rules for targets named TaskController

# Build rule for target.
TaskController: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TaskController
.PHONY : TaskController

# fast build rule for target.
TaskController/fast:
	$(MAKE) -f TaskController/CMakeFiles/TaskController.dir/build.make TaskController/CMakeFiles/TaskController.dir/build
.PHONY : TaskController/fast

#=============================================================================
# Target rules for targets named Supporter_BSH

# Build rule for target.
Supporter_BSH: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Supporter_BSH
.PHONY : Supporter_BSH

# fast build rule for target.
Supporter_BSH/fast:
	$(MAKE) -f Supporter_BSH/CMakeFiles/Supporter_BSH.dir/build.make Supporter_BSH/CMakeFiles/Supporter_BSH.dir/build
.PHONY : Supporter_BSH/fast

#=============================================================================
# Target rules for targets named PTPS_Master

# Build rule for target.
PTPS_Master: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PTPS_Master
.PHONY : PTPS_Master

# fast build rule for target.
PTPS_Master/fast:
	$(MAKE) -f PTPS_Master/CMakeFiles/PTPS_Master.dir/build.make PTPS_Master/CMakeFiles/PTPS_Master.dir/build
.PHONY : PTPS_Master/fast

#=============================================================================
# Target rules for targets named PTPS_Slave

# Build rule for target.
PTPS_Slave: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PTPS_Slave
.PHONY : PTPS_Slave

# fast build rule for target.
PTPS_Slave/fast:
	$(MAKE) -f PTPS_Slave/CMakeFiles/PTPS_Slave.dir/build.make PTPS_Slave/CMakeFiles/PTPS_Slave.dir/build
.PHONY : PTPS_Slave/fast

#=============================================================================
# Target rules for targets named PTPS

# Build rule for target.
PTPS: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PTPS
.PHONY : PTPS

# fast build rule for target.
PTPS/fast:
	$(MAKE) -f PTPS/CMakeFiles/PTPS.dir/build.make PTPS/CMakeFiles/PTPS.dir/build
.PHONY : PTPS/fast

#=============================================================================
# Target rules for targets named ZMQ_BROKER.exe

# Build rule for target.
ZMQ_BROKER.exe: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ZMQ_BROKER.exe
.PHONY : ZMQ_BROKER.exe

# fast build rule for target.
ZMQ_BROKER.exe/fast:
	$(MAKE) -f ZMQ_BROKER/CMakeFiles/ZMQ_BROKER.exe.dir/build.make ZMQ_BROKER/CMakeFiles/ZMQ_BROKER.exe.dir/build
.PHONY : ZMQ_BROKER.exe/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... common"
	@echo "... Logger"
	@echo "... JobResolver"
	@echo "... Condition4DirMonitor"
	@echo "... Condition4DirMonitorAll"
	@echo "... Condition4Once"
	@echo "... Condition4Timer"
	@echo "... Condition4CycleTimer"
	@echo "... ConditionTrigger"
	@echo "... CZMQ_Worker"
	@echo "... Displayer"
	@echo "... JobDispatcher"
	@echo "... JobScheduler"
	@echo "... SQLITE_wrapper"
	@echo "... JobManager"
	@echo "... InterfaceSingle4Master"
	@echo "... InterfaceSingle4Slave"
	@echo "... MsgReceiver"
	@echo "... TaskExecutor"
	@echo "... TaskController"
	@echo "... Supporter_BSH"
	@echo "... PTPS_Master"
	@echo "... PTPS_Slave"
	@echo "... PTPS"
	@echo "... ZMQ_BROKER.exe"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

