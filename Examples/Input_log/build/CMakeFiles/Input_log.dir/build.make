# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build

# Include any dependencies generated for this target.
include CMakeFiles/Input_log.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Input_log.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Input_log.dir/flags.make

CMakeFiles/Input_log.dir/main.c.o: CMakeFiles/Input_log.dir/flags.make
CMakeFiles/Input_log.dir/main.c.o: /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Input_log.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Input_log.dir/main.c.o   -c /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source/main.c

CMakeFiles/Input_log.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Input_log.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source/main.c > CMakeFiles/Input_log.dir/main.c.i

CMakeFiles/Input_log.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Input_log.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source/main.c -o CMakeFiles/Input_log.dir/main.c.s

# Object files for target Input_log
Input_log_OBJECTS = \
"CMakeFiles/Input_log.dir/main.c.o"

# External object files for target Input_log
Input_log_EXTERNAL_OBJECTS =

Input_log: CMakeFiles/Input_log.dir/main.c.o
Input_log: CMakeFiles/Input_log.dir/build.make
Input_log: CMakeFiles/Input_log.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Input_log"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Input_log.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Input_log.dir/build: Input_log

.PHONY : CMakeFiles/Input_log.dir/build

CMakeFiles/Input_log.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Input_log.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Input_log.dir/clean

CMakeFiles/Input_log.dir/depend:
	cd /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/Source /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build /home/pi/embed2/Opdracht1/Embed2-Opdracht1/Examples/Input_log/build/CMakeFiles/Input_log.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Input_log.dir/depend

