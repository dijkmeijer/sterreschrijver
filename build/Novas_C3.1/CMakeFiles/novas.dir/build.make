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
include Novas_C3.1/CMakeFiles/novas.dir/depend.make

# Include the progress variables for this target.
include Novas_C3.1/CMakeFiles/novas.dir/progress.make

# Include the compile flags for this target's objects.
include Novas_C3.1/CMakeFiles/novas.dir/flags.make

Novas_C3.1/CMakeFiles/novas.dir/novas.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/novas.c.o: ../Novas_C3.1/novas.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/novas.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/novas.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/novas.c

Novas_C3.1/CMakeFiles/novas.dir/novas.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/novas.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/novas.c > CMakeFiles/novas.dir/novas.c.i

Novas_C3.1/CMakeFiles/novas.dir/novas.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/novas.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/novas.c -o CMakeFiles/novas.dir/novas.c.s

Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/novas.c.o

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o: ../Novas_C3.1/readeph0.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/readeph0.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/readeph0.c

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/readeph0.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/readeph0.c > CMakeFiles/novas.dir/readeph0.c.i

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/readeph0.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/readeph0.c -o CMakeFiles/novas.dir/readeph0.c.s

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o: ../Novas_C3.1/solsys1.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/solsys1.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/solsys1.c

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/solsys1.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/solsys1.c > CMakeFiles/novas.dir/solsys1.c.i

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/solsys1.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/solsys1.c -o CMakeFiles/novas.dir/solsys1.c.s

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o: ../Novas_C3.1/nutation.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/nutation.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/nutation.c

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/nutation.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/nutation.c > CMakeFiles/novas.dir/nutation.c.i

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/nutation.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/nutation.c -o CMakeFiles/novas.dir/nutation.c.s

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o: ../Novas_C3.1/novascon.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/novascon.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/novascon.c

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/novascon.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/novascon.c > CMakeFiles/novas.dir/novascon.c.i

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/novascon.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/novascon.c -o CMakeFiles/novas.dir/novascon.c.s

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o: ../Novas_C3.1/eph_manager.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/eph_manager.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/eph_manager.c

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/eph_manager.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/eph_manager.c > CMakeFiles/novas.dir/eph_manager.c.i

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/eph_manager.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/eph_manager.c -o CMakeFiles/novas.dir/eph_manager.c.s

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o: Novas_C3.1/CMakeFiles/novas.dir/flags.make
Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o: ../Novas_C3.1/cio_file.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/valentijn/sterreschrijver/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/novas.dir/cio_file.c.o   -c /home/valentijn/sterreschrijver/Novas_C3.1/cio_file.c

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/novas.dir/cio_file.c.i"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/valentijn/sterreschrijver/Novas_C3.1/cio_file.c > CMakeFiles/novas.dir/cio_file.c.i

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/novas.dir/cio_file.c.s"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/valentijn/sterreschrijver/Novas_C3.1/cio_file.c -o CMakeFiles/novas.dir/cio_file.c.s

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.requires:
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.requires

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.provides: Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.requires
	$(MAKE) -f Novas_C3.1/CMakeFiles/novas.dir/build.make Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.provides.build
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.provides

Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.provides.build: Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o

# Object files for target novas
novas_OBJECTS = \
"CMakeFiles/novas.dir/novas.c.o" \
"CMakeFiles/novas.dir/readeph0.c.o" \
"CMakeFiles/novas.dir/solsys1.c.o" \
"CMakeFiles/novas.dir/nutation.c.o" \
"CMakeFiles/novas.dir/novascon.c.o" \
"CMakeFiles/novas.dir/eph_manager.c.o" \
"CMakeFiles/novas.dir/cio_file.c.o"

# External object files for target novas
novas_EXTERNAL_OBJECTS =

Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/novas.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/build.make
Novas_C3.1/libnovas.a: Novas_C3.1/CMakeFiles/novas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libnovas.a"
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && $(CMAKE_COMMAND) -P CMakeFiles/novas.dir/cmake_clean_target.cmake
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/novas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Novas_C3.1/CMakeFiles/novas.dir/build: Novas_C3.1/libnovas.a
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/build

Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/novas.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/readeph0.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/solsys1.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/nutation.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/novascon.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/eph_manager.c.o.requires
Novas_C3.1/CMakeFiles/novas.dir/requires: Novas_C3.1/CMakeFiles/novas.dir/cio_file.c.o.requires
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/requires

Novas_C3.1/CMakeFiles/novas.dir/clean:
	cd /home/valentijn/sterreschrijver/build/Novas_C3.1 && $(CMAKE_COMMAND) -P CMakeFiles/novas.dir/cmake_clean.cmake
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/clean

Novas_C3.1/CMakeFiles/novas.dir/depend:
	cd /home/valentijn/sterreschrijver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/valentijn/sterreschrijver /home/valentijn/sterreschrijver/Novas_C3.1 /home/valentijn/sterreschrijver/build /home/valentijn/sterreschrijver/build/Novas_C3.1 /home/valentijn/sterreschrijver/build/Novas_C3.1/CMakeFiles/novas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Novas_C3.1/CMakeFiles/novas.dir/depend

