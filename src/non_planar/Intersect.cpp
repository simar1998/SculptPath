//
// Created by simar on 11/15/2023.
//

#include "Intersect.h"


//Creates plane at zOffset from top of mesh and generates a grid from which rays are generated pointing down
std::vector<Intersect::Point_3> Intersect::gridIntersect(double zOffset, double gridRes) {

    MeshLoad meshLoad(filePath);
    Mesh mesh = meshLoad.getMesh();

    std::vector<Point_3> intersect_points;
    std::vector<Point_3> grid_points;
    for (double x = meshLoad.x_min; x <= meshLoad.x_max; x += gridRes) {
        for (double y = meshLoad.y_min; y <= meshLoad.y_max; y += gridRes) {
            grid_points.push_back(Point_3(x, y, meshLoad.z_max + zOffset));
        }
    }

    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    for (const MeshLoad::Point_3& grid_point : grid_points) {
        // Create a ray shooting down from the grid point
        Ray_3 ray(grid_point, Point_3(grid_point.x(), grid_point.y(), grid_point.z() - 1));

        // Check for intersection with the mesh
        auto intersection = tree.first_intersection(ray);

        if (intersection) {
            if (const Point_3* p = boost::get<Point_3>(&intersection->first)) {
                intersect_points.push_back(*p);
                std::cout << "Ray intersected at: " << *p << std::endl;
            }
        }
    }
    return intersect_points;
}

//Performs ray intersect with mesh
std::vector<Intersect::Point_3> Intersect::rayIntersect(Intersect::Ray_3 ray, IntersectType type) {
    std::vector<Point_3> intersection_points;

    MeshLoad meshLoad(filePath);
    Mesh mesh = meshLoad.getMesh();

    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    if (type == one_point) {
        auto intersection = tree.first_intersection(ray);
        if (intersection) {
            if (const Point_3* p = boost::get<Point_3>(&intersection->first)) {
                intersection_points.push_back(*p);
            }
        }
    } else if (type == two_point) {
        //TODO
    }

    // Process the intersection points
    for (const auto& point : intersection_points) {
        std::cout << "Intersection at: " << point << std::endl;
    }
    return intersection_points;
}



