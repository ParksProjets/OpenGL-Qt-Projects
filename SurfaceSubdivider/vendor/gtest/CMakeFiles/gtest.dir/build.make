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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider

# Include any dependencies generated for this target.
include vendor/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include vendor/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/gtest/CMakeFiles/gtest.dir/flags.make

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: vendor/gtest/CMakeFiles/gtest.dir/flags.make
vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: vendor/gtest/src/gtest-all.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/src/gtest-all.cc

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires:
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides: vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
	$(MAKE) -f vendor/gtest/CMakeFiles/gtest.dir/build.make vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides

vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build: vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o: vendor/gtest/CMakeFiles/gtest.dir/flags.make
vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o: vendor/gtest/gtest_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/gtest_automoc.cpp.o -c /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/gtest_automoc.cpp

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/gtest_automoc.cpp.i"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/gtest_automoc.cpp > CMakeFiles/gtest.dir/gtest_automoc.cpp.i

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/gtest_automoc.cpp.s"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/gtest_automoc.cpp -o CMakeFiles/gtest.dir/gtest_automoc.cpp.s

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.requires:
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.requires

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.provides: vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.requires
	$(MAKE) -f vendor/gtest/CMakeFiles/gtest.dir/build.make vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.provides.build
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.provides

vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.provides.build: vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o" \
"CMakeFiles/gtest.dir/gtest_automoc.cpp.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

vendor/gtest/libgtest.a: vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
vendor/gtest/libgtest.a: vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o
vendor/gtest/libgtest.a: vendor/gtest/CMakeFiles/gtest.dir/build.make
vendor/gtest/libgtest.a: vendor/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libgtest.a"
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/gtest/CMakeFiles/gtest.dir/build: vendor/gtest/libgtest.a
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/build

vendor/gtest/CMakeFiles/gtest.dir/requires: vendor/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
vendor/gtest/CMakeFiles/gtest.dir/requires: vendor/gtest/CMakeFiles/gtest.dir/gtest_automoc.cpp.o.requires
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/requires

vendor/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/clean

vendor/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest /home/drusk/workspaces/misc/courses/csc486/a3/SurfaceSubdivider/vendor/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/gtest/CMakeFiles/gtest.dir/depend

