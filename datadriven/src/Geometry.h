//
// Created by Simarpal Kalsi on 2024-02-16.
//

// Custom type for storing geometry, however probably will give issues with future code taken from libraries

#ifndef NONPLANAR_GEOMETRY_H
#define NONPLANAR_GEOMETRY_H

#include <glm/vec3.hpp>
#include <cmath>

struct Vertex {
    explicit Vertex(float x, float y, float z) : position(x, y, z) {}
    explicit Vertex(const glm::vec3 &position) : position(position) {}
    explicit Vertex() = default;
    glm::vec3 position;
};

struct Triangle {
    explicit Triangle() {
    }

    Vertex vertices[3];
};

struct Ray {
    Ray(const glm::vec3 origin, glm::vec3 direction) {
        this->origin = origin;
        this->direction = direction;
    }




    glm::vec3 origin;
    glm::vec3 direction;
};

inline float getDistance(const Vertex& v1, const Vertex& v2) {
    float dx = v2.position.x - v1.position.x;
    float dy = v2.position.y - v1.position.y;
    float dz = v2.position.z - v1.position.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}



#endif //NONPLANAR_GEOMETRY_H