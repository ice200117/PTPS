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
include MsgReceiver/CMakeFiles/MsgReceiver.dir/depend.make

# Include the progress variables for this target.
include MsgReceiver/CMakeFiles/MsgReceiver.dir/progress.make

# Include the compile flags for this target's objects.
include MsgReceiver/CMakeFiles/MsgReceiver.dir/flags.make

MsgReceiver/moc_MsgReceiver.cxx: MsgReceiver/MsgReceiver.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_MsgReceiver.cxx"
	cd /mnt/disk/PTPS/MsgReceiver && /mnt/disk/soft/qt-4.8.2/bin/moc @/mnt/disk/PTPS/MsgReceiver/moc_MsgReceiver.cxx_parameters

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o: MsgReceiver/CMakeFiles/MsgReceiver.dir/flags.make
MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o: MsgReceiver/MsgReceiver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o -c /mnt/disk/PTPS/MsgReceiver/MsgReceiver.cpp

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.i"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/MsgReceiver/MsgReceiver.cpp > CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.i

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.s"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/MsgReceiver/MsgReceiver.cpp -o CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.s

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.requires:
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.requires

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.provides: MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.requires
	$(MAKE) -f MsgReceiver/CMakeFiles/MsgReceiver.dir/build.make MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.provides.build
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.provides

MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.provides.build: MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o: MsgReceiver/CMakeFiles/MsgReceiver.dir/flags.make
MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o: MsgReceiver/moc_MsgReceiver.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o -c /mnt/disk/PTPS/MsgReceiver/moc_MsgReceiver.cxx

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.i"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/MsgReceiver/moc_MsgReceiver.cxx > CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.i

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.s"
	cd /mnt/disk/PTPS/MsgReceiver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/MsgReceiver/moc_MsgReceiver.cxx -o CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.s

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.requires:
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.requires

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.provides: MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.requires
	$(MAKE) -f MsgReceiver/CMakeFiles/MsgReceiver.dir/build.make MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.provides.build
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.provides

MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.provides.build: MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o

# Object files for target MsgReceiver
MsgReceiver_OBJECTS = \
"CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o" \
"CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o"

# External object files for target MsgReceiver
MsgReceiver_EXTERNAL_OBJECTS =

bin/libMsgReceiver.so: MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o
bin/libMsgReceiver.so: MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o
bin/libMsgReceiver.so: MsgReceiver/CMakeFiles/MsgReceiver.dir/build.make
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libMsgReceiver.so: bin/libCZMQ_Worker.so
bin/libMsgReceiver.so: bin/libLogger.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
bin/libMsgReceiver.so: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
bin/libMsgReceiver.so: MsgReceiver/CMakeFiles/MsgReceiver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../bin/libMsgReceiver.so"
	cd /mnt/disk/PTPS/MsgReceiver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MsgReceiver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MsgReceiver/CMakeFiles/MsgReceiver.dir/build: bin/libMsgReceiver.so
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/build

MsgReceiver/CMakeFiles/MsgReceiver.dir/requires: MsgReceiver/CMakeFiles/MsgReceiver.dir/MsgReceiver.cpp.o.requires
MsgReceiver/CMakeFiles/MsgReceiver.dir/requires: MsgReceiver/CMakeFiles/MsgReceiver.dir/moc_MsgReceiver.cxx.o.requires
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/requires

MsgReceiver/CMakeFiles/MsgReceiver.dir/clean:
	cd /mnt/disk/PTPS/MsgReceiver && $(CMAKE_COMMAND) -P CMakeFiles/MsgReceiver.dir/cmake_clean.cmake
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/clean

MsgReceiver/CMakeFiles/MsgReceiver.dir/depend: MsgReceiver/moc_MsgReceiver.cxx
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/MsgReceiver /mnt/disk/PTPS /mnt/disk/PTPS/MsgReceiver /mnt/disk/PTPS/MsgReceiver/CMakeFiles/MsgReceiver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MsgReceiver/CMakeFiles/MsgReceiver.dir/depend

