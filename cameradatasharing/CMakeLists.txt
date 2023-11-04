cmake_minimum_required(VERSION 3.3)
project(sensorsharing)
set(CMAKE_CXX_FLAGS "-std=c++17")

find_package(OpenCV REQUIRED)
# include(/home/$ENV{USER}/grpc/examples/cpp/cmake/common.cmake)
include(${GRPC_DIR}/grpc/examples/cpp/cmake/common.cmake)
get_filename_component(hw_proto ${CMAKE_CURRENT_SOURCE_DIR}/../protos/sensorsharing.proto ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/sensorsharing.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/sensorsharing.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/sensorsharing.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/sensorsharing.grpc.pb.h")

add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}" )
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
add_executable( Server  src/Server.cc src/Main.cpp src/ServerImpl.cc src/Utility.cpp )
target_link_libraries(Server
  hw_grpc_proto
  absl::flags
  absl::flags_parse
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  ${OpenCV_LIBS})

add_executable( Client  src/Client.cc)
target_link_libraries(Client
  hw_grpc_proto
  absl::flags
  absl::flags_parse
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  ${OpenCV_LIBS})