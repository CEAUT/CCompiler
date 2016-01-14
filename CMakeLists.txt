cmake_minimum_required(VERSION 3.3)
project(CCompiler)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp loader.h loader.cpp loader.h errorgen.cpp errorgen.h limits.h)
add_executable(CCompiler ${SOURCE_FILES})