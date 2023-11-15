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


}
