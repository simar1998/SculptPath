cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)

add_executable(SculptPath src/main.cpp src/MCUT_HW.h src/MCUT_HW.cpp include/recon/Reconstructors.h src/RECON_HW.h src/RECON_HW.cpp )


# TODO look at proper way to allow MCUT header files to be used

target_include_directories(SculptPath PRIVATE include)

include_directories(
        include/Eigen
        include/clipper2
        include/mcut
        include/recon
)

