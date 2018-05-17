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
include src/core/libs/CMakeFiles/rx_core_lib.dir/depend.make

# Include the progress variables for this target.
include src/core/libs/CMakeFiles/rx_core_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/core/libs/CMakeFiles/rx_core_lib.dir/flags.make

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o: src/core/libs/CMakeFiles/rx_core_lib.dir/flags.make
src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o: ../src/core/libs/ini.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rx_core_lib.dir/ini.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/ini.cc

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rx_core_lib.dir/ini.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/ini.cc > CMakeFiles/rx_core_lib.dir/ini.cc.i

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rx_core_lib.dir/ini.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/ini.cc -o CMakeFiles/rx_core_lib.dir/ini.cc.s

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.requires:

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.requires

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.provides: src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.requires
	$(MAKE) -f src/core/libs/CMakeFiles/rx_core_lib.dir/build.make src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.provides.build
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.provides

src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.provides.build: src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o


src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o: src/core/libs/CMakeFiles/rx_core_lib.dir/flags.make
src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o: ../src/core/libs/INIReader.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rx_core_lib.dir/INIReader.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/INIReader.cc

src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rx_core_lib.dir/INIReader.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/INIReader.cc > CMakeFiles/rx_core_lib.dir/INIReader.cc.i

src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rx_core_lib.dir/INIReader.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/INIReader.cc -o CMakeFiles/rx_core_lib.dir/INIReader.cc.s

src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.requires:

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.requires

src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.provides: src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.requires
	$(MAKE) -f src/core/libs/CMakeFiles/rx_core_lib.dir/build.make src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.provides.build
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.provides

src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.provides.build: src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o


src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o: src/core/libs/CMakeFiles/rx_core_lib.dir/flags.make
src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o: ../src/core/libs/string_converter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rx_core_lib.dir/string_converter.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/string_converter.cc

src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rx_core_lib.dir/string_converter.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/string_converter.cc > CMakeFiles/rx_core_lib.dir/string_converter.cc.i

src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rx_core_lib.dir/string_converter.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/string_converter.cc -o CMakeFiles/rx_core_lib.dir/string_converter.cc.s

src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.requires:

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.requires

src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.provides: src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.requires
	$(MAKE) -f src/core/libs/CMakeFiles/rx_core_lib.dir/build.make src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.provides.build
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.provides

src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.provides.build: src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o


src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o: src/core/libs/CMakeFiles/rx_core_lib.dir/flags.make
src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o: ../src/core/libs/gnss_sdr_supl_client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o -c /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/gnss_sdr_supl_client.cc

src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.i"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/gnss_sdr_supl_client.cc > CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.i

src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.s"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/passive_radar/gnss-sdr/src/core/libs/gnss_sdr_supl_client.cc -o CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.s

src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.requires:

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.requires

src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.provides: src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.requires
	$(MAKE) -f src/core/libs/CMakeFiles/rx_core_lib.dir/build.make src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.provides.build
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.provides

src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.provides.build: src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o


# Object files for target rx_core_lib
rx_core_lib_OBJECTS = \
"CMakeFiles/rx_core_lib.dir/ini.cc.o" \
"CMakeFiles/rx_core_lib.dir/INIReader.cc.o" \
"CMakeFiles/rx_core_lib.dir/string_converter.cc.o" \
"CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o"

# External object files for target rx_core_lib
rx_core_lib_EXTERNAL_OBJECTS =

src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o
src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o
src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o
src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o
src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/build.make
src/core/libs/librx_core_lib.a: src/core/libs/CMakeFiles/rx_core_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/passive_radar/gnss-sdr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library librx_core_lib.a"
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && $(CMAKE_COMMAND) -P CMakeFiles/rx_core_lib.dir/cmake_clean_target.cmake
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rx_core_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/core/libs/CMakeFiles/rx_core_lib.dir/build: src/core/libs/librx_core_lib.a

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/build

src/core/libs/CMakeFiles/rx_core_lib.dir/requires: src/core/libs/CMakeFiles/rx_core_lib.dir/ini.cc.o.requires
src/core/libs/CMakeFiles/rx_core_lib.dir/requires: src/core/libs/CMakeFiles/rx_core_lib.dir/INIReader.cc.o.requires
src/core/libs/CMakeFiles/rx_core_lib.dir/requires: src/core/libs/CMakeFiles/rx_core_lib.dir/string_converter.cc.o.requires
src/core/libs/CMakeFiles/rx_core_lib.dir/requires: src/core/libs/CMakeFiles/rx_core_lib.dir/gnss_sdr_supl_client.cc.o.requires

.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/requires

src/core/libs/CMakeFiles/rx_core_lib.dir/clean:
	cd /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs && $(CMAKE_COMMAND) -P CMakeFiles/rx_core_lib.dir/cmake_clean.cmake
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/clean

src/core/libs/CMakeFiles/rx_core_lib.dir/depend:
	cd /home/ubuntu/passive_radar/gnss-sdr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/passive_radar/gnss-sdr /home/ubuntu/passive_radar/gnss-sdr/src/core/libs /home/ubuntu/passive_radar/gnss-sdr/build /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs /home/ubuntu/passive_radar/gnss-sdr/build/src/core/libs/CMakeFiles/rx_core_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/core/libs/CMakeFiles/rx_core_lib.dir/depend

