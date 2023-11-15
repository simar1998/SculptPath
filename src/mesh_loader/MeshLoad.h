//
// Created by simar on 11/8/2023.
//

#ifndef SCULPTPATH_MESHLOAD_H
#define SCULPTPATH_MESHLOAD_H


#include <string>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <iostream>
#include <fstream>
#include <string>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>

enum FileType {STL, OBJ};
class MeshLoad {


    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;
    typedef Mesh::Vertex_index vertex_descriptor;
    typedef Mesh::Face_index face_descriptor;



    std::string filePath;



public:

    explicit MeshLoad(std::string& filePath);

    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Point_3 Point_3;
    typedef Kernel::Point_3 Point;
    typedef Kernel::Ray_3 Ray_3;
    typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
    typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
    typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;

    Mesh m;
    Mesh ch;
    void loadMesh();

    const Mesh &getMesh() const;

private:

    Mesh mesh;  // Declare the mesh variable
    FileType getMeshFormat(bool check);


};


#endif //SCULPTPATH_MESHLOAD_H
