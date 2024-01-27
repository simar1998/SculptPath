//
// Created by simar on 11/15/2023.
//

#include "Intersect.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include <iostream>
#include <fstream>
#include "MeshException.h"



//Creates plane at zOffset from top of mesh and generates a grid from which rays are generated pointing down
std::vector<Intersect::Point_3> Intersect::gridIntersect(double zOffset, double gridRes) {

    MeshLoad meshLoad(filePath);
    meshLoad.loadMesh();
    Mesh mesh = meshLoad.getMesh();
    meshLoad.getMeshBounding();



    std::vector<Point_3> intersect_points;
    std::vector<Point_3> grid_points;
    for (double x = meshLoad.x_min; x <= meshLoad.x_max; x += gridRes) {
        for (double y = meshLoad.y_min; y <= meshLoad.y_max; y += gridRes) {
            grid_points.push_back(Point_3(x, y, meshLoad.z_max + zOffset));
        }
    }

    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    if (tree.empty()){
        std::cerr << "The loaded mesh tree is empty" << std::endl;
    }

    std::cout << "Number of grid points in the grid" << grid_points.size() << std::endl;

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

    std::cout << "Number of intersect points in the mesh" << intersect_points.size() << std::endl;
    return intersect_points;
}

std::vector<Intersect::Point_3> Intersect::gridIntersectRefined(double zOffset, double gridRes, double refineRes) {

    MeshLoad meshLoad(filePath);
    meshLoad.loadMesh();
    Mesh mesh = meshLoad.getMesh();
    meshLoad.getMeshBounding();

    if(meshLoad.getMesh().is_empty()){
        std::cerr << "Mesh Load Failed, nothing is loaded into the mesh" << std::endl;
    }

    std::vector<Point_3> intersect_points;
    std::vector<Point_3> grid_points;
    std::vector<Point_3> no_hit_points;

    for (double x = meshLoad.x_min; x <= meshLoad.x_max; x += gridRes) {
        for (double y = meshLoad.y_min; y <= meshLoad.y_max; y += gridRes) {
            grid_points.push_back(Point_3(x, y, meshLoad.z_max + zOffset));
        }
    }

    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    for (const MeshLoad::Point_3& grid_point : grid_points) {
        Ray_3 ray(grid_point, Point_3(grid_point.x(), grid_point.y(), grid_point.z() - 1));
        auto intersection = tree.first_intersection(ray);

        if (intersection) {
            if (const Point_3* p = boost::get<Point_3>(&intersection->first)) {
                intersect_points.push_back(*p);
                std::cout << "Ray intersected at: " << *p << std::endl;
            }
        } else {
            no_hit_points.push_back(grid_point);
        }
    }

    std::cout << "No Hit points size : " << no_hit_points.size() << std::endl;

    // Adaptive refinement for rays that did not hit the mesh
    for (const MeshLoad::Point_3& no_hit_point : no_hit_points) {
        // Refine around the no-hit point within a specified smaller interval
        for (double x = no_hit_point.x() - refineRes; x <= no_hit_point.x() + refineRes; x += refineRes / 2) {
            for (double y = no_hit_point.y() - refineRes; y <= no_hit_point.y() + refineRes; y += refineRes / 2) {
                Point_3 refine_point(x, y, meshLoad.z_max + zOffset);
                Ray_3 refine_ray(refine_point, Point_3(refine_point.x(), refine_point.y(), refine_point.z() - 1));
                auto refine_intersection = tree.first_intersection(refine_ray);

                if (refine_intersection) {
                    if (const Point_3* p = boost::get<Point_3>(&refine_intersection->first)) {
                        intersect_points.push_back(*p);
                        std::cout << "Refined ray intersected at: " << *p << std::endl;
                    }
                }
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

bool Intersect::isPointInMesh(const Point_3& point, Mesh &mesh) {
   /** MeshLoad meshLoad(filePath);
    meshLoad.loadMesh();
    Mesh mesh = meshLoad.getMesh();
**/
    // Ensure the mesh is loaded
    if (mesh.is_empty()) {
        std::cerr << "Mesh Load Failed, nothing is loaded into the mesh" << std::endl;
        return false;
    }

    // Build an AABB tree for the mesh
    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    // Create a Side_of_triangle_mesh object
    CGAL::Side_of_triangle_mesh<Mesh, K> inside_tester(tree);

    // Check if the point is inside the mesh
    return inside_tester(point) == CGAL::ON_BOUNDED_SIDE;
}

std::vector<Intersect::Point_3> Intersect::planeIntersect(double zHeight) {
    std::vector<Intersect::Point_3> intersectPoint;



    return std::vector<Intersect::Point_3>();
}

/**
 * Added the globular mesh intersection at point class to create a globular ray burst at point and collect intersection results to return to caller. Presumes mesh is aolready loaded to
 * avoid reloading the mesh
 * @param originPoint
 * @param globularDensity
 * @param meshLoad
 * @return
 */
std::vector<GlobularResult> Intersect::globularIntersectionAtPoint(Intersect::Point_3 originPoint, double globularDensity, MeshLoad meshLoad) {
    std::vector<GlobularResult> result;

    Mesh mesh = meshLoad.getMesh();
    if (mesh.is_empty()) {
        throw std::runtime_error("Mesh Load Failed, nothing is loaded into the mesh");
    }

    std::cout << "Globular Ray Intersect" << std::endl;

    int numPoints = 1000;
    double scaleFactor = 1.5;
    double offset = 0.0;

    std::vector<Intersect::Ray_3> globularRays = generateModifiedFibonacciPoints(numPoints, scaleFactor, offset, originPoint);

    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    for (const auto& ray : globularRays) {
        auto intersection = tree.first_intersection(ray);

        if (intersection) {
            if (const Point_3* p = boost::get<Point_3>(&intersection->first)) {
                // Store the intersection result
                GlobularResult result1(originPoint, ray, *p);
                result.emplace_back(result1);
            }
        }
    }

    return result;
}
/**
 * Generates fibonacci lattice at point for globular ray brust
 * @param numberOfPoints
 * @param scaleFactor
 * @param offset
 * @param originPoint
 * @return
 */
std::vector<Intersect::Ray_3> Intersect::generateModifiedFibonacciPoints(int numberOfPoints, double scaleFactor, double offset, Intersect::Point_3 originPoint) {
    std::vector<Intersect::Ray_3> rays;
    double goldenRatio = (std::sqrt(5.0) + 1.0) / 2.0;

    for (int i = 0; i < numberOfPoints; ++i) {
        double theta = 2 * M_PI * i / goldenRatio;
        double phi = acos(1 - (2 * (i + 0.5) / numberOfPoints));
        double x = std::cos(theta) * std::sin(phi);
        double y = std::sin(theta) * std::sin(phi);
        double z = std::cos(phi);
        Intersect::Ray_3 ray(originPoint, Intersect::Point_3 (x, y, z));
        rays.emplace_back(ray);
    }

    return rays;
}

