# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# Include any dependencies generated for this target.
include PTPS_Master/CMakeFiles/PTPS_Master.dir/depend.make

# Include the progress variables for this target.
include PTPS_Master/CMakeFiles/PTPS_Master.dir/progress.make

# Include the compile flags for this target's objects.
include PTPS_Master/CMakeFiles/PTPS_Master.dir/flags.make

PTPS_Master/moc_PTPS_Master.cxx: PTPS_Master/PTPS_Master.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_PTPS_Master.cxx"
	cd /mnt/disk/PTPS/PTPS_Master && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/PTPS_Master/moc_PTPS_Master.cxx_parameters

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o: PTPS_Master/CMakeFiles/PTPS_Master.dir/flags.make
PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o: PTPS_Master/PTPS_Master.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o -c /mnt/disk/PTPS/PTPS_Master/PTPS_Master.cpp

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.i"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/PTPS_Master/PTPS_Master.cpp > CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.i

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.s"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/PTPS_Master/PTPS_Master.cpp -o CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.s

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.requires:
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.requires

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.provides: PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.requires
	$(MAKE) -f PTPS_Master/CMakeFiles/PTPS_Master.dir/build.make PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.provides.build
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.provides

PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.provides.build: PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o: PTPS_Master/CMakeFiles/PTPS_Master.dir/flags.make
PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o: PTPS_Master/moc_PTPS_Master.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o -c /mnt/disk/PTPS/PTPS_Master/moc_PTPS_Master.cxx

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.i"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/PTPS_Master/moc_PTPS_Master.cxx > CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.i

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.s"
	cd /mnt/disk/PTPS/PTPS_Master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/PTPS_Master/moc_PTPS_Master.cxx -o CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.s

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.requires:
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.requires

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.provides: PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.requires
	$(MAKE) -f PTPS_Master/CMakeFiles/PTPS_Master.dir/build.make PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.provides.build
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.provides

PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.provides.build: PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o

# Object files for target PTPS_Master
PTPS_Master_OBJECTS = \
"CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o" \
"CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o"

# External object files for target PTPS_Master
PTPS_Master_EXTERNAL_OBJECTS =

bin/libPTPS_Master.so: PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o
bin/libPTPS_Master.so: PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o
bin/libPTPS_Master.so: PTPS_Master/CMakeFiles/PTPS_Master.dir/build.make
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libPTPS_Master.so: bin/libMsgReceiver.so
bin/libPTPS_Master.so: bin/libJobManager.so
bin/libPTPS_Master.so: bin/libJobDispatcher.so
bin/libPTPS_Master.so: bin/libInterfaceSingle4Master.so
bin/libPTPS_Master.so: bin/libcommon.so
bin/libPTPS_Master.so: bin/libLogger.so
bin/libPTPS_Master.so: bin/libJobManager.so
bin/libPTPS_Master.so: bin/libCZMQ_Worker.so
bin/libPTPS_Master.so: bin/libConditionTrigger.so
bin/libPTPS_Master.so: bin/libCondition4DirMonitorAll.so
bin/libPTPS_Master.so: bin/libCondition4Timer.so
bin/libPTPS_Master.so: bin/libCondition4Once.so
bin/libPTPS_Master.so: bin/libCondition4DirMonitor.so
bin/libPTPS_Master.so: bin/libCondition4CycleTimer.so
bin/libPTPS_Master.so: bin/libJobResolver.so
bin/libPTPS_Master.so: bin/libJobScheduler.so
bin/libPTPS_Master.so: bin/libSQLITE_wrapper.so
bin/libPTPS_Master.so: bin/libLogger.so
bin/libPTPS_Master.so: bin/libcommon.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libPTPS_Master.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libPTPS_Master.so: PTPS_Master/CMakeFiles/PTPS_Master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../bin/libPTPS_Master.so"
	cd /mnt/disk/PTPS/PTPS_Master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PTPS_Master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
PTPS_Master/CMakeFiles/PTPS_Master.dir/build: bin/libPTPS_Master.so
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/build

PTPS_Master/CMakeFiles/PTPS_Master.dir/requires: PTPS_Master/CMakeFiles/PTPS_Master.dir/PTPS_Master.cpp.o.requires
PTPS_Master/CMakeFiles/PTPS_Master.dir/requires: PTPS_Master/CMakeFiles/PTPS_Master.dir/moc_PTPS_Master.cxx.o.requires
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/requires

PTPS_Master/CMakeFiles/PTPS_Master.dir/clean:
	cd /mnt/disk/PTPS/PTPS_Master && $(CMAKE_COMMAND) -P CMakeFiles/PTPS_Master.dir/cmake_clean.cmake
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/clean

PTPS_Master/CMakeFiles/PTPS_Master.dir/depend: PTPS_Master/moc_PTPS_Master.cxx
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/PTPS_Master /mnt/disk/PTPS /mnt/disk/PTPS/PTPS_Master /mnt/disk/PTPS/PTPS_Master/CMakeFiles/PTPS_Master.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PTPS_Master/CMakeFiles/PTPS_Master.dir/depend

