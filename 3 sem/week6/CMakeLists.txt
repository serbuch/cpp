cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

project(grid VERSION 1.0 LANGUAGES CXX)

add_executable(pow pow.cpp)
