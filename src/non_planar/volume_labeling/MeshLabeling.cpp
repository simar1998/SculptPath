//
// Created by simar on 11/28/2023.
//

#include "MeshLabeling.h"
#include <fstream>
#include <CGAL/IO/OBJ.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include <CGAL/mesh_segmentation.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/property_map.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;


MeshLabeling::MeshLabeling(const std::string& filePath) : filePath(filePath) {

    std::ifstream input(filePath, std::ios::in);
    if (!input) {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
        return;
    }
    CGAL::read(input, mesh);

    std::cout << "Mesh loaded successfully from " << filePath << std::endl;
}

void MeshLabeling::performSegmentation() {
    // Create a property-map for SDF values
    typedef std::map<face_descriptor, double> Facet_double_map;
    Facet_double_map internal_sdf_map;
    boost::associative_property_map<Facet_double_map> sdf_property_map(internal_sdf_map);

    // Compute SDF values
    CGAL::sdf_values(mesh, sdf_property_map);

    // Create a property-map for segment-ids
    typedef std::map<face_descriptor, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    boost::associative_property_map<Facet_int_map> segment_property_map(internal_segment_map);

    // Segment the mesh
    std::size_t number_of_segments = CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map);

    std::map<face_descriptor, std::size_t> face_indices;
    std::size_t index = 0;
    for (face_descriptor f : faces(mesh)) {
        face_indices[f] = index++;
    }
    // Output the result
    std::cout << "Number of segments: " << number_of_segments << std::endl;
    for (face_descriptor f : faces(mesh)) {
        std::cout << "Face " << face_indices[f] << " is in segment " << segment_property_map[f] << std::endl;
    }
}


//TODO make integrate diffrential plane detection
void MeshLabeling::identifyNonPlanarSurfaces() {
 //Will add segmenetation code here for test pursposes for no
}

void MeshLabeling::analyzeSurfacePatch() {
    // Fit a plane to the patch and calculate deviations
    // Mark as non-planar if deviations exceed a threshold
}

void MeshLabeling::identifyCurves() {
    detectEdges();
    detectRidges();
}

void MeshLabeling::detectEdges() {
    // Implement edge detection
}

void MeshLabeling::detectRidges() {
    // Implement ridge detection
}
//Compute sdf values for the mesh here
void MeshLabeling::computeSDF() {



}
