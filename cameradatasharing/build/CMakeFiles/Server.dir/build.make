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
CMAKE_SOURCE_DIR = /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/src/Server.cc.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/src/Server.cc.o: ../src/Server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Server.dir/src/Server.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/src/Server.cc.o -c /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Server.cc

CMakeFiles/Server.dir/src/Server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/src/Server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Server.cc > CMakeFiles/Server.dir/src/Server.cc.i

CMakeFiles/Server.dir/src/Server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/src/Server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Server.cc -o CMakeFiles/Server.dir/src/Server.cc.s

CMakeFiles/Server.dir/src/Main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/src/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/src/Main.cpp.o -c /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Main.cpp

CMakeFiles/Server.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Main.cpp > CMakeFiles/Server.dir/src/Main.cpp.i

CMakeFiles/Server.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Main.cpp -o CMakeFiles/Server.dir/src/Main.cpp.s

CMakeFiles/Server.dir/src/ServerImpl.cc.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/src/ServerImpl.cc.o: ../src/ServerImpl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/src/ServerImpl.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/src/ServerImpl.cc.o -c /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/ServerImpl.cc

CMakeFiles/Server.dir/src/ServerImpl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/src/ServerImpl.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/ServerImpl.cc > CMakeFiles/Server.dir/src/ServerImpl.cc.i

CMakeFiles/Server.dir/src/ServerImpl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/src/ServerImpl.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/ServerImpl.cc -o CMakeFiles/Server.dir/src/ServerImpl.cc.s

CMakeFiles/Server.dir/src/Utility.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/src/Utility.cpp.o: ../src/Utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Server.dir/src/Utility.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/src/Utility.cpp.o -c /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Utility.cpp

CMakeFiles/Server.dir/src/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/src/Utility.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Utility.cpp > CMakeFiles/Server.dir/src/Utility.cpp.i

CMakeFiles/Server.dir/src/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/src/Utility.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Utility.cpp -o CMakeFiles/Server.dir/src/Utility.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/src/Server.cc.o" \
"CMakeFiles/Server.dir/src/Main.cpp.o" \
"CMakeFiles/Server.dir/src/ServerImpl.cc.o" \
"CMakeFiles/Server.dir/src/Utility.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/src/Server.cc.o
Server: CMakeFiles/Server.dir/src/Main.cpp.o
Server: CMakeFiles/Server.dir/src/ServerImpl.cc.o
Server: CMakeFiles/Server.dir/src/Utility.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: libhw_grpc_proto.a
Server: /home/sdv-2534/.local/lib/libabsl_flags.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_parse.a
Server: /home/sdv-2534/.local/lib/libgrpc++_reflection.a
Server: /home/sdv-2534/.local/lib/libgrpc++.a
Server: /home/sdv-2534/.local/lib/libprotobuf.a
Server: /usr/local/lib/libopencv_gapi.so.4.8.0
Server: /usr/local/lib/libopencv_highgui.so.4.8.0
Server: /usr/local/lib/libopencv_ml.so.4.8.0
Server: /usr/local/lib/libopencv_objdetect.so.4.8.0
Server: /usr/local/lib/libopencv_photo.so.4.8.0
Server: /usr/local/lib/libopencv_stitching.so.4.8.0
Server: /usr/local/lib/libopencv_video.so.4.8.0
Server: /usr/local/lib/libopencv_videoio.so.4.8.0
Server: /home/sdv-2534/.local/lib/libgrpc.a
Server: /home/sdv-2534/.local/lib/libcares.a
Server: /home/sdv-2534/.local/lib/libaddress_sorting.a
Server: /home/sdv-2534/.local/lib/libre2.a
Server: /home/sdv-2534/.local/lib/libupb.a
Server: /home/sdv-2534/.local/lib/libgpr.a
Server: /home/sdv-2534/.local/lib/libz.a
Server: /home/sdv-2534/.local/lib/libabsl_random_distributions.a
Server: /home/sdv-2534/.local/lib/libabsl_random_seed_sequences.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_pool_urbg.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_randen.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_hwaes.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_slow.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_platform.a
Server: /home/sdv-2534/.local/lib/libabsl_random_internal_seed_material.a
Server: /home/sdv-2534/.local/lib/libabsl_random_seed_gen_exception.a
Server: /home/sdv-2534/.local/lib/libssl.a
Server: /home/sdv-2534/.local/lib/libcrypto.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_check_op.a
Server: /home/sdv-2534/.local/lib/libabsl_leak_check.a
Server: /home/sdv-2534/.local/lib/libabsl_die_if_null.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_conditions.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_message.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_nullguard.a
Server: /home/sdv-2534/.local/lib/libabsl_examine_stack.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_format.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_proto.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_log_sink_set.a
Server: /home/sdv-2534/.local/lib/libabsl_log_sink.a
Server: /home/sdv-2534/.local/lib/libabsl_log_entry.a
Server: /home/sdv-2534/.local/lib/libabsl_log_initialize.a
Server: /home/sdv-2534/.local/lib/libabsl_log_globals.a
Server: /home/sdv-2534/.local/lib/libabsl_log_internal_globals.a
Server: /home/sdv-2534/.local/lib/libabsl_statusor.a
Server: /home/sdv-2534/.local/lib/libabsl_status.a
Server: /home/sdv-2534/.local/lib/libabsl_strerror.a
Server: /home/sdv-2534/.local/lib/libutf8_validity.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_usage.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_usage_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_flags.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_marshalling.a
Server: /home/sdv-2534/.local/lib/libabsl_str_format_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_reflection.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_config.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_private_handle_accessor.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_commandlineflag.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_commandlineflag_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_flags_program_name.a
Server: /home/sdv-2534/.local/lib/libabsl_cord.a
Server: /home/sdv-2534/.local/lib/libabsl_cordz_info.a
Server: /home/sdv-2534/.local/lib/libabsl_cord_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_cordz_functions.a
Server: /home/sdv-2534/.local/lib/libabsl_cordz_handle.a
Server: /home/sdv-2534/.local/lib/libabsl_crc_cord_state.a
Server: /home/sdv-2534/.local/lib/libabsl_crc32c.a
Server: /home/sdv-2534/.local/lib/libabsl_crc_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_crc_cpu_detect.a
Server: /home/sdv-2534/.local/lib/libabsl_hash.a
Server: /home/sdv-2534/.local/lib/libabsl_bad_variant_access.a
Server: /home/sdv-2534/.local/lib/libabsl_city.a
Server: /home/sdv-2534/.local/lib/libabsl_low_level_hash.a
Server: /home/sdv-2534/.local/lib/libabsl_raw_hash_set.a
Server: /home/sdv-2534/.local/lib/libabsl_bad_optional_access.a
Server: /home/sdv-2534/.local/lib/libabsl_hashtablez_sampler.a
Server: /home/sdv-2534/.local/lib/libabsl_exponential_biased.a
Server: /home/sdv-2534/.local/lib/libabsl_synchronization.a
Server: /home/sdv-2534/.local/lib/libabsl_graphcycles_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_time.a
Server: /home/sdv-2534/.local/lib/libabsl_civil_time.a
Server: /home/sdv-2534/.local/lib/libabsl_time_zone.a
Server: /home/sdv-2534/.local/lib/libabsl_stacktrace.a
Server: /home/sdv-2534/.local/lib/libabsl_symbolize.a
Server: /home/sdv-2534/.local/lib/libabsl_strings.a
Server: /home/sdv-2534/.local/lib/libabsl_strings_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_int128.a
Server: /home/sdv-2534/.local/lib/libabsl_throw_delegate.a
Server: /home/sdv-2534/.local/lib/libabsl_malloc_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_debugging_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_demangle_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_base.a
Server: /home/sdv-2534/.local/lib/libabsl_raw_logging_internal.a
Server: /home/sdv-2534/.local/lib/libabsl_log_severity.a
Server: /home/sdv-2534/.local/lib/libabsl_spinlock_wait.a
Server: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
Server: /usr/local/lib/libopencv_dnn.so.4.8.0
Server: /usr/local/lib/libopencv_calib3d.so.4.8.0
Server: /usr/local/lib/libopencv_features2d.so.4.8.0
Server: /usr/local/lib/libopencv_flann.so.4.8.0
Server: /usr/local/lib/libopencv_imgproc.so.4.8.0
Server: /usr/local/lib/libopencv_core.so.4.8.0
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server

.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend

