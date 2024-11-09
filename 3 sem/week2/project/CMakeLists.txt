cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

project(raytracing VERSION 1.0 LANGUAGES CXX)

message(INFO:\ ${raytracing_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${raytracing_SOURCE_DIR}/bin)

add_executable(raytracing main.cpp)