//
// Created by simar on 11/25/2023.
//

#ifndef SCULPTPATH_MESHTRIANGULATION_H
#define SCULPTPATH_MESHTRIANGULATION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <string>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_3<K> Delaunay;
typedef K::Point_3 Point;

class MeshTriangulation {
public:
    explicit MeshTriangulation(const std::string& objFilePath);
    void performTriangulation();
    void iterateVolume();

private:
    std::vector<Point> readObjFile(const std::string& filePath);
    Delaunay triangulation;
};

#endif //SCULPTPATH_MESHTRIANGULATION_H
