#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <cstring>


Mesh::Mesh(const std::string& filePath, bool printOutput) : printOutput(printOutput) {
    readMeshFile(filePath);
}

const std::vector<Triangle>& Mesh::getTriangles() const {
    return triangles;
}

bool Mesh::isAsciiSTL(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file." << std::endl;
        return false;
    }

    char header[6]; // Enough to hold "solid"
    file.read(header, 5);
    header[5] = '\0';

    file.close();

    return std::strncmp(header, "solid", 5) == 0;
}

void Mesh::readAsciiSTL(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    Triangle currentTriangle;
    int vertexCount = 0; // To track the number of vertices read for the current triangle

    while (std::getline(file, line)) {
        // Trim leading and trailing spaces from the line (if necessary)
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.find("vertex") != std::string::npos) {
            glm::vec3 v;
            std::sscanf(line.c_str(), "vertex %f %f %f", &v.x, &v.y, &v.z);

            if (printOutput) {
                std::cout << "Vertex: " << v.x << ", " << v.y << ", " << v.z << std::endl;
            }

            currentTriangle.vertices[vertexCount++].position = v;
            if (vertexCount == 3) { // A triangle is complete
                triangles.push_back(currentTriangle);
                vertexCount = 0; // Reset for the next triangle
            }
        }
    }

    if (vertexCount != 0) {
        std::cerr << "Warning: The last triangle does not have 3 vertices." << std::endl;
    }
}

void Mesh::readBinarySTL(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file." << std::endl;
        return;
    }

    char header[80];
    file.read(header, 80); // Skip the header

    unsigned int numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), 4);

    triangles.reserve(numTriangles);

    for (unsigned int i = 0; i < numTriangles; ++i) {
        char buffer[50]; // Each triangle is 50 bytes
        file.read(buffer, 50);

        Triangle tri;
        for (int j = 0; j < 3; ++j) {
            glm::vec3 v;
            // Offset for each vertex in the buffer: 12 bytes for normal, then 12 bytes per vertex
            std::memcpy(&v, buffer + 12 + j * 12, 12);

            tri.vertices[j].position = v;

            if (printOutput) {
                std::cout << "Vertex: " << v.x << ", " << v.y << ", " << v.z << std::endl;
            }
        }
        triangles.push_back(tri);
    }
}

void Mesh::readSTL(const std::string& filePath) {
    if (isAsciiSTL(filePath)) {
        std::cout << "Reading ASCII STL file." << std::endl;
        readAsciiSTL(filePath);
    } else {
        std::cout << "Reading Binary STL file." << std::endl;
        readBinarySTL(filePath);
    }
}


void Mesh::readOBJ(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") { // Vertex data
            glm::vec3 v;
            std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
            std::cout << "Vertex: " << v.x << ", " << v.y << ", " << v.z << std::endl;
        }
    }
}

void Mesh::readMeshFile(const std::string& filePath) {
    // Determine file type by extension, for simplicity
    if (filePath.substr(filePath.find_last_of(".") + 1) == "stl" || filePath.substr(filePath.find_last_of(".") + 1) == "STL") {
        readSTL(filePath);
    } else if (filePath.substr(filePath.find_last_of(".") + 1) == "obj" || filePath.substr(filePath.find_last_of(".") + 1) == "OBJ") {
        std::cout << "Reading ASCII OBJ file." << std::endl;
        readOBJ(filePath);
    } else {
        std::cerr << "Unsupported file format." << std::endl;
    }
}

Mesh::Mesh(bool printOutput) {}

