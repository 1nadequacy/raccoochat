# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Alex/workplace/raccoochat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Alex/workplace/raccoochat

# Include any dependencies generated for this target.
include CMakeFiles/SimpleTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SimpleTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimpleTest.dir/flags.make

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o: CMakeFiles/SimpleTest.dir/flags.make
CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o: raccoochat/test/SimpleTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Alex/workplace/raccoochat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o -c /Users/Alex/workplace/raccoochat/raccoochat/test/SimpleTest.cpp

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Alex/workplace/raccoochat/raccoochat/test/SimpleTest.cpp > CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.i

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Alex/workplace/raccoochat/raccoochat/test/SimpleTest.cpp -o CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.s

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.requires:

.PHONY : CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.requires

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.provides: CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/SimpleTest.dir/build.make CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.provides.build
.PHONY : CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.provides

CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.provides.build: CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o


# Object files for target SimpleTest
SimpleTest_OBJECTS = \
"CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o"

# External object files for target SimpleTest
SimpleTest_EXTERNAL_OBJECTS =

test/SimpleTest: CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o
test/SimpleTest: CMakeFiles/SimpleTest.dir/build.make
test/SimpleTest: libraccoochat.a
test/SimpleTest: raccoochat/third-party/gtest-1.7.0/fused-src/gtest/libgtest.a
test/SimpleTest: raccoochat/third-party/gtest-1.7.0/fused-src/gtest/libgtest_main.a
test/SimpleTest: raccoochat/third-party/gtest-1.7.0/fused-src/gtest/libgtest.a
test/SimpleTest: CMakeFiles/SimpleTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Alex/workplace/raccoochat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test/SimpleTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimpleTest.dir/build: test/SimpleTest

.PHONY : CMakeFiles/SimpleTest.dir/build

CMakeFiles/SimpleTest.dir/requires: CMakeFiles/SimpleTest.dir/raccoochat/test/SimpleTest.cpp.o.requires

.PHONY : CMakeFiles/SimpleTest.dir/requires

CMakeFiles/SimpleTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimpleTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimpleTest.dir/clean

CMakeFiles/SimpleTest.dir/depend:
	cd /Users/Alex/workplace/raccoochat && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Alex/workplace/raccoochat /Users/Alex/workplace/raccoochat /Users/Alex/workplace/raccoochat /Users/Alex/workplace/raccoochat /Users/Alex/workplace/raccoochat/CMakeFiles/SimpleTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SimpleTest.dir/depend
