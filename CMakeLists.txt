cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(SculptPath src/main.cpp src/MCUT_HW.h src/MCUT_HW.cpp)

target_include_directories(SculptPath PRIVATE include)