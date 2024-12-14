cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

project(parser VERSION 1.0 LANGUAGES CXX)

message(INFO:\ ${parser_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${parser_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main.out main.cpp src/utils.cpp src/parser.cpp)
