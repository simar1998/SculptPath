//
// Created by simar on 11/15/2023.
//

#include "MeshBoolean.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>

using namespace CGAL::Polygon_mesh_processing;
/**
 * Contructor for multiple mesh
 * @param m1
 * @param m2
 */

MeshBoolean::MeshBoolean(MeshBoolean::Mesh m1, MeshBoolean::Mesh m2) {
    this -> m1 = m1;
    this -> m2 = m2;
}

MeshBoolean::Mesh MeshBoolean::meshUnion(const MeshBoolean::Mesh &mesh1, const MeshBoolean::Mesh &mesh2) {
    Mesh out;

    // Copy input meshes
    Mesh triangulated1 = mesh1;
    Mesh triangulated2 = mesh2;

    // Triangulate both meshes
    triangulate_faces(triangulated1);
    triangulate_faces(triangulated2);

    // Perform the union operation
    bool valid_union = corefine_and_compute_union(triangulated1, triangulated2, out);

    std::cout << "Union validity" << valid_union << std::endl;

    if (valid_union) {
        std::cout << "Union was successfully computed\n";
        bool write_success = CGAL::IO::write_polygon_mesh("union.off", out, CGAL::parameters::stream_precision(17));
        if (write_success) {
            std::cout << "File 'union.off' written successfully.\n";
        } else {
            std::cerr << "Failed to write file 'union.off'.\n";
        }
        return out; // Return the union mesh
    }



    // In case of failure, return an empty mesh or handle appropriately
    Mesh empty_mesh;
    return empty_mesh;
}
