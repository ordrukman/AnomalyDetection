# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/yolevin/Documents/CLion-2021.2.2/clion-2021.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yolevin/Documents/CLion-2021.2.2/clion-2021.2.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AnomalyDetection.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/AnomalyDetection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AnomalyDetection.dir/flags.make

CMakeFiles/AnomalyDetection.dir/main.cpp.o: CMakeFiles/AnomalyDetection.dir/flags.make
CMakeFiles/AnomalyDetection.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AnomalyDetection.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnomalyDetection.dir/main.cpp.o -c /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/main.cpp

CMakeFiles/AnomalyDetection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnomalyDetection.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/main.cpp > CMakeFiles/AnomalyDetection.dir/main.cpp.i

CMakeFiles/AnomalyDetection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnomalyDetection.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/main.cpp -o CMakeFiles/AnomalyDetection.dir/main.cpp.s

CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o: CMakeFiles/AnomalyDetection.dir/flags.make
CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o -c /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/anomaly_detection_util.cpp

CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/anomaly_detection_util.cpp > CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.i

CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/anomaly_detection_util.cpp -o CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.s

# Object files for target AnomalyDetection
AnomalyDetection_OBJECTS = \
"CMakeFiles/AnomalyDetection.dir/main.cpp.o" \
"CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o"

# External object files for target AnomalyDetection
AnomalyDetection_EXTERNAL_OBJECTS =

AnomalyDetection: CMakeFiles/AnomalyDetection.dir/main.cpp.o
AnomalyDetection: CMakeFiles/AnomalyDetection.dir/anomaly_detection_util.cpp.o
AnomalyDetection: CMakeFiles/AnomalyDetection.dir/build.make
AnomalyDetection: CMakeFiles/AnomalyDetection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AnomalyDetection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnomalyDetection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AnomalyDetection.dir/build: AnomalyDetection
.PHONY : CMakeFiles/AnomalyDetection.dir/build

CMakeFiles/AnomalyDetection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AnomalyDetection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AnomalyDetection.dir/clean

CMakeFiles/AnomalyDetection.dir/depend:
	cd /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug /home/yolevin/Documents/ComputerScience_BarIlan/Advanced_Programming/cmake-build-debug/CMakeFiles/AnomalyDetection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AnomalyDetection.dir/depend

