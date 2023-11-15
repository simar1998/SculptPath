//
// Created by simar on 11/15/2023.
//

#ifndef SCULPTPATH_INTERSECT_H
#define SCULPTPATH_INTERSECT_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include "../mesh_loader/MeshLoad.h"
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>

enum IntersectType {one_point, two_point};
class Intersect {


public :

    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Ray_3 Ray_3;
    typedef Kernel::Point_3 Point_3;
    typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
    typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
    typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;

    Mesh mesh;
    MeshLoad meshLoad;

    explicit Intersect(MeshLoad m, MeshLoad meshLoad);

    std::vector<Point_3> gridIntersect(double zOffset, double gridRes);

    //TODO create intersect return type
    std::vector<Point_3> rayIntersect(Ray_3 ray, IntersectType type);

};


#endif //SCULPTPATH_INTERSECT_H
