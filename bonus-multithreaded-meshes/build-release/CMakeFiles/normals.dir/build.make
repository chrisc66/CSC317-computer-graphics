# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release

# Include any dependencies generated for this target.
include CMakeFiles/normals.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/normals.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/normals.dir/flags.make

CMakeFiles/normals.dir/normals.cpp.o: CMakeFiles/normals.dir/flags.make
CMakeFiles/normals.dir/normals.cpp.o: ../normals.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/normals.dir/normals.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/normals.dir/normals.cpp.o -c /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/normals.cpp

CMakeFiles/normals.dir/normals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/normals.dir/normals.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/normals.cpp > CMakeFiles/normals.dir/normals.cpp.i

CMakeFiles/normals.dir/normals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/normals.dir/normals.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/normals.cpp -o CMakeFiles/normals.dir/normals.cpp.s

# Object files for target normals
normals_OBJECTS = \
"CMakeFiles/normals.dir/normals.cpp.o"

# External object files for target normals
normals_EXTERNAL_OBJECTS =

normals: CMakeFiles/normals.dir/normals.cpp.o
normals: CMakeFiles/normals.dir/build.make
normals: libcore.a
normals: /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
normals: glad/libglad.a
normals: glfw/src/libglfw3.a
normals: CMakeFiles/normals.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable normals"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/normals.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/normals.dir/build: normals

.PHONY : CMakeFiles/normals.dir/build

CMakeFiles/normals.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/normals.dir/cmake_clean.cmake
.PHONY : CMakeFiles/normals.dir/clean

CMakeFiles/normals.dir/depend:
	cd /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release /Users/Zichun.Chong@ibm.com/Desktop/csc317/computer-graphics-meshes-bonus/build-release/CMakeFiles/normals.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/normals.dir/depend

