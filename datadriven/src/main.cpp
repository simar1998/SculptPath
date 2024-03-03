#include <iostream>
#include <fstream>
#include <string>
#include "Mesh.h"
#include "volnag/VolumeNavigation.h"

int main(int argc, char *argv[]) {


    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <stl_file> <gcode_file> <output_dir> \n";
        return 1;
    }

    std::string meshFile = argv[1];
    std::string gcodeFile = argv[2];
    std::string outputDir = argv[3];

    VolumeNavigation volav(meshFile, gcodeFile, outputDir);

    return 0;
}