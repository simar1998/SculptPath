//
// Created by Simarpal Kalsi on 2024-02-16.
//

#ifndef NONPLANAR_INTERSECT_H
#define NONPLANAR_INTERSECT_H

#include "Geometry.h"
#include <vector>
#include <string>

/**
 * This class is responsible for performing intersection operations.
 * This only has the basic intersection methods in it.
 * Complex stuff like grid intersection and globular intersection will be in different classes and reference this one.
 */

enum class intersectionAlgorithm {
    MOLLER_TROMBORE,
};

class Intersect {
public:
    Intersect(std::vector<Triangle> trianglesPtr);

    Intersect();

    std::vector<Vertex> rayIntersect(const Ray& ray, intersectionAlgorithm algorithm = intersectionAlgorithm::MOLLER_TROMBORE);

    std::vector<Triangle> triangles;

    // Intersection functions

    std::vector<Vertex> planeIntersect(double z);
    bool isPointInMesh(const Vertex& point);
    std::vector<float> getBoundingVals();
};


#endif //NONPLANAR_INTERSECT_H
