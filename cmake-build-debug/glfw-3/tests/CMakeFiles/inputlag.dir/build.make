# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michaelferents/CLionProjects/Wuu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug

# Include any dependencies generated for this target.
include glfw-3/tests/CMakeFiles/inputlag.dir/depend.make
# Include the progress variables for this target.
include glfw-3/tests/CMakeFiles/inputlag.dir/progress.make

# Include the compile flags for this target's objects.
include glfw-3/tests/CMakeFiles/inputlag.dir/flags.make

glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.o: glfw-3/tests/CMakeFiles/inputlag.dir/flags.make
glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.o: ../glfw-3/tests/inputlag.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.o"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/inputlag.c.o -c /Users/michaelferents/CLionProjects/Wuu/glfw-3/tests/inputlag.c

glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/inputlag.c.i"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michaelferents/CLionProjects/Wuu/glfw-3/tests/inputlag.c > CMakeFiles/inputlag.dir/inputlag.c.i

glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/inputlag.c.s"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michaelferents/CLionProjects/Wuu/glfw-3/tests/inputlag.c -o CMakeFiles/inputlag.dir/inputlag.c.s

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: glfw-3/tests/CMakeFiles/inputlag.dir/flags.make
glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: ../glfw-3/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/__/deps/getopt.c.o -c /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/getopt.c

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/getopt.c.i"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/getopt.c > CMakeFiles/inputlag.dir/__/deps/getopt.c.i

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/getopt.c.s"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/getopt.c -o CMakeFiles/inputlag.dir/__/deps/getopt.c.s

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: glfw-3/tests/CMakeFiles/inputlag.dir/flags.make
glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: ../glfw-3/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -c /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/glad_gl.c

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/glad_gl.c > CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i

glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michaelferents/CLionProjects/Wuu/glfw-3/deps/glad_gl.c -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s

# Object files for target inputlag
inputlag_OBJECTS = \
"CMakeFiles/inputlag.dir/inputlag.c.o" \
"CMakeFiles/inputlag.dir/__/deps/getopt.c.o" \
"CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"

# External object files for target inputlag
inputlag_EXTERNAL_OBJECTS =

glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/tests/CMakeFiles/inputlag.dir/inputlag.c.o
glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o
glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o
glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/tests/CMakeFiles/inputlag.dir/build.make
glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/src/libglfw3.a
glfw-3/tests/inputlag.app/Contents/MacOS/inputlag: glfw-3/tests/CMakeFiles/inputlag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable inputlag.app/Contents/MacOS/inputlag"
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputlag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw-3/tests/CMakeFiles/inputlag.dir/build: glfw-3/tests/inputlag.app/Contents/MacOS/inputlag
.PHONY : glfw-3/tests/CMakeFiles/inputlag.dir/build

glfw-3/tests/CMakeFiles/inputlag.dir/clean:
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests && $(CMAKE_COMMAND) -P CMakeFiles/inputlag.dir/cmake_clean.cmake
.PHONY : glfw-3/tests/CMakeFiles/inputlag.dir/clean

glfw-3/tests/CMakeFiles/inputlag.dir/depend:
	cd /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michaelferents/CLionProjects/Wuu /Users/michaelferents/CLionProjects/Wuu/glfw-3/tests /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests /Users/michaelferents/CLionProjects/Wuu/cmake-build-debug/glfw-3/tests/CMakeFiles/inputlag.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw-3/tests/CMakeFiles/inputlag.dir/depend

