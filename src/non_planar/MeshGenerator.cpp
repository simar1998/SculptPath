//
// Created by simar on 11/20/2023.
//

#include "MeshGenerator.h"
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/IO/OFF.h>

MeshGenerator::MeshGenerator() {}

void MeshGenerator::addPoint(const Point_3& point) {
    points.push_back(point);
}

void MeshGenerator::generateMesh() {
    polyhedron.clear();
    CGAL::convex_hull_3(points.begin(), points.end(), polyhedron);
}


const Polyhedron& MeshGenerator::getMesh() const {
    return polyhedron;
}