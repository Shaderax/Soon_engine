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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nrouzeva/Documents/42_PJ/Soon_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug

# Include any dependencies generated for this target.
include ThirdParty/glfw/tests/CMakeFiles/events.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/glfw/tests/CMakeFiles/events.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/glfw/tests/CMakeFiles/events.dir/flags.make

ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.o: ThirdParty/glfw/tests/CMakeFiles/events.dir/flags.make
ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.o: ../ThirdParty/glfw/tests/events.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.o"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/events.c.o   -c /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/tests/events.c

ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/events.c.i"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/tests/events.c > CMakeFiles/events.dir/events.c.i

ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/events.c.s"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/tests/events.c -o CMakeFiles/events.dir/events.c.s

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: ThirdParty/glfw/tests/CMakeFiles/events.dir/flags.make
ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: ../ThirdParty/glfw/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/__/deps/getopt.c.o   -c /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/getopt.c

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/getopt.c.i"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/getopt.c > CMakeFiles/events.dir/__/deps/getopt.c.i

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/getopt.c.s"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/getopt.c -o CMakeFiles/events.dir/__/deps/getopt.c.s

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.o: ThirdParty/glfw/tests/CMakeFiles/events.dir/flags.make
ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.o: ../ThirdParty/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.o"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/__/deps/glad.c.o   -c /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/glad.c

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/glad.c.i"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/glad.c > CMakeFiles/events.dir/__/deps/glad.c.i

ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/glad.c.s"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/deps/glad.c -o CMakeFiles/events.dir/__/deps/glad.c.s

# Object files for target events
events_OBJECTS = \
"CMakeFiles/events.dir/events.c.o" \
"CMakeFiles/events.dir/__/deps/getopt.c.o" \
"CMakeFiles/events.dir/__/deps/glad.c.o"

# External object files for target events
events_EXTERNAL_OBJECTS =

ThirdParty/glfw/tests/events: ThirdParty/glfw/tests/CMakeFiles/events.dir/events.c.o
ThirdParty/glfw/tests/events: ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o
ThirdParty/glfw/tests/events: ThirdParty/glfw/tests/CMakeFiles/events.dir/__/deps/glad.c.o
ThirdParty/glfw/tests/events: ThirdParty/glfw/tests/CMakeFiles/events.dir/build.make
ThirdParty/glfw/tests/events: ThirdParty/glfw/src/libglfw3.a
ThirdParty/glfw/tests/events: ThirdParty/glfw/tests/CMakeFiles/events.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable events"
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/events.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/glfw/tests/CMakeFiles/events.dir/build: ThirdParty/glfw/tests/events

.PHONY : ThirdParty/glfw/tests/CMakeFiles/events.dir/build

ThirdParty/glfw/tests/CMakeFiles/events.dir/clean:
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/events.dir/cmake_clean.cmake
.PHONY : ThirdParty/glfw/tests/CMakeFiles/events.dir/clean

ThirdParty/glfw/tests/CMakeFiles/events.dir/depend:
	cd /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nrouzeva/Documents/42_PJ/Soon_engine /Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/glfw/tests /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests /Users/nrouzeva/Documents/42_PJ/Soon_engine/cmake-build-debug/ThirdParty/glfw/tests/CMakeFiles/events.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/glfw/tests/CMakeFiles/events.dir/depend

