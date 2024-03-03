//
// Created by Simarpal Kalsi on 2024-02-20.
//

#ifndef NONPLANAR_GLOBULARCAST_H
#define NONPLANAR_GLOBULARCAST_H

#include "../Mesh.h"

std::vector<Vertex> globularRayIntersect(Mesh& mesh, Vertex originPoint);
std::vector<Vertex> generateModifiedFibonacciPoints(int numPoints, double radius, double height, Vertex originPoint);


#endif //NONPLANAR_GLOBULARCAST_H
