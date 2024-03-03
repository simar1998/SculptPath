cmake_minimum_required(VERSION 3.25)
project(nonplanar)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(nonplanar
        src/Mesh.cpp
        src/Intersect.cpp
        src/Geometry.h
        src/volnag/VolumeNavigation.cpp
        src/volnag/GlobularCast.cpp
        src/main.cpp
        src/volnag/GlobularCast.h
        src/volnag/VolnavPoint.h
        src/settings/Settings.cpp
        src/settings/Settings.h
        src/volnag/PlanarDispertionRayCast.cpp
        src/volnag/PlanarDispertionRayCast.h
        src/ml/FactoryGCODE.cpp
        src/ml/FactoryGCODE.h
       )

# Copy meshfiles and settings to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/meshfiles/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/meshfiles/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/settings/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/settings/)