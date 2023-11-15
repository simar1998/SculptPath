//
// Created by simar on 11/14/2023.
//

#include "Slicer.h"
#include "../mesh_loader/MeshLoad.h"
#include <boost/optional.hpp>
#include <boost/variant.hpp>


typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Ray_3 Ray_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;
typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;

//Test Slice function
void Slicer::sliceFile(std::string filePath, Settings settings) {

    MeshLoad load(filePath);
    load.loadMesh();
    Mesh mesh = load.getMesh();//Gets the mesh to start ray intersection Test

    // Initialize the bounding box
    CGAL::Bbox_3 bbox = CGAL::bbox_3(mesh.points().begin(), mesh.points().end());

// Get the min and max coordinates
    double x_min = bbox.xmin();
    double x_max = bbox.xmax();
    double y_min = bbox.ymin();
    double y_max = bbox.ymax();
    double z_max = bbox.zmax();

    double grid_resolution = 0.5; // Distance between grid points
    double grid_height = 10.0; // Height of the grid above the mesh

    std::vector<Point_3> grid_points;
    for (double x = x_min; x <= x_max; x += grid_resolution) {
        for (double y = y_min; y <= y_max; y += grid_resolution) {
            grid_points.push_back(Point_3(x, y, z_max + grid_height));
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
                std::cout << "Ray intersected at: " << *p << std::endl;
            }
        }
    }
}
