# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/ubuntu/passive_radar/gnss-sdr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/passive_radar/gnss-sdr/build

# Include any dependencies generated for this target.
include src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/depend.make

# Include the progress variables for this target.
include src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/progress.make

# Include the compile flags for this target's objects.
include src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition.cc > CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_assisted_acquisition_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_assisted_acquisition_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_assisted_acquisition_cc.cc > CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_assisted_acquisition_cc.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition_fine_doppler_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition_fine_doppler_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition_fine_doppler_cc.cc > CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_acquisition_fine_doppler_cc.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_tong_acquisition_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_tong_acquisition_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_tong_acquisition_cc.cc > CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_tong_acquisition_cc.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_cccwsr_acquisition_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_cccwsr_acquisition_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_cccwsr_acquisition_cc.cc > CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_cccwsr_acquisition_cc.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/pcps_quicksync_acquisition_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_quicksync_acquisition_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_quicksync_acquisition_cc.cc > CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/pcps_quicksync_acquisition_cc.cc -o CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/galileo_pcps_8ms_acquisition_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_pcps_8ms_acquisition_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_pcps_8ms_acquisition_cc.cc > CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_pcps_8ms_acquisition_cc.cc -o CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o


src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/flags.make
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o: ../src/algorithms/acquisition/gnuradio_blocks/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc > CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.i

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc -o CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.s

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.requires:

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.provides: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.requires
	$(MAKE) -f src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.provides.build
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.provides

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.provides.build: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o


# Object files for target acq_gr_blocks
acq_gr_blocks_OBJECTS = \
"CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o" \
"CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o"

# External object files for target acq_gr_blocks
acq_gr_blocks_EXTERNAL_OBJECTS =

src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build.make
src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libacq_gr_blocks.a"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && $(CMAKE_COMMAND) -P CMakeFiles/acq_gr_blocks.dir/cmake_clean_target.cmake
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/acq_gr_blocks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build: src/algorithms/acquisition/gnuradio_blocks/libacq_gr_blocks.a

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/build

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_assisted_acquisition_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_acquisition_fine_doppler_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_tong_acquisition_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_cccwsr_acquisition_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/pcps_quicksync_acquisition_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_pcps_8ms_acquisition_cc.cc.o.requires
src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires: src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/galileo_e5a_noncoherent_iq_acquisition_caf_cc.cc.o.requires

.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/requires

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/clean:
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks && $(CMAKE_COMMAND) -P CMakeFiles/acq_gr_blocks.dir/cmake_clean.cmake
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/clean

src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/depend:
	cd /home/ubuntu/passive_radar/gnss-sdr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/passive_radar/gnss-sdr /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/acquisition/gnuradio_blocks /home/ubuntu/passive_radar/gnss-sdr/build /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks /home/ubuntu/passive_radar/gnss-sdr/build/src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/algorithms/acquisition/gnuradio_blocks/CMakeFiles/acq_gr_blocks.dir/depend

