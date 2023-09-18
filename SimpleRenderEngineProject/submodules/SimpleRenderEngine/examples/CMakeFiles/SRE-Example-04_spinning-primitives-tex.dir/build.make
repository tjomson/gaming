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
include submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/compiler_depend.make

# Include the progress variables for this target.
include submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/progress.make

# Include the compile flags for this target's objects.
include submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/flags.make

submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o: submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/flags.make
submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o: submodules/SimpleRenderEngine/examples/04_spinning-primitives-tex.cpp
submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o: submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o -MF CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o.d -o CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o -c /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples/04_spinning-primitives-tex.cpp

submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.i"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples/04_spinning-primitives-tex.cpp > CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.i

submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.s"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples/04_spinning-primitives-tex.cpp -o CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.s

# Object files for target SRE-Example-04_spinning-primitives-tex
SRE__Example__04_spinning__primitives__tex_OBJECTS = \
"CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o"

# External object files for target SRE-Example-04_spinning-primitives-tex
SRE__Example__04_spinning__primitives__tex_EXTERNAL_OBJECTS =

submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/04_spinning-primitives-tex.cpp.o
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/build.make
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: submodules/SimpleRenderEngine/src/libSRE.a
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /usr/lib64/libGL.so
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /usr/lib64/libGLU.so
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /lib64/libGLEW.so
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /usr/lib64/libSDL2main.a
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /usr/lib64/libSDL2.so
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: /usr/lib64/libSDL2_image.so
submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex: submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SRE-Example-04_spinning-primitives-tex"
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/build: submodules/SimpleRenderEngine/examples/SRE-Example-04_spinning-primitives-tex
.PHONY : submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/build

submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/clean:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples && $(CMAKE_COMMAND) -P CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/cmake_clean.cmake
.PHONY : submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/clean

submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/depend:
	cd /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples /home/tjoms/Documents/GitHub/GameProgramming23-Exercises/SimpleRenderEngineProject/submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : submodules/SimpleRenderEngine/examples/CMakeFiles/SRE-Example-04_spinning-primitives-tex.dir/depend
