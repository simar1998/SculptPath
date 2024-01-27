#include <iostream>

#include "mesh_loader/MeshLoad.h"
#include "non_planar/Slicer.h"
#include "non_planar/MeshBoolean.h"
#include "mesh_loader/MeshLoad.h"

int main(int argc, char  *argv[]) {

    std::cout << "Welcome to Sculpt Plath Non Planar Gcode Generation!" << std::endl;

//    if(argc != 2) {
//        std::cout << "Usage: " << argv[0] << " <file1>" << std::endl;
//        return 1;
//    }
//    std::string filePath1 =argv[1];
    Slicer slicer;
    Settings settings;
    slicer.sliceFile("", settings);
    return 0;
}
