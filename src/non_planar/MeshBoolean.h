//
// Created by simar on 11/15/2023.
//

#ifndef SCULPTPATH_MESHBOOLEAN_H
#define SCULPTPATH_MESHBOOLEAN_H

#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
// Define the mesh type here or include the file that defines it


class MeshBoolean {

private:

    std::string filePath1;
    std::string filePath2;

public:
    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;

    Mesh m1;
    Mesh m2;


    MeshBoolean(std::string str1, std::string str2)
            : filePath1(std::move(str1)), filePath2(std::move(str2)) {}

    Mesh meshUnion();

};


#endif //SCULPTPATH_MESHBOOLEAN_H
