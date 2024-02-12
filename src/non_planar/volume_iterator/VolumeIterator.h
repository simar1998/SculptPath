//
// Created by simar on 12/10/2023.
//

#ifndef SCULPTPATH_VOLUMEITERATOR_H
#define SCULPTPATH_VOLUMEITERATOR_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <string>
#include "../../mesh_loader/MeshLoad.h"

class VolumeIterator {

    std::string filePath;


    typedef CGAL::Simple_cartesian<double> K;
    typedef CGAL::Surface_mesh<K::Point_3> Mesh;
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Ray_3 Ray_3;
    typedef Kernel::Point_3 Point_3;
    typedef Kernel::Vector_3 Vector_3;
    typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
    typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
    typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;

    public :

    Tree tree;//Mesh tree object for AABB mesh tree





    //Mesh object
    Mesh mesh;

    VolumeIterator(std::string str) : filePath(std::move(str)){};

    MeshLoad load;

    std::string startIteratorOperations();

    void initMesh();

    void initVolumeTraversal();
    
private :

    std::vector<Point_3> createCandidatePoints(std::vector<Point_3> intersect);

   

};


#endif //SCULPTPATH_VOLUMEITERATOR_H
