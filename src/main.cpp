#include <iostream>

#include "mesh_loader/MeshLoad.h"
#include "non_planar/Slicer.h"
#include "non_planar/MeshBoolean.h"
#include "mesh_loader/MeshLoad.h"

int main() {

    std::cout << "Hello, World!" << std::endl;

    std::string filePath1 = R"(C:\Code\SculptPath\assets\test_mp_2.obj)";
    std::string filePath2 = R"(C:\Code\SculptPath\assets\cube.obj)";
    Slicer slicer;
    Settings settings;
    slicer.sliceFile(filePath1, settings);


    return 0;
}
