#include <iostream>

#include "mesh_loader/MeshLoad.h"

int main() {

    std::cout << "Hello, World!" << std::endl;

    std::string filePath = "C:\\Code\\SculptPath\\assets\\test_mp_2.stl";

    MeshLoad load(filePath);
    load.loadMesh();


    return 0;
}
