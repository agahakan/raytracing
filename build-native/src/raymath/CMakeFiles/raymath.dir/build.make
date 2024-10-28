# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /Users/G0512/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /Users/G0512/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/G0512/Dev/HETIC/RayTracer/raytracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native

# Include any dependencies generated for this target.
include src/raymath/CMakeFiles/raymath.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/raymath/CMakeFiles/raymath.dir/compiler_depend.make

# Include the progress variables for this target.
include src/raymath/CMakeFiles/raymath.dir/progress.make

# Include the compile flags for this target's objects.
include src/raymath/CMakeFiles/raymath.dir/flags.make

src/raymath/CMakeFiles/raymath.dir/Color.cpp.o: src/raymath/CMakeFiles/raymath.dir/flags.make
src/raymath/CMakeFiles/raymath.dir/Color.cpp.o: /Users/G0512/Dev/HETIC/RayTracer/raytracing/src/raymath/Color.cpp
src/raymath/CMakeFiles/raymath.dir/Color.cpp.o: src/raymath/CMakeFiles/raymath.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/raymath/CMakeFiles/raymath.dir/Color.cpp.o"
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/raymath/CMakeFiles/raymath.dir/Color.cpp.o -MF CMakeFiles/raymath.dir/Color.cpp.o.d -o CMakeFiles/raymath.dir/Color.cpp.o -c /Users/G0512/Dev/HETIC/RayTracer/raytracing/src/raymath/Color.cpp

src/raymath/CMakeFiles/raymath.dir/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raymath.dir/Color.cpp.i"
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/G0512/Dev/HETIC/RayTracer/raytracing/src/raymath/Color.cpp > CMakeFiles/raymath.dir/Color.cpp.i

src/raymath/CMakeFiles/raymath.dir/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raymath.dir/Color.cpp.s"
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/G0512/Dev/HETIC/RayTracer/raytracing/src/raymath/Color.cpp -o CMakeFiles/raymath.dir/Color.cpp.s

# Object files for target raymath
raymath_OBJECTS = \
"CMakeFiles/raymath.dir/Color.cpp.o"

# External object files for target raymath
raymath_EXTERNAL_OBJECTS =

src/raymath/libraymath.a: src/raymath/CMakeFiles/raymath.dir/Color.cpp.o
src/raymath/libraymath.a: src/raymath/CMakeFiles/raymath.dir/build.make
src/raymath/libraymath.a: src/raymath/CMakeFiles/raymath.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libraymath.a"
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && $(CMAKE_COMMAND) -P CMakeFiles/raymath.dir/cmake_clean_target.cmake
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raymath.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/raymath/CMakeFiles/raymath.dir/build: src/raymath/libraymath.a
.PHONY : src/raymath/CMakeFiles/raymath.dir/build

src/raymath/CMakeFiles/raymath.dir/clean:
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath && $(CMAKE_COMMAND) -P CMakeFiles/raymath.dir/cmake_clean.cmake
.PHONY : src/raymath/CMakeFiles/raymath.dir/clean

src/raymath/CMakeFiles/raymath.dir/depend:
	cd /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/G0512/Dev/HETIC/RayTracer/raytracing /Users/G0512/Dev/HETIC/RayTracer/raytracing/src/raymath /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath /Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/src/raymath/CMakeFiles/raymath.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/raymath/CMakeFiles/raymath.dir/depend

