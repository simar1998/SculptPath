cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
set(CMAKE_BUILD_TYPE Release)

include_directories(
        include/Eigen
        include/clipper2
        include/recon
)

find_package(CGAL CONFIG REQUIRED)

add_executable(SculptPath 
        src/main.cpp
        src/mesh_loader/MeshLoad.cpp
        src/non_planar/Slicer.cpp
        src/non_planar/Settings.cpp
        src/non_planar/fileWriter/ThreadThreadSafeFileWriter.cpp
        src/non_planar/Intersect.cpp
        src/non_planar/MeshBoolean.cpp
        src/non_planar/MeshGenerator.cpp
        src/non_planar/PointPopulater.cpp
        src/non_planar/volume_navigation/MeshTriangulation.cpp
        src/non_planar/volume_iterator/VolumeIterator.cpp
        src/non_planar/volume_iterator/PointAnalyzer.cpp
        src/non_planar/GlobularResult.cpp
        src/non_planar/GlobularResult.h
        src/non_planar/volume_iterator/VolumeEntry.cpp
        src/non_planar/volume_iterator/VolumeEntry.h
        src/non_planar/volume_iterator/VolumeEntry.h
        src/non_planar/volume_iterator/CentroidIntersection.cpp
        src/non_planar/volume_iterator/CentroidIntersection.h
)

target_link_libraries(SculptPath PRIVATE CGAL::CGAL)
