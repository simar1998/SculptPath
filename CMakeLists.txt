cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)



include_directories(
        include/Eigen
        include/clipper2
        include/recon
)

find_package(CGAL CONFIG REQUIRED)


add_executable(SculptPath src/main.cpp
        src/MCUT_HW.h
        src/MCUT_HW.cpp
        include/recon/Reconstructors.h
        src/RECON_HW.h
        src/RECON_HW.cpp src/mesh_loader/MeshLoad.cpp src/mesh_loader/MeshLoad.h)

target_link_libraries(SculptPath PRIVATE lib/mcut.dll)

target_include_directories(SculptPath PRIVATE include)

target_link_libraries(SculptPath PRIVATE CGAL::CGAL)


