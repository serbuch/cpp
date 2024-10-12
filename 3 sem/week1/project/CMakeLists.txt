cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER clang++)

project(task3 VERSION 1.0 LANGUAGES CXX)

message(INFO:\ ${task3_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${task3_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(task3 main.cpp src/my_math.cpp)
