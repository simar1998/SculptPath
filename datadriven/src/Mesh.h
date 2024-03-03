#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "Geometry.h"

class Mesh {
public:
    explicit Mesh(bool printOutput = false);
    explicit Mesh(const std::string& filePath, bool printOutput = false);
    void readMeshFile(const std::string &filePath);

    [[nodiscard]] const std::vector<Triangle>& getTriangles() const;

    std::vector<Triangle> triangles;
    bool printOutput{}; // Flag to control printing output

private:

    bool isAsciiSTL(const std::string& filePath);
    void readAsciiSTL(const std::string& filePath);
    void readBinarySTL(const std::string& filePath);
    void readOBJ(const std::string& filePath);

    void readSTL(const std::string &filePath);


};

#endif // MESH_H
