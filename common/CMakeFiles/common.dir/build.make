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
include common/CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/common.dir/flags.make

common/moc_DispatcherInterface.cxx: common/DispatcherInterface.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_DispatcherInterface.cxx"
	cd /mnt/disk/PTPS/common && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/common/moc_DispatcherInterface.cxx_parameters

common/moc_ConditionInterface.cxx: common/ConditionInterface.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_ConditionInterface.cxx"
	cd /mnt/disk/PTPS/common && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/common/moc_ConditionInterface.cxx_parameters

common/CMakeFiles/common.dir/Task.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/Task.cpp.o: common/Task.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/CMakeFiles/common.dir/Task.cpp.o"
	cd /mnt/disk/PTPS/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/Task.cpp.o -c /mnt/disk/PTPS/common/Task.cpp

common/CMakeFiles/common.dir/Task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/Task.cpp.i"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/common/Task.cpp > CMakeFiles/common.dir/Task.cpp.i

common/CMakeFiles/common.dir/Task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/Task.cpp.s"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/common/Task.cpp -o CMakeFiles/common.dir/Task.cpp.s

common/CMakeFiles/common.dir/Task.cpp.o.requires:
.PHONY : common/CMakeFiles/common.dir/Task.cpp.o.requires

common/CMakeFiles/common.dir/Task.cpp.o.provides: common/CMakeFiles/common.dir/Task.cpp.o.requires
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/Task.cpp.o.provides.build
.PHONY : common/CMakeFiles/common.dir/Task.cpp.o.provides

common/CMakeFiles/common.dir/Task.cpp.o.provides.build: common/CMakeFiles/common.dir/Task.cpp.o

common/CMakeFiles/common.dir/Serialization.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/Serialization.cpp.o: common/Serialization.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/CMakeFiles/common.dir/Serialization.cpp.o"
	cd /mnt/disk/PTPS/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/Serialization.cpp.o -c /mnt/disk/PTPS/common/Serialization.cpp

common/CMakeFiles/common.dir/Serialization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/Serialization.cpp.i"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/common/Serialization.cpp > CMakeFiles/common.dir/Serialization.cpp.i

common/CMakeFiles/common.dir/Serialization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/Serialization.cpp.s"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/common/Serialization.cpp -o CMakeFiles/common.dir/Serialization.cpp.s

common/CMakeFiles/common.dir/Serialization.cpp.o.requires:
.PHONY : common/CMakeFiles/common.dir/Serialization.cpp.o.requires

common/CMakeFiles/common.dir/Serialization.cpp.o.provides: common/CMakeFiles/common.dir/Serialization.cpp.o.requires
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/Serialization.cpp.o.provides.build
.PHONY : common/CMakeFiles/common.dir/Serialization.cpp.o.provides

common/CMakeFiles/common.dir/Serialization.cpp.o.provides.build: common/CMakeFiles/common.dir/Serialization.cpp.o

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o: common/moc_DispatcherInterface.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o"
	cd /mnt/disk/PTPS/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o -c /mnt/disk/PTPS/common/moc_DispatcherInterface.cxx

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/moc_DispatcherInterface.cxx.i"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/common/moc_DispatcherInterface.cxx > CMakeFiles/common.dir/moc_DispatcherInterface.cxx.i

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/moc_DispatcherInterface.cxx.s"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/common/moc_DispatcherInterface.cxx -o CMakeFiles/common.dir/moc_DispatcherInterface.cxx.s

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.requires:
.PHONY : common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.requires

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.provides: common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.requires
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.provides.build
.PHONY : common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.provides

common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.provides.build: common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o: common/moc_ConditionInterface.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o"
	cd /mnt/disk/PTPS/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/moc_ConditionInterface.cxx.o -c /mnt/disk/PTPS/common/moc_ConditionInterface.cxx

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/moc_ConditionInterface.cxx.i"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/common/moc_ConditionInterface.cxx > CMakeFiles/common.dir/moc_ConditionInterface.cxx.i

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/moc_ConditionInterface.cxx.s"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/common/moc_ConditionInterface.cxx -o CMakeFiles/common.dir/moc_ConditionInterface.cxx.s

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.requires:
.PHONY : common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.requires

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.provides: common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.requires
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.provides.build
.PHONY : common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.provides

common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.provides.build: common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o

common/CMakeFiles/common.dir/DBInterface.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/DBInterface.cpp.o: common/DBInterface.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/CMakeFiles/common.dir/DBInterface.cpp.o"
	cd /mnt/disk/PTPS/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/DBInterface.cpp.o -c /mnt/disk/PTPS/common/DBInterface.cpp

common/CMakeFiles/common.dir/DBInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/DBInterface.cpp.i"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/common/DBInterface.cpp > CMakeFiles/common.dir/DBInterface.cpp.i

common/CMakeFiles/common.dir/DBInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/DBInterface.cpp.s"
	cd /mnt/disk/PTPS/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/common/DBInterface.cpp -o CMakeFiles/common.dir/DBInterface.cpp.s

common/CMakeFiles/common.dir/DBInterface.cpp.o.requires:
.PHONY : common/CMakeFiles/common.dir/DBInterface.cpp.o.requires

common/CMakeFiles/common.dir/DBInterface.cpp.o.provides: common/CMakeFiles/common.dir/DBInterface.cpp.o.requires
	$(MAKE) -f common/CMakeFiles/common.dir/build.make common/CMakeFiles/common.dir/DBInterface.cpp.o.provides.build
.PHONY : common/CMakeFiles/common.dir/DBInterface.cpp.o.provides

common/CMakeFiles/common.dir/DBInterface.cpp.o.provides.build: common/CMakeFiles/common.dir/DBInterface.cpp.o

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/Task.cpp.o" \
"CMakeFiles/common.dir/Serialization.cpp.o" \
"CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o" \
"CMakeFiles/common.dir/moc_ConditionInterface.cxx.o" \
"CMakeFiles/common.dir/DBInterface.cpp.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

bin/libcommon.so: common/CMakeFiles/common.dir/Task.cpp.o
bin/libcommon.so: common/CMakeFiles/common.dir/Serialization.cpp.o
bin/libcommon.so: common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o
bin/libcommon.so: common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o
bin/libcommon.so: common/CMakeFiles/common.dir/DBInterface.cpp.o
bin/libcommon.so: common/CMakeFiles/common.dir/build.make
bin/libcommon.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libcommon.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libcommon.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libcommon.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libcommon.so: common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../bin/libcommon.so"
	cd /mnt/disk/PTPS/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/common.dir/build: bin/libcommon.so
.PHONY : common/CMakeFiles/common.dir/build

common/CMakeFiles/common.dir/requires: common/CMakeFiles/common.dir/Task.cpp.o.requires
common/CMakeFiles/common.dir/requires: common/CMakeFiles/common.dir/Serialization.cpp.o.requires
common/CMakeFiles/common.dir/requires: common/CMakeFiles/common.dir/moc_DispatcherInterface.cxx.o.requires
common/CMakeFiles/common.dir/requires: common/CMakeFiles/common.dir/moc_ConditionInterface.cxx.o.requires
common/CMakeFiles/common.dir/requires: common/CMakeFiles/common.dir/DBInterface.cpp.o.requires
.PHONY : common/CMakeFiles/common.dir/requires

common/CMakeFiles/common.dir/clean:
	cd /mnt/disk/PTPS/common && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : common/CMakeFiles/common.dir/clean

common/CMakeFiles/common.dir/depend: common/moc_DispatcherInterface.cxx
common/CMakeFiles/common.dir/depend: common/moc_ConditionInterface.cxx
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/common /mnt/disk/PTPS /mnt/disk/PTPS/common /mnt/disk/PTPS/common/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : common/CMakeFiles/common.dir/depend

