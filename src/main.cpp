#include <iostream>

#include "mesh_loader/MeshLoad.h"
#include "non_planar/Slicer.h"

int main() {

    std::cout << "Hello, World!" << std::endl;

    std::string filePath = R"(C:\Code\SculptPath\assets\test_mp_2.obj)";

    Slicer slicer;
    slicer.sliceFile(filePath);


    return 0;
}
