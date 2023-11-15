//
// Created by simar on 11/15/2023.
//

#ifndef SCULPTPATH_MESHBOOLEAN_H
#define SCULPTPATH_MESHBOOLEAN_H

#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
// Define the mesh type here or include the file that defines it


class MeshBoolean {
public:
    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;

    static Mesh meshUnion(const Mesh& mesh1, const Mesh& mesh2);
    static Mesh meshIntersection(const Mesh& mesh1, const Mesh& mesh2);
    static Mesh meshDifference(const Mesh& mesh1, const Mesh& mesh2);
    static Mesh meshSymmetricDifference(const Mesh& mesh1, const Mesh& mesh2);
};


#endif //SCULPTPATH_MESHBOOLEAN_H
