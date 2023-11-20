//
// Created by simar on 11/20/2023.
//

#ifndef SCULPTPATH_MESHGENERATOR_H
#define SCULPTPATH_MESHGENERATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <sstream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Delaunay_triangulation_3<Kernel> Delaunay;
typedef Kernel::Point_3 Point_3;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;

class MeshGenerator {
public:
    MeshGenerator();
    void addPoint(const Point_3& point);
    void generateMesh();
    const Polyhedron& getMesh() const; // Getter for the mesh

private:
    std::vector<Point_3> points;
    Polyhedron polyhedron;
};


#endif //SCULPTPATH_MESHGENERATOR_H
