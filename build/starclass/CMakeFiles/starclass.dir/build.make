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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/valentijn/sterreschrijver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/valentijn/sterreschrijver/build

# Include any dependencies generated for this target.
include starclass/CMakeFiles/starclass.dir/depend.make

# Include the progress variables for this target.
include starclass/CMakeFiles/starclass.dir/progress.make

# Include the compile flags for this target's objects.
include starclass/CMakeFiles/starclass.dir/flags.make

starclass/CMakeFiles/starclass.dir/starclass.cpp.o: starclass/CMakeFiles/starclass.dir/flags.make
starclass/CMakeFiles/starclass.dir/starclass.cpp.o: ../starclass/starclass.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object starclass/CMakeFiles/starclass.dir/starclass.cpp.o"
	cd /home/valentijn/sterreschrijver/build/starclass && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/starclass.dir/starclass.cpp.o -c /home/valentijn/sterreschrijver/starclass/starclass.cpp

starclass/CMakeFiles/starclass.dir/starclass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/starclass.dir/starclass.cpp.i"
	cd /home/valentijn/sterreschrijver/build/starclass && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/valentijn/sterreschrijver/starclass/starclass.cpp > CMakeFiles/starclass.dir/starclass.cpp.i

starclass/CMakeFiles/starclass.dir/starclass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/starclass.dir/starclass.cpp.s"
	cd /home/valentijn/sterreschrijver/build/starclass && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/valentijn/sterreschrijver/starclass/starclass.cpp -o CMakeFiles/starclass.dir/starclass.cpp.s

starclass/CMakeFiles/starclass.dir/starclass.cpp.o.requires:
.PHONY : starclass/CMakeFiles/starclass.dir/starclass.cpp.o.requires

starclass/CMakeFiles/starclass.dir/starclass.cpp.o.provides: starclass/CMakeFiles/starclass.dir/starclass.cpp.o.requires
	$(MAKE) -f starclass/CMakeFiles/starclass.dir/build.make starclass/CMakeFiles/starclass.dir/starclass.cpp.o.provides.build
.PHONY : starclass/CMakeFiles/starclass.dir/starclass.cpp.o.provides

starclass/CMakeFiles/starclass.dir/starclass.cpp.o.provides.build: starclass/CMakeFiles/starclass.dir/starclass.cpp.o

# Object files for target starclass
starclass_OBJECTS = \
"CMakeFiles/starclass.dir/starclass.cpp.o"

# External object files for target starclass
starclass_EXTERNAL_OBJECTS =

starclass/libstarclass.a: starclass/CMakeFiles/starclass.dir/starclass.cpp.o
starclass/libstarclass.a: starclass/CMakeFiles/starclass.dir/build.make
starclass/libstarclass.a: starclass/CMakeFiles/starclass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libstarclass.a"
	cd /home/valentijn/sterreschrijver/build/starclass && $(CMAKE_COMMAND) -P CMakeFiles/starclass.dir/cmake_clean_target.cmake
	cd /home/valentijn/sterreschrijver/build/starclass && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/starclass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
starclass/CMakeFiles/starclass.dir/build: starclass/libstarclass.a
.PHONY : starclass/CMakeFiles/starclass.dir/build

starclass/CMakeFiles/starclass.dir/requires: starclass/CMakeFiles/starclass.dir/starclass.cpp.o.requires
.PHONY : starclass/CMakeFiles/starclass.dir/requires

starclass/CMakeFiles/starclass.dir/clean:
	cd /home/valentijn/sterreschrijver/build/starclass && $(CMAKE_COMMAND) -P CMakeFiles/starclass.dir/cmake_clean.cmake
.PHONY : starclass/CMakeFiles/starclass.dir/clean

starclass/CMakeFiles/starclass.dir/depend:
	cd /home/valentijn/sterreschrijver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/valentijn/sterreschrijver /home/valentijn/sterreschrijver/starclass /home/valentijn/sterreschrijver/build /home/valentijn/sterreschrijver/build/starclass /home/valentijn/sterreschrijver/build/starclass/CMakeFiles/starclass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : starclass/CMakeFiles/starclass.dir/depend

