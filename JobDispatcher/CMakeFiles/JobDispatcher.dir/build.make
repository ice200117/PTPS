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
include JobDispatcher/CMakeFiles/JobDispatcher.dir/depend.make

# Include the progress variables for this target.
include JobDispatcher/CMakeFiles/JobDispatcher.dir/progress.make

# Include the compile flags for this target's objects.
include JobDispatcher/CMakeFiles/JobDispatcher.dir/flags.make

JobDispatcher/moc_JobDispatcher.cxx: JobDispatcher/JobDispatcher.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_JobDispatcher.cxx"
	cd /mnt/disk/PTPS/JobDispatcher && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/JobDispatcher/moc_JobDispatcher.cxx_parameters

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o: JobDispatcher/CMakeFiles/JobDispatcher.dir/flags.make
JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o: JobDispatcher/JobDispatcher.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o -c /mnt/disk/PTPS/JobDispatcher/JobDispatcher.cpp

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.i"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/JobDispatcher/JobDispatcher.cpp > CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.i

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.s"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/JobDispatcher/JobDispatcher.cpp -o CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.s

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.requires:
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.requires

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.provides: JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.requires
	$(MAKE) -f JobDispatcher/CMakeFiles/JobDispatcher.dir/build.make JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.provides.build
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.provides

JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.provides.build: JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o: JobDispatcher/CMakeFiles/JobDispatcher.dir/flags.make
JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o: JobDispatcher/moc_JobDispatcher.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o -c /mnt/disk/PTPS/JobDispatcher/moc_JobDispatcher.cxx

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.i"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/JobDispatcher/moc_JobDispatcher.cxx > CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.i

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.s"
	cd /mnt/disk/PTPS/JobDispatcher && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/JobDispatcher/moc_JobDispatcher.cxx -o CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.s

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.requires:
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.requires

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.provides: JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.requires
	$(MAKE) -f JobDispatcher/CMakeFiles/JobDispatcher.dir/build.make JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.provides.build
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.provides

JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.provides.build: JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o

# Object files for target JobDispatcher
JobDispatcher_OBJECTS = \
"CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o" \
"CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o"

# External object files for target JobDispatcher
JobDispatcher_EXTERNAL_OBJECTS =

bin/libJobDispatcher.so: JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o
bin/libJobDispatcher.so: JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o
bin/libJobDispatcher.so: JobDispatcher/CMakeFiles/JobDispatcher.dir/build.make
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libJobDispatcher.so: bin/libcommon.so
bin/libJobDispatcher.so: bin/libLogger.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libJobDispatcher.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libJobDispatcher.so: JobDispatcher/CMakeFiles/JobDispatcher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../bin/libJobDispatcher.so"
	cd /mnt/disk/PTPS/JobDispatcher && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JobDispatcher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
JobDispatcher/CMakeFiles/JobDispatcher.dir/build: bin/libJobDispatcher.so
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/build

JobDispatcher/CMakeFiles/JobDispatcher.dir/requires: JobDispatcher/CMakeFiles/JobDispatcher.dir/JobDispatcher.cpp.o.requires
JobDispatcher/CMakeFiles/JobDispatcher.dir/requires: JobDispatcher/CMakeFiles/JobDispatcher.dir/moc_JobDispatcher.cxx.o.requires
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/requires

JobDispatcher/CMakeFiles/JobDispatcher.dir/clean:
	cd /mnt/disk/PTPS/JobDispatcher && $(CMAKE_COMMAND) -P CMakeFiles/JobDispatcher.dir/cmake_clean.cmake
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/clean

JobDispatcher/CMakeFiles/JobDispatcher.dir/depend: JobDispatcher/moc_JobDispatcher.cxx
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/JobDispatcher /mnt/disk/PTPS /mnt/disk/PTPS/JobDispatcher /mnt/disk/PTPS/JobDispatcher/CMakeFiles/JobDispatcher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : JobDispatcher/CMakeFiles/JobDispatcher.dir/depend
