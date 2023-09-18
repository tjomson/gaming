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
include project/CMakeFiles/SRE-project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project/CMakeFiles/SRE-project.dir/compiler_depend.make

# Include the progress variables for this target.
include project/CMakeFiles/SRE-project.dir/progress.make

# Include the compile flags for this target's objects.
include project/CMakeFiles/SRE-project.dir/flags.make

project/CMakeFiles/SRE-project.dir/project.cpp.o: project/CMakeFiles/SRE-project.dir/flags.make
project/CMakeFiles/SRE-project.dir/project.cpp.o: project/project.cpp
project/CMakeFiles/SRE-project.dir/project.cpp.o: project/CMakeFiles/SRE-project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project/CMakeFiles/SRE-project.dir/project.cpp.o"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT project/CMakeFiles/SRE-project.dir/project.cpp.o -MF CMakeFiles/SRE-project.dir/project.cpp.o.d -o CMakeFiles/SRE-project.dir/project.cpp.o -c /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/project.cpp

project/CMakeFiles/SRE-project.dir/project.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SRE-project.dir/project.cpp.i"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/project.cpp > CMakeFiles/SRE-project.dir/project.cpp.i

project/CMakeFiles/SRE-project.dir/project.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SRE-project.dir/project.cpp.s"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/project.cpp -o CMakeFiles/SRE-project.dir/project.cpp.s

# Object files for target SRE-project
SRE__project_OBJECTS = \
"CMakeFiles/SRE-project.dir/project.cpp.o"

# External object files for target SRE-project
SRE__project_EXTERNAL_OBJECTS =

project/SRE-project: project/CMakeFiles/SRE-project.dir/project.cpp.o
project/SRE-project: project/CMakeFiles/SRE-project.dir/build.make
project/SRE-project: /usr/lib64/libGL.so
project/SRE-project: /usr/lib64/libGLU.so
project/SRE-project: /lib64/libGLEW.so
project/SRE-project: /usr/lib64/libSDL2main.a
project/SRE-project: /usr/lib64/libSDL2.so
project/SRE-project: /usr/lib64/libSDL2_image.so
project/SRE-project: /usr/lib64/libSDL2_mixer.so
project/SRE-project: /usr/lib64/liblua-5.4.so
project/SRE-project: /usr/lib64/libm.so
project/SRE-project: submodules/SimpleRenderEngine/src/libSRE.a
project/SRE-project: thirdparty/Linux/Box2D/lib/libBox2D.a
project/SRE-project: /usr/lib64/libGL.so
project/SRE-project: /usr/lib64/libGLU.so
project/SRE-project: /lib64/libGLEW.so
project/SRE-project: /usr/lib64/libSDL2main.a
project/SRE-project: /usr/lib64/libSDL2.so
project/SRE-project: /usr/lib64/libSDL2_image.so
project/SRE-project: project/CMakeFiles/SRE-project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SRE-project"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SRE-project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project/CMakeFiles/SRE-project.dir/build: project/SRE-project
.PHONY : project/CMakeFiles/SRE-project.dir/build

project/CMakeFiles/SRE-project.dir/clean:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project && $(CMAKE_COMMAND) -P CMakeFiles/SRE-project.dir/cmake_clean.cmake
.PHONY : project/CMakeFiles/SRE-project.dir/clean

project/CMakeFiles/SRE-project.dir/depend:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/project/CMakeFiles/SRE-project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : project/CMakeFiles/SRE-project.dir/depend

