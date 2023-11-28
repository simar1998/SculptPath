//
// Created by simar on 11/25/2023.
//

#include "MeshTriangulation.h"
#include <iostream>
#include <fstream>
#include <sstream>

MeshTriangulation::MeshTriangulation(const std::string& objFilePath) {
    auto points = readObjFile(objFilePath);
    triangulation.insert(points.begin(), points.end());
}

std::vector<Point> MeshTriangulation::readObjFile(const std::string& filePath) {
    std::vector<Point> points;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            double x, y, z;
            s >> x; s >> y; s >> z;
            points.emplace_back(x, y, z);
        }
    }

    return points;
}

void MeshTriangulation::performTriangulation() {
    // Triangulation is already performed in the constructor
}

void MeshTriangulation::iterateVolume() {
    for (auto it = triangulation.finite_cells_begin(); it != triangulation.finite_cells_end(); ++it) {
        Point p0 = it->vertex(0)->point();
        Point p1 = it->vertex(1)->point();
        Point p2 = it->vertex(2)->point();
        Point p3 = it->vertex(3)->point();

        std::cout << "Tetrahedron vertices: " << std::endl;
        std::cout << "p0: " << p0 << ", p1: " << p1 << ", p2: " << p2 << ", p3: " << p3 << std::endl;
    }
}