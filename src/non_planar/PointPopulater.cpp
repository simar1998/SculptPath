//
// Created by simar on 11/20/2023.
//

#include "PointPopulater.h"
#include <CGAL/convex_hull_3.h>

PointPopulator::PointPopulator() {}

std::vector<Point_3> PointPopulator::populatePoints(const Polyhedron& mesh) {
    std::vector<Point_3> points;

    // Determine the number of points to generate (this could be based on mesh size, user input, etc.)
    size_t numPoints = 100; // Example value, will need dynamic logic to get this number. needs to be heuristic

    for (size_t i = 0; i < numPoints; ++i) {
        Point_3 newPoint;
        do {
            newPoint = generatePoint(mesh);
        } while (!isInside(newPoint, mesh));
        points.push_back(newPoint);
    }

    return points;
}

bool PointPopulator::isInside(const Point_3& point, const Polyhedron& mesh) {
    // Implement point-in-polyhedron test using ray tracing

    return true; // Placeholder
}

Point_3 PointPopulator::generatePoint(const Polyhedron& mesh) {
    // Generate a point within the bounding box of the mesh

    return Point_3(0, 0, 0); // Placeholder
}