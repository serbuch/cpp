cmake_minimum_required(VERSION 3.20)

project(laba LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(test laba.cpp)