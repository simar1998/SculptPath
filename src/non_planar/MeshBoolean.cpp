//
// Created by simar on 11/15/2023.
//

#include "MeshBoolean.h"
#include <CGAL/Polygon_mesh_processing/boolean_operations.h>

using namespace CGAL::Polygon_mesh_processing;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
namespace PMP = CGAL::Polygon_mesh_processing;

Mesh MeshBoolean::meshUnion(const Mesh& mesh1, const Mesh& mesh2) {
    Mesh result;
    corefine_and_compute_union(mesh1, mesh2, result);
    return result;
}

Mesh MeshBoolean::meshIntersection(const Mesh& mesh1, const Mesh& mesh2) {
    Mesh result;
    corefine_and_compute_intersection(mesh1, mesh2, result);
    return result;
}

Mesh MeshBoolean::meshDifference(const Mesh& mesh1, const Mesh& mesh2) {
    Mesh result;
    corefine_and_compute_difference(mesh1, mesh2, result);
    return result;
}

Mesh MeshBoolean::meshSymmetricDifference(const Mesh& mesh1, const Mesh& mesh2) {
    Mesh result;
    corefine_and_compute_symmetric_difference(mesh1, mesh2, result);
    return result;
}