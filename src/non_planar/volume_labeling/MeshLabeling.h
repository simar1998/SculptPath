//
// Created by simar on 11/28/2023.
//

#ifndef SCULPTPATH_MESHLABELING_H
#define SCULPTPATH_MESHLABELING_H

#include <string>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

class MeshLabeling {

    Polyhedron mesh;

public:
    explicit MeshLabeling(const std::string& filePath);
    void performSegmentation();
    void identifyNonPlanarSurfaces();
    void identifyCurves();



private:
    std::string filePath;
    void analyzeSurfacePatch();
    void detectEdges();
    void detectRidges();
};


#endif //SCULPTPATH_MESHLABELING_H
