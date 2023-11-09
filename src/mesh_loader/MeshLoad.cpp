//
// Created by simar on 11/8/2023.
//

#include "MeshLoad.h"
#include <fstream>
#include <vector>


/**
 * Standard constructor that sets up the file path for mesh
 * @param filePath
 */
MeshLoad::MeshLoad(std::string& filePath) {
    MeshLoad::filePath = filePath;
}

/**
 * Gets the mesh file format and returns enum of the type
 * @param check
 * @return
 */
FileType MeshLoad::getMeshFormat(bool check) {

    std::string extension;
    size_t dotPos = filePath.find_last_of('.');

    if (dotPos != std::string::npos){
        extension = filePath.substr(dotPos + 1);
    }

    if (std::equal(extension.begin(), extension.end(),"stl")){
        return STL;
    } else if (std::equal(extension.begin(), extension.end(),"obj")){
        return OBJ;
    }

    //TODO write code for checking if each format is correctly structured

}

/**
 * Loads the mesh into CGAL's standard polygon mesh stuff based on type
 */
void MeshLoad::loadMesh() {

    /**
     * Standard stl file loader
     */
    if (getMeshFormat(false) == STL) {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file " << filePath << std::endl;
            return;
        }

        file.ignore(80); // Ignores STL header 80 bytes

        unsigned int numTriangles;
        file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

        for (unsigned int i = 0; i < numTriangles; ++i) {
            float normal[3], vertex[3][3];
            file.read(reinterpret_cast<char*>(normal), 3 * sizeof(float)); // normal is not used

            for (int j = 0; j < 3; ++j) {
                file.read(reinterpret_cast<char*>(vertex[j]), 3 * sizeof(float));
            }

            file.ignore(2); // Skipping the attribute byte count

            std::vector<Mesh::Vertex_index> face_vertices;
            for (int j = 0; j < 3; ++j) {
                face_vertices.push_back(mesh.add_vertex(Point(vertex[j][0], vertex[j][1], vertex[j][2])));
            }
            mesh.add_face(face_vertices);
        }

        if (file.fail()) {
            std::cerr << "Error reading file " << filePath << std::endl;
        }

        file.close();
    }
    /**
     * Standard file mesh loader for OBJ file format
     */
     //TODO not OBJ | fixme
    else if (getMeshFormat(false) == OBJ) {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file " << filePath << std::endl;
            return;
        }

        file.ignore(80); // Ignores STL header 80 bytes

        unsigned int numTriangles;
        file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

        for (unsigned int i = 0; i < numTriangles; ++i) {
            float normal[3], vertex[3][3];
            file.read(reinterpret_cast<char*>(normal), 3 * sizeof(float)); // normal is not used

            for (int j = 0; j < 3; ++j) {
                file.read(reinterpret_cast<char*>(vertex[j]), 3 * sizeof(float));
            }

            file.ignore(2); // Skipping the attribute byte count

            std::vector<Mesh::Vertex_index> face_vertices;
            for (int j = 0; j < 3; ++j) {
                face_vertices.push_back(mesh.add_vertex(Point(vertex[j][0], vertex[j][1], vertex[j][2])));
            }
            mesh.add_face(face_vertices);
        }

        std::cout << "Opened file as OBJ format" << std::endl;

        if (file.fail()) {
            std::cerr << "Error reading file " << filePath << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Unsupported file format." << std::endl;
    }
}