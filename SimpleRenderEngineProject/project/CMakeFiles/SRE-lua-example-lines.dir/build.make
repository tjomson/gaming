# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject

# Include any dependencies generated for this target.
include project/CMakeFiles/SRE-lua-example-lines.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project/CMakeFiles/SRE-lua-example-lines.dir/compiler_depend.make

# Include the progress variables for this target.
include project/CMakeFiles/SRE-lua-example-lines.dir/progress.make

# Include the compile flags for this target's objects.
include project/CMakeFiles/SRE-lua-example-lines.dir/flags.make

project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o: project/CMakeFiles/SRE-lua-example-lines.dir/flags.make
project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o: project/lua-example-lines.cpp
project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o: project/CMakeFiles/SRE-lua-example-lines.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o -MF CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o.d -o CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o -c /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/lua-example-lines.cpp

project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.i"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/lua-example-lines.cpp > CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.i

project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.s"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/lua-example-lines.cpp -o CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.s

# Object files for target SRE-lua-example-lines
SRE__lua__example__lines_OBJECTS = \
"CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o"

# External object files for target SRE-lua-example-lines
SRE__lua__example__lines_EXTERNAL_OBJECTS =

project/SRE-lua-example-lines: project/CMakeFiles/SRE-lua-example-lines.dir/lua-example-lines.cpp.o
project/SRE-lua-example-lines: project/CMakeFiles/SRE-lua-example-lines.dir/build.make
project/SRE-lua-example-lines: /usr/lib64/libGL.so
project/SRE-lua-example-lines: /usr/lib64/libGLU.so
project/SRE-lua-example-lines: /lib64/libGLEW.so
project/SRE-lua-example-lines: /usr/lib64/libSDL2main.a
project/SRE-lua-example-lines: /usr/lib64/libSDL2.so
project/SRE-lua-example-lines: /usr/lib64/libSDL2_image.so
project/SRE-lua-example-lines: /usr/lib64/libSDL2_mixer.so
project/SRE-lua-example-lines: /usr/lib64/liblua-5.4.so
project/SRE-lua-example-lines: /usr/lib64/libm.so
project/SRE-lua-example-lines: submodules/SimpleRenderEngine/src/libSRE.a
project/SRE-lua-example-lines: thirdparty/Linux/Box2D/lib/libBox2D.a
project/SRE-lua-example-lines: /usr/lib64/libGL.so
project/SRE-lua-example-lines: /usr/lib64/libGLU.so
project/SRE-lua-example-lines: /lib64/libGLEW.so
project/SRE-lua-example-lines: /usr/lib64/libSDL2main.a
project/SRE-lua-example-lines: /usr/lib64/libSDL2.so
project/SRE-lua-example-lines: /usr/lib64/libSDL2_image.so
project/SRE-lua-example-lines: project/CMakeFiles/SRE-lua-example-lines.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SRE-lua-example-lines"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SRE-lua-example-lines.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project/CMakeFiles/SRE-lua-example-lines.dir/build: project/SRE-lua-example-lines
.PHONY : project/CMakeFiles/SRE-lua-example-lines.dir/build

project/CMakeFiles/SRE-lua-example-lines.dir/clean:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && $(CMAKE_COMMAND) -P CMakeFiles/SRE-lua-example-lines.dir/cmake_clean.cmake
.PHONY : project/CMakeFiles/SRE-lua-example-lines.dir/clean

project/CMakeFiles/SRE-lua-example-lines.dir/depend:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/CMakeFiles/SRE-lua-example-lines.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : project/CMakeFiles/SRE-lua-example-lines.dir/depend

