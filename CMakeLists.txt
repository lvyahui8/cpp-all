cmake_minimum_required(VERSION 3.8)
project(cpp-all)

set(CMAKE_CXX_STANDARD  11)

#
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lcurl")


set(SOURCE_FILES net/get_example.cpp)

message(${cpp-all_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})

# cmake 编译
add_executable(cpp-all ${SOURCE_FILES})

# make编译，用自己写的makefile
#add_custom_target(cpp-all make -c ${cpp-all_SOURCE_DIR}  CLION_EXE_DIR=${PROJECT_BINARY_DIR} && cp ${cpp-all_SOURCE_DIR}/cpp-all ./)