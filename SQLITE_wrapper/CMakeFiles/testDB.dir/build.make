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
include SQLITE_wrapper/CMakeFiles/testDB.dir/depend.make

# Include the progress variables for this target.
include SQLITE_wrapper/CMakeFiles/testDB.dir/progress.make

# Include the compile flags for this target's objects.
include SQLITE_wrapper/CMakeFiles/testDB.dir/flags.make

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o: SQLITE_wrapper/CMakeFiles/testDB.dir/flags.make
SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o: SQLITE_wrapper/testDB.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/disk/PTPS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o"
	cd /mnt/disk/PTPS/SQLITE_wrapper && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testDB.dir/testDB.cpp.o -c /mnt/disk/PTPS/SQLITE_wrapper/testDB.cpp

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testDB.dir/testDB.cpp.i"
	cd /mnt/disk/PTPS/SQLITE_wrapper && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/disk/PTPS/SQLITE_wrapper/testDB.cpp > CMakeFiles/testDB.dir/testDB.cpp.i

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testDB.dir/testDB.cpp.s"
	cd /mnt/disk/PTPS/SQLITE_wrapper && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/disk/PTPS/SQLITE_wrapper/testDB.cpp -o CMakeFiles/testDB.dir/testDB.cpp.s

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.requires:
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.requires

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.provides: SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.requires
	$(MAKE) -f SQLITE_wrapper/CMakeFiles/testDB.dir/build.make SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.provides.build
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.provides

SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.provides.build: SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o

# Object files for target testDB
testDB_OBJECTS = \
"CMakeFiles/testDB.dir/testDB.cpp.o"

# External object files for target testDB
testDB_EXTERNAL_OBJECTS =

SQLITE_wrapper/testDB: SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o
SQLITE_wrapper/testDB: SQLITE_wrapper/CMakeFiles/testDB.dir/build.make
SQLITE_wrapper/testDB: bin/libcommon.so
SQLITE_wrapper/testDB: bin/libSQLITE_wrapper.so
SQLITE_wrapper/testDB: bin/libcommon.so
SQLITE_wrapper/testDB: /mnt/disk/soft/qt-4.8.2/lib/libQtGui.so
SQLITE_wrapper/testDB: /mnt/disk/soft/qt-4.8.2/lib/libQtXml.so
SQLITE_wrapper/testDB: /mnt/disk/soft/qt-4.8.2/lib/libQtNetwork.so
SQLITE_wrapper/testDB: /mnt/disk/soft/qt-4.8.2/lib/libQtCore.so
SQLITE_wrapper/testDB: SQLITE_wrapper/CMakeFiles/testDB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable testDB"
	cd /mnt/disk/PTPS/SQLITE_wrapper && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testDB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SQLITE_wrapper/CMakeFiles/testDB.dir/build: SQLITE_wrapper/testDB
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/build

SQLITE_wrapper/CMakeFiles/testDB.dir/requires: SQLITE_wrapper/CMakeFiles/testDB.dir/testDB.cpp.o.requires
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/requires

SQLITE_wrapper/CMakeFiles/testDB.dir/clean:
	cd /mnt/disk/PTPS/SQLITE_wrapper && $(CMAKE_COMMAND) -P CMakeFiles/testDB.dir/cmake_clean.cmake
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/clean

SQLITE_wrapper/CMakeFiles/testDB.dir/depend:
	cd /mnt/disk/PTPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/disk/PTPS /mnt/disk/PTPS/SQLITE_wrapper /mnt/disk/PTPS /mnt/disk/PTPS/SQLITE_wrapper /mnt/disk/PTPS/SQLITE_wrapper/CMakeFiles/testDB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SQLITE_wrapper/CMakeFiles/testDB.dir/depend

