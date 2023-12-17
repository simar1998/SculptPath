cmake_minimum_required(VERSION 3.25)
project(SculptPath)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
set(CMAKE_BUILD_TYPE Release)

include_directories(
        include/Eigen
        include/clipper2
        include/recon
)

find_package(CGAL CONFIG REQUIRED)
find_package(pybind11 REQUIRED)

add_executable(SculptPath src/main.cpp
        src/mesh_loader/MeshLoad.cpp
        src/mesh_loader/MeshLoad.h src/mesh_loader/OBJ_Loader.h src/non_planar/Slicer.cpp src/non_planar/Slicer.h
        src/non_planar/Slicer.h src/non_planar/Settings.cpp src/non_planar/Settings.h src/non_planar/Settings.h
        src/non_planar/fileWriter/ThreadThreadSafeFileWriter.cpp src/non_planar/fileWriter/ThreadThreadSafeFileWriter.h
        src/non_planar/fileWriter/ThreadThreadSafeFileWriter.h src/non_planar/Intersect.cpp src/non_planar/Intersect.h
        src/non_planar/Intersect.h src/non_planar/MeshBoolean.cpp src/non_planar/MeshBoolean.h src/non_planar/MeshBoolean.h src/non_planar/MeshGenerator.cpp src/non_planar/MeshGenerator.h src/non_planar/MeshGenerator.h src/non_planar/PointPopulater.cpp src/non_planar/PointPopulater.h src/non_planar/PointPopulater.h src/non_planar/volume_navigation/MeshTriangulation.cpp src/non_planar/volume_navigation/MeshTriangulation.h src/non_planar/volume_labeling/MeshLabeling.cpp src/non_planar/volume_labeling/MeshLabeling.h src/non_planar/volume_labeling/MeshLabeling.h src/non_planar/volume_labeling/Segmentation.cpp src/non_planar/volume_labeling/Segmentation.h src/non_planar/volume_labeling/Segmentation.h src/non_planar/surface_labeling/MeshSurfaceEstimation.cpp src/non_planar/surface_labeling/MeshSurfaceEstimation.h src/non_planar/surface_labeling/MeshSurfaceEstimation.h src/non_planar/volume_iterator/VolumeIterator.cpp src/non_planar/volume_iterator/VolumeIterator.h src/non_planar/volume_iterator/VolumeIterator.h src/mesh_loader/FileInjest.cpp src/mesh_loader/FileInjest.h src/mesh_loader/FileInjest.h)

target_include_directories(SculptPath PRIVATE include)

target_link_libraries(SculptPath PRIVATE CGAL::CGAL)
target_link_libraries(SculptPath PRIVATE pybind11::embed)

