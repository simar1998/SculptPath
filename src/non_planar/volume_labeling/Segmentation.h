//
// Created by simar on 11/30/2023.
//

#ifndef SCULPTPATH_SEGMENTATION_H
#define SCULPTPATH_SEGMENTATION_H

#include <string>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   Kernel;
typedef Kernel::Point_3                                       Point_3;

typedef CGAL::Surface_mesh<Point_3>                           Mesh;

typedef boost::graph_traits<Mesh>::vertex_descriptor          vertex_descriptor;
typedef boost::graph_traits<Mesh>::face_descriptor            face_descriptor;


class Segmentation {

    std::string filePath;

public:
    explicit Segmentation(const std::string& filePath);

    void performSegSDF();
};


#endif //SCULPTPATH_SEGMENTATION_H
