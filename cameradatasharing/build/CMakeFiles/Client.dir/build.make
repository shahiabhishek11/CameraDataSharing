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
include CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/src/Client.cc.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/src/Client.cc.o: ../src/Client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/src/Client.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/src/Client.cc.o -c /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Client.cc

CMakeFiles/Client.dir/src/Client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/src/Client.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Client.cc > CMakeFiles/Client.dir/src/Client.cc.i

CMakeFiles/Client.dir/src/Client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/src/Client.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/src/Client.cc -o CMakeFiles/Client.dir/src/Client.cc.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/src/Client.cc.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client: CMakeFiles/Client.dir/src/Client.cc.o
Client: CMakeFiles/Client.dir/build.make
Client: libhw_grpc_proto.a
Client: /home/sdv-2534/.local/lib/libabsl_flags.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_parse.a
Client: /home/sdv-2534/.local/lib/libgrpc++_reflection.a
Client: /home/sdv-2534/.local/lib/libgrpc++.a
Client: /home/sdv-2534/.local/lib/libprotobuf.a
Client: /usr/local/lib/libopencv_gapi.so.4.8.0
Client: /usr/local/lib/libopencv_highgui.so.4.8.0
Client: /usr/local/lib/libopencv_ml.so.4.8.0
Client: /usr/local/lib/libopencv_objdetect.so.4.8.0
Client: /usr/local/lib/libopencv_photo.so.4.8.0
Client: /usr/local/lib/libopencv_stitching.so.4.8.0
Client: /usr/local/lib/libopencv_video.so.4.8.0
Client: /usr/local/lib/libopencv_videoio.so.4.8.0
Client: /home/sdv-2534/.local/lib/libgrpc.a
Client: /home/sdv-2534/.local/lib/libcares.a
Client: /home/sdv-2534/.local/lib/libaddress_sorting.a
Client: /home/sdv-2534/.local/lib/libre2.a
Client: /home/sdv-2534/.local/lib/libupb.a
Client: /home/sdv-2534/.local/lib/libgpr.a
Client: /home/sdv-2534/.local/lib/libz.a
Client: /home/sdv-2534/.local/lib/libabsl_random_distributions.a
Client: /home/sdv-2534/.local/lib/libabsl_random_seed_sequences.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_pool_urbg.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_randen.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_hwaes.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_randen_slow.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_platform.a
Client: /home/sdv-2534/.local/lib/libabsl_random_internal_seed_material.a
Client: /home/sdv-2534/.local/lib/libabsl_random_seed_gen_exception.a
Client: /home/sdv-2534/.local/lib/libssl.a
Client: /home/sdv-2534/.local/lib/libcrypto.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_check_op.a
Client: /home/sdv-2534/.local/lib/libabsl_leak_check.a
Client: /home/sdv-2534/.local/lib/libabsl_die_if_null.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_conditions.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_message.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_nullguard.a
Client: /home/sdv-2534/.local/lib/libabsl_examine_stack.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_format.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_proto.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_log_sink_set.a
Client: /home/sdv-2534/.local/lib/libabsl_log_sink.a
Client: /home/sdv-2534/.local/lib/libabsl_log_entry.a
Client: /home/sdv-2534/.local/lib/libabsl_log_initialize.a
Client: /home/sdv-2534/.local/lib/libabsl_log_globals.a
Client: /home/sdv-2534/.local/lib/libabsl_log_internal_globals.a
Client: /home/sdv-2534/.local/lib/libabsl_statusor.a
Client: /home/sdv-2534/.local/lib/libabsl_status.a
Client: /home/sdv-2534/.local/lib/libabsl_strerror.a
Client: /home/sdv-2534/.local/lib/libutf8_validity.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_usage.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_usage_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_flags.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_marshalling.a
Client: /home/sdv-2534/.local/lib/libabsl_str_format_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_reflection.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_config.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_private_handle_accessor.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_commandlineflag.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_commandlineflag_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_flags_program_name.a
Client: /home/sdv-2534/.local/lib/libabsl_cord.a
Client: /home/sdv-2534/.local/lib/libabsl_cordz_info.a
Client: /home/sdv-2534/.local/lib/libabsl_cord_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_cordz_functions.a
Client: /home/sdv-2534/.local/lib/libabsl_cordz_handle.a
Client: /home/sdv-2534/.local/lib/libabsl_crc_cord_state.a
Client: /home/sdv-2534/.local/lib/libabsl_crc32c.a
Client: /home/sdv-2534/.local/lib/libabsl_crc_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_crc_cpu_detect.a
Client: /home/sdv-2534/.local/lib/libabsl_hash.a
Client: /home/sdv-2534/.local/lib/libabsl_bad_variant_access.a
Client: /home/sdv-2534/.local/lib/libabsl_city.a
Client: /home/sdv-2534/.local/lib/libabsl_low_level_hash.a
Client: /home/sdv-2534/.local/lib/libabsl_raw_hash_set.a
Client: /home/sdv-2534/.local/lib/libabsl_bad_optional_access.a
Client: /home/sdv-2534/.local/lib/libabsl_hashtablez_sampler.a
Client: /home/sdv-2534/.local/lib/libabsl_exponential_biased.a
Client: /home/sdv-2534/.local/lib/libabsl_synchronization.a
Client: /home/sdv-2534/.local/lib/libabsl_graphcycles_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_time.a
Client: /home/sdv-2534/.local/lib/libabsl_civil_time.a
Client: /home/sdv-2534/.local/lib/libabsl_time_zone.a
Client: /home/sdv-2534/.local/lib/libabsl_stacktrace.a
Client: /home/sdv-2534/.local/lib/libabsl_symbolize.a
Client: /home/sdv-2534/.local/lib/libabsl_strings.a
Client: /home/sdv-2534/.local/lib/libabsl_strings_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_int128.a
Client: /home/sdv-2534/.local/lib/libabsl_throw_delegate.a
Client: /home/sdv-2534/.local/lib/libabsl_malloc_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_debugging_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_demangle_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_base.a
Client: /home/sdv-2534/.local/lib/libabsl_raw_logging_internal.a
Client: /home/sdv-2534/.local/lib/libabsl_log_severity.a
Client: /home/sdv-2534/.local/lib/libabsl_spinlock_wait.a
Client: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
Client: /usr/local/lib/libopencv_dnn.so.4.8.0
Client: /usr/local/lib/libopencv_calib3d.so.4.8.0
Client: /usr/local/lib/libopencv_features2d.so.4.8.0
Client: /usr/local/lib/libopencv_flann.so.4.8.0
Client: /usr/local/lib/libopencv_imgproc.so.4.8.0
Client: /usr/local/lib/libopencv_core.so.4.8.0
Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client

.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build /home/sdv-2534/AZUR/sdv_app_sensorsharing/sensorsharing/build/CMakeFiles/Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

