# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Users/nrouzeva/.brew/Cellar/cmake/3.14.0/bin/cmake

# The command to remove a file.
RM = /Users/nrouzeva/.brew/Cellar/cmake/3.14.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nrouzeva/Documents/42_PJ/Soon_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test

# Include any dependencies generated for this target.
include Source/Core/CMakeFiles/Core.dir/depend.make

# Include the progress variables for this target.
include Source/Core/CMakeFiles/Core.dir/progress.make

# Include the compile flags for this target's objects.
include Source/Core/CMakeFiles/Core.dir/flags.make

Source/Core/CMakeFiles/Core.dir/Engine.cpp.o: Source/Core/CMakeFiles/Core.dir/flags.make
Source/Core/CMakeFiles/Core.dir/Engine.cpp.o: ../Source/Core/Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Source/Core/CMakeFiles/Core.dir/Engine.cpp.o"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Core.dir/Engine.cpp.o -c /Users/nrouzeva/Documents/42_PJ/Soon_engine/Source/Core/Engine.cpp

Source/Core/CMakeFiles/Core.dir/Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Engine.cpp.i"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nrouzeva/Documents/42_PJ/Soon_engine/Source/Core/Engine.cpp > CMakeFiles/Core.dir/Engine.cpp.i

Source/Core/CMakeFiles/Core.dir/Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Engine.cpp.s"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nrouzeva/Documents/42_PJ/Soon_engine/Source/Core/Engine.cpp -o CMakeFiles/Core.dir/Engine.cpp.s

# Object files for target Core
Core_OBJECTS = \
"CMakeFiles/Core.dir/Engine.cpp.o"

# External object files for target Core
Core_EXTERNAL_OBJECTS =

Source/Core/libCore.a: Source/Core/CMakeFiles/Core.dir/Engine.cpp.o
Source/Core/libCore.a: Source/Core/CMakeFiles/Core.dir/build.make
Source/Core/libCore.a: Source/Core/CMakeFiles/Core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCore.a"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && $(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean_target.cmake
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/Core/CMakeFiles/Core.dir/build: Source/Core/libCore.a

.PHONY : Source/Core/CMakeFiles/Core.dir/build

Source/Core/CMakeFiles/Core.dir/clean:
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core && $(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean.cmake
.PHONY : Source/Core/CMakeFiles/Core.dir/clean

Source/Core/CMakeFiles/Core.dir/depend:
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nrouzeva/Documents/42_PJ/Soon_engine /Users/nrouzeva/Documents/42_PJ/Soon_engine/Source/Core /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core /Users/nrouzeva/Documents/42_PJ/Soon_engine/Folder_test/Source/Core/CMakeFiles/Core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Source/Core/CMakeFiles/Core.dir/depend

