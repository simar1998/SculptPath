//
// Created by simar on 11/14/2023.
//
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include "Settings.h"

#ifndef SCULPTPATH_SLICER_H
#define SCULPTPATH_SLICER_H


class Slicer {



public:

    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;
    typedef Mesh::Vertex_index vertex_descriptor;
    typedef Mesh::Face_index face_descriptor;
    typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
    typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
    typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;


    void sliceFile(std::string filePath, Settings settings);


};


#endif //SCULPTPATH_SLICER_H
