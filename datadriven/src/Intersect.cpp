//
// Created by Simarpal Kalsi on 2024-02-16.
//

#include "Intersect.h"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include <utility>

#define EPSILON 0.000001f

Intersect::Intersect(std::vector<Triangle> trianglesPtr) {
    triangles = std::move(trianglesPtr);
}

/**
 * Intersect a ray with the mesh
 * @param ray
 * @param algorithm
 * @return
 */
std::vector<Vertex> Intersect::rayIntersect(const Ray &ray, const intersectionAlgorithm algorithm)
{
    if (algorithm == intersectionAlgorithm::MOLLER_TROMBORE)
    {
        std::vector<Vertex> intersectedVertices;
        
        for (const auto& triangle : triangles)
        {
            const Vertex& v0 = triangle.vertices[0];
            const Vertex& v1 = triangle.vertices[1];
            const Vertex& v2 = triangle.vertices[2];
            
            glm::vec3 edge1 = v1.position - v0.position;
            glm::vec3 edge2 = v2.position - v0.position;
            glm::vec3 h = glm::cross(ray.direction, edge2);
            float a = glm::dot(edge1, h);
            
            if (a > -EPSILON && a < EPSILON)
                continue;
            
            float f = 1.0f / a;
            glm::vec3 s = ray.origin - v0.position;
            float u = f * glm::dot(s, h);
            
            if (u < 0.0f || u > 1.0f)
                continue;
            
            glm::vec3 q = glm::cross(s, edge1);
            float v = f * glm::dot(ray.direction, q);
            
            if (v < 0.0f || u + v > 1.0f)
                continue;
            
            float t = f * glm::dot(edge2, q);
            
            if (t > EPSILON)
            {
                Vertex intersectedVertex;
                intersectedVertex.position = ray.origin + t * ray.direction;
                intersectedVertices.push_back(intersectedVertex);
            }
        }
        
        return intersectedVertices;
    }
    
    return std::vector<Vertex>();
}

/**
 * Intersect a plane with the mesh, only on the z axis
 * @param z
 * @return
 */
std::vector<Vertex> Intersect::planeIntersect(double z) {
    std::vector<Vertex> intersectedVertices;
    
    for (const auto& triangle : triangles)
    {
        const Vertex& v0 = triangle.vertices[0];
        const Vertex& v1 = triangle.vertices[1];
        const Vertex& v2 = triangle.vertices[2];
        
        // Check if the triangle intersects with the plane
        if ((v0.position.z <= z && v1.position.z >= z) || (v0.position.z >= z && v1.position.z <= z))
        {
            // Calculate the intersection point
            float t = (z - v0.position.z) / (v1.position.z - v0.position.z);
            glm::vec3 intersectionPoint = v0.position + t * (v1.position - v0.position);
            
            // Append the intersection point to the vector list
            Vertex intersectedVertex;
            intersectedVertex.position = intersectionPoint;
            intersectedVertices.push_back(intersectedVertex);
        }
    }
    
    return intersectedVertices;
}

/**
 * Check if a point is inside the mesh
 * @param point
 * @return
 */
bool Intersect::isPointInMesh(const Vertex &point) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.0001, 0.0001);
    glm::vec3 direction = glm::vec3(1.0f + dis(gen), dis(gen), dis(gen));

    Ray ray(point.position, direction);
    int count = 0;

    for (const auto& triangle : triangles) {
        const Vertex& v0 = triangle.vertices[0];
        const Vertex& v1 = triangle.vertices[1];
        const Vertex& v2 = triangle.vertices[2];

        glm::vec3 edge1 = v1.position - v0.position;
        glm::vec3 edge2 = v2.position - v0.position;
        glm::vec3 h = glm::cross(ray.direction, edge2);
        float a = glm::dot(edge1, h);

        if (a > -EPSILON && a < EPSILON)
            continue;

        float f = 1.0f / a;
        glm::vec3 s = ray.origin - v0.position;
        float u = f * glm::dot(s, h);

        if (u < 0.0f || u > 1.0f)
            continue;

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(ray.direction, q);

        if (v < 0.0f || u + v > 1.0f)
            continue;

        float t = f * glm::dot(edge2, q);

        if (t > EPSILON) {
            count++;
        }
    }

    return count % 2 != 0;
}

std::vector<float> Intersect::getBoundingVals() {
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();
    float maxZ = std::numeric_limits<float>::min();

    for (const auto& triangle : triangles) {
        for (const auto& vertex : triangle.vertices) {
            minX = std::min(minX, vertex.position.x);
            minY = std::min(minY, vertex.position.y);
            minZ = std::min(minZ, vertex.position.z);
            maxX = std::max(maxX, vertex.position.x);
            maxY = std::max(maxY, vertex.position.y);
            maxZ = std::max(maxZ, vertex.position.z);
        }
    }

    std::vector<float> boundingVals = {minX, minY, minZ, maxX, maxY, maxZ};

    // Print bounding values
    std::cout << "Bounding Values: ";
    for (const auto& val : boundingVals) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return boundingVals;
}

Intersect::Intersect() {}
