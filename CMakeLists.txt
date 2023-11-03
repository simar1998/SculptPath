cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(SculptPath src/main.cpp src/MCUT_HW.h src/MCUT_HW.cpp include/recon/Reconstructors.h src/RECON_HW.h src/RECON_HW.cpp include/mcut/source/bvh.cpp include/mcut/source/frontend.cpp include/mcut/source/hmesh.cpp include/mcut/source/kernel.cpp include/mcut/source/math.cpp include/mcut/source/mcut.cpp include/mcut/source/preproc.cpp include/mcut/source/shewchuk.c)

# TODO look at proper way to allow MCUT header files to be used

target_include_directories(SculptPath PRIVATE include)