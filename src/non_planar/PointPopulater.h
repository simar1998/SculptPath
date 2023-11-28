//
// Created by simar on 11/20/2023.
//

#ifndef SCULPTPATH_POINTPOPULATER_H
#define SCULPTPATH_POINTPOPULATER_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Kernel::Point_3 Point_3;

class PointPopulator {
public:
    PointPopulator();

    // Function to populate points within the volume of a mesh
    std::vector<Point_3> populatePoints(const Polyhedron& mesh);

private:
    // Helper function to check if a point is inside the mesh
    bool isInside(const Point_3& point, const Polyhedron& mesh);

    // Function to generate a single point within the bounding box of the mesh
    Point_3 generatePoint(const Polyhedron& mesh);
};

#endif //SCULPTPATH_POINTPOPULATER_H
