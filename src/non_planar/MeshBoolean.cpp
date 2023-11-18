//
// Created by simar on 11/15/2023.
//

#include "MeshBoolean.h"
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include "CGAL/IO/OBJ.h"

using namespace CGAL::Polygon_mesh_processing;

/**
 * Mesh boolean union function
 * @return
 */
MeshBoolean::Mesh MeshBoolean::meshUnion() {
    Mesh out;

    // Copy input meshes
    Mesh m1;
    Mesh m2;

    if (!CGAL::IO::read_OBJ(filePath1, m1)) {
        std::cerr << "Failed to load mesh from " << filePath1 << std::endl;
    }

    if (!CGAL::IO::read_OBJ(filePath2, m2)) {
        std::cerr << "Failed to load mesh from " << filePath2 << std::endl;
    }
    // Triangulate both meshes
    triangulate_faces(m1);
    triangulate_faces(m2);

    // Perform the union operation
    bool valid_union = corefine_and_compute_union(m1, m2, out);

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

MeshBoolean::Mesh MeshBoolean::meshDifference() {

    Mesh out;

    // Copy input meshes
    Mesh m1;
    Mesh m2;

    if (!CGAL::IO::read_OBJ(filePath1, m1)) {
        std::cerr << "Failed to load mesh from " << filePath1 << std::endl;
    }

    if (!CGAL::IO::read_OBJ(filePath2, m2)) {
        std::cerr << "Failed to load mesh from " << filePath2 << std::endl;
    }
    // Triangulate both meshes
    triangulate_faces(m1);
    triangulate_faces(m2);

    bool valid_difference = corefine_and_compute_difference(m1, m2, out);


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

MeshBoolean::Mesh MeshBoolean::meshIntersection() {

    Mesh out;

    // Copy input meshes
    Mesh m1;
    Mesh m2;

    if (!CGAL::IO::read_OBJ(filePath1, m1)) {
        std::cerr << "Failed to load mesh from " << filePath1 << std::endl;
    }

    if (!CGAL::IO::read_OBJ(filePath2, m2)) {
        std::cerr << "Failed to load mesh from " << filePath2 << std::endl;
    }
    // Triangulate both meshes
    triangulate_faces(m1);
    triangulate_faces(m2);

    bool valid_intersection = corefine_and_compute_intersection(m1, m2, out);

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
