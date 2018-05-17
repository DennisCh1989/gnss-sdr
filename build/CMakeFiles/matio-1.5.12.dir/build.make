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

# Utility rule file for matio-1.5.12.

# Include the progress variables for this target.
include CMakeFiles/matio-1.5.12.dir/progress.make

CMakeFiles/matio-1.5.12: CMakeFiles/matio-1.5.12-complete


CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-install
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-mkdir
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-download
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-update
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-patch
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-configure
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-build
CMakeFiles/matio-1.5.12-complete: matio/src/matio-1.5.12-stamp/matio-1.5.12-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'matio-1.5.12'"
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles
	/usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles/matio-1.5.12-complete
	/usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-done

matio/src/matio-1.5.12-stamp/matio-1.5.12-install: matio/src/matio-1.5.12-stamp/matio-1.5.12-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'matio-1.5.12'"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && $(MAKE) install
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && /usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-install

matio/src/matio-1.5.12-stamp/matio-1.5.12-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'matio-1.5.12'"
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio/matio-1.5.12
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/matio
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/matio/tmp
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp
	/usr/bin/cmake -E make_directory /home/ubuntu/passive_radar/gnss-sdr/build/matio/src
	/usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-mkdir

matio/src/matio-1.5.12-stamp/matio-1.5.12-download: matio/src/matio-1.5.12-stamp/matio-1.5.12-gitinfo.txt
matio/src/matio-1.5.12-stamp/matio-1.5.12-download: matio/src/matio-1.5.12-stamp/matio-1.5.12-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'matio-1.5.12'"
	cd /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio && /usr/bin/cmake -P /home/ubuntu/passive_radar/gnss-sdr/build/matio/tmp/matio-1.5.12-gitclone.cmake
	cd /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio && /usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-download

matio/src/matio-1.5.12-stamp/matio-1.5.12-update: matio/src/matio-1.5.12-stamp/matio-1.5.12-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'matio-1.5.12'"
	cd /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio/matio-1.5.12 && /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio/matio-1.5.12/autogen.sh
	cd /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio/matio-1.5.12 && /usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-update

matio/src/matio-1.5.12-stamp/matio-1.5.12-patch: matio/src/matio-1.5.12-stamp/matio-1.5.12-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'matio-1.5.12'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-patch

matio/src/matio-1.5.12-stamp/matio-1.5.12-configure: matio/tmp/matio-1.5.12-cfgcmd.txt
matio/src/matio-1.5.12-stamp/matio-1.5.12-configure: matio/src/matio-1.5.12-stamp/matio-1.5.12-update
matio/src/matio-1.5.12-stamp/matio-1.5.12-configure: matio/src/matio-1.5.12-stamp/matio-1.5.12-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'matio-1.5.12'"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && /home/ubuntu/passive_radar/gnss-sdr/thirdparty/matio/matio-1.5.12/configure --with-hdf5=/usr/lib/x86_64-linux-gnu/hdf5/serial --with-zlib=/usr --with-default-file-ver=7.3 --enable-mat73=yes --prefix=/home/ubuntu/passive_radar/gnss-sdr/build/matio
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && /usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-configure

matio/src/matio-1.5.12-stamp/matio-1.5.12-build: matio/src/matio-1.5.12-stamp/matio-1.5.12-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'matio-1.5.12'"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && make
	cd /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-build && /usr/bin/cmake -E touch /home/ubuntu/passive_radar/gnss-sdr/build/matio/src/matio-1.5.12-stamp/matio-1.5.12-build

matio-1.5.12: CMakeFiles/matio-1.5.12
matio-1.5.12: CMakeFiles/matio-1.5.12-complete
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-install
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-mkdir
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-download
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-update
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-patch
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-configure
matio-1.5.12: matio/src/matio-1.5.12-stamp/matio-1.5.12-build
matio-1.5.12: CMakeFiles/matio-1.5.12.dir/build.make

.PHONY : matio-1.5.12

# Rule to build all files generated by this target.
CMakeFiles/matio-1.5.12.dir/build: matio-1.5.12

.PHONY : CMakeFiles/matio-1.5.12.dir/build

CMakeFiles/matio-1.5.12.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matio-1.5.12.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matio-1.5.12.dir/clean

CMakeFiles/matio-1.5.12.dir/depend:
	cd /home/ubuntu/passive_radar/gnss-sdr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/passive_radar/gnss-sdr /home/ubuntu/passive_radar/gnss-sdr /home/ubuntu/passive_radar/gnss-sdr/build /home/ubuntu/passive_radar/gnss-sdr/build /home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles/matio-1.5.12.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matio-1.5.12.dir/depend

