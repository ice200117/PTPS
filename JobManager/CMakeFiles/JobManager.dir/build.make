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
include JobManager/CMakeFiles/JobManager.dir/depend.make

# Include the progress variables for this target.
include JobManager/CMakeFiles/JobManager.dir/progress.make

# Include the compile flags for this target's objects.
include JobManager/CMakeFiles/JobManager.dir/flags.make

JobManager/moc_JobManager.cxx: JobManager/JobManager.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_JobManager.cxx"
	cd /mnt/disk/PTPS/JobManager && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/JobManager/moc_JobManager.cxx_parameters

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o: JobManager/CMakeFiles/JobManager.dir/flags.make
JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o: JobManager/JobManager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JobManager.dir/JobManager.cpp.o -c /mnt/disk/PTPS/JobManager/JobManager.cpp

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JobManager.dir/JobManager.cpp.i"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/JobManager/JobManager.cpp > CMakeFiles/JobManager.dir/JobManager.cpp.i

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JobManager.dir/JobManager.cpp.s"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/JobManager/JobManager.cpp -o CMakeFiles/JobManager.dir/JobManager.cpp.s

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.requires:
.PHONY : JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.requires

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.provides: JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.requires
	$(MAKE) -f JobManager/CMakeFiles/JobManager.dir/build.make JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.provides.build
.PHONY : JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.provides

JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.provides.build: JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o: JobManager/CMakeFiles/JobManager.dir/flags.make
JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o: JobManager/moc_JobManager.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JobManager.dir/moc_JobManager.cxx.o -c /mnt/disk/PTPS/JobManager/moc_JobManager.cxx

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JobManager.dir/moc_JobManager.cxx.i"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/JobManager/moc_JobManager.cxx > CMakeFiles/JobManager.dir/moc_JobManager.cxx.i

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JobManager.dir/moc_JobManager.cxx.s"
	cd /mnt/disk/PTPS/JobManager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/JobManager/moc_JobManager.cxx -o CMakeFiles/JobManager.dir/moc_JobManager.cxx.s

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.requires:
.PHONY : JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.requires

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.provides: JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.requires
	$(MAKE) -f JobManager/CMakeFiles/JobManager.dir/build.make JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.provides.build
.PHONY : JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.provides

JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.provides.build: JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o

# Object files for target JobManager
JobManager_OBJECTS = \
"CMakeFiles/JobManager.dir/JobManager.cpp.o" \
"CMakeFiles/JobManager.dir/moc_JobManager.cxx.o"

# External object files for target JobManager
JobManager_EXTERNAL_OBJECTS =

bin/libJobManager.so: JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o
bin/libJobManager.so: JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o
bin/libJobManager.so: JobManager/CMakeFiles/JobManager.dir/build.make
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libJobManager.so: bin/libcommon.so
bin/libJobManager.so: bin/libLogger.so
bin/libJobManager.so: bin/libConditionTrigger.so
bin/libJobManager.so: bin/libJobResolver.so
bin/libJobManager.so: bin/libJobScheduler.so
bin/libJobManager.so: bin/libSQLITE_wrapper.so
bin/libJobManager.so: bin/libCondition4DirMonitorAll.so
bin/libJobManager.so: bin/libCondition4Timer.so
bin/libJobManager.so: bin/libCondition4Once.so
bin/libJobManager.so: bin/libCondition4DirMonitor.so
bin/libJobManager.so: bin/libCondition4CycleTimer.so
bin/libJobManager.so: bin/libJobResolver.so
bin/libJobManager.so: bin/libLogger.so
bin/libJobManager.so: bin/libcommon.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libJobManager.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libJobManager.so: JobManager/CMakeFiles/JobManager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../bin/libJobManager.so"
	cd /mnt/disk/PTPS/JobManager && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JobManager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
JobManager/CMakeFiles/JobManager.dir/build: bin/libJobManager.so
.PHONY : JobManager/CMakeFiles/JobManager.dir/build

JobManager/CMakeFiles/JobManager.dir/requires: JobManager/CMakeFiles/JobManager.dir/JobManager.cpp.o.requires
JobManager/CMakeFiles/JobManager.dir/requires: JobManager/CMakeFiles/JobManager.dir/moc_JobManager.cxx.o.requires
.PHONY : JobManager/CMakeFiles/JobManager.dir/requires

JobManager/CMakeFiles/JobManager.dir/clean:
	cd /mnt/disk/PTPS/JobManager && $(CMAKE_COMMAND) -P CMakeFiles/JobManager.dir/cmake_clean.cmake
.PHONY : JobManager/CMakeFiles/JobManager.dir/clean

JobManager/CMakeFiles/JobManager.dir/depend: JobManager/moc_JobManager.cxx
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/JobManager /mnt/disk/PTPS /mnt/disk/PTPS/JobManager /mnt/disk/PTPS/JobManager/CMakeFiles/JobManager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : JobManager/CMakeFiles/JobManager.dir/depend

