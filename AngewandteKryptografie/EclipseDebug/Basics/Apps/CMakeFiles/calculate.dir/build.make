# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug"

# Include any dependencies generated for this target.
include Basics/Apps/CMakeFiles/calculate.dir/depend.make

# Include the progress variables for this target.
include Basics/Apps/CMakeFiles/calculate.dir/progress.make

# Include the compile flags for this target's objects.
include Basics/Apps/CMakeFiles/calculate.dir/flags.make

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o: Basics/Apps/CMakeFiles/calculate.dir/flags.make
Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o: /home/fenix/Dropbox/uni/Kryptographische\ Algorithmen/ak2/AngewandteKryptografie/src/Basics/Apps/calculate.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o"
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/calculate.dir/calculate.cpp.o -c "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src/Basics/Apps/calculate.cpp"

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculate.dir/calculate.cpp.i"
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src/Basics/Apps/calculate.cpp" > CMakeFiles/calculate.dir/calculate.cpp.i

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculate.dir/calculate.cpp.s"
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src/Basics/Apps/calculate.cpp" -o CMakeFiles/calculate.dir/calculate.cpp.s

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.requires:
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.requires

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.provides: Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.requires
	$(MAKE) -f Basics/Apps/CMakeFiles/calculate.dir/build.make Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.provides.build
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.provides

Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.provides.build: Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o

# Object files for target calculate
calculate_OBJECTS = \
"CMakeFiles/calculate.dir/calculate.cpp.o"

# External object files for target calculate
calculate_EXTERNAL_OBJECTS =

bin/calculate: Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o
bin/calculate: Basics/Apps/CMakeFiles/calculate.dir/build.make
bin/calculate: Basics/Lib/libfunctions.a
bin/calculate: Basics/Apps/CMakeFiles/calculate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/calculate"
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calculate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Basics/Apps/CMakeFiles/calculate.dir/build: bin/calculate
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/build

Basics/Apps/CMakeFiles/calculate.dir/requires: Basics/Apps/CMakeFiles/calculate.dir/calculate.cpp.o.requires
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/requires

Basics/Apps/CMakeFiles/calculate.dir/clean:
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" && $(CMAKE_COMMAND) -P CMakeFiles/calculate.dir/cmake_clean.cmake
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/clean

Basics/Apps/CMakeFiles/calculate.dir/depend:
	cd "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src" "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/src/Basics/Apps" "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug" "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps" "/home/fenix/Dropbox/uni/Kryptographische Algorithmen/ak2/AngewandteKryptografie/EclipseDebug/Basics/Apps/CMakeFiles/calculate.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Basics/Apps/CMakeFiles/calculate.dir/depend

