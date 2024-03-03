//
// Created by Simarpal Kalsi on 2024-02-17.
//

#include "../Intersect.h"
#include "../Mesh.h"
/**
 * Generates fibonacci lattice at point for globular ray brust
 * @param numberOfPoints
 * @param scaleFactor
 * @param offset
 * @param originPoint
 * @return
 */
extern std::vector<Ray> generateModifiedFibonacciPoints(int numberOfPoints, double scaleFactor, double offset, Vertex originPoint) {
    std::vector<Ray> rays;
    double goldenRatio = (std::sqrt(5.0) + 1.0) / 2.0;

    for (int i = 0; i < numberOfPoints; ++i) {
        double theta = 2 * M_PI * i / goldenRatio;
        double phi = acos(1 - (2 * (i + 0.5) / numberOfPoints));
        double x = std::cos(theta) * std::sin(phi);
        double y = std::sin(theta) * std::sin(phi);
        double z = std::cos(phi);
        Ray ray(originPoint.position, glm::vec3 (x, y, z));
        rays.emplace_back(ray);
    }

    return rays;
}

/**
 * Intersect a mesh with a globular ray
 * @param mesh
 * @param point
 * @return
 */
std::vector<Vertex> globularRayIntersect(Mesh& mesh, Vertex point) {

    std::vector<Vertex> intersectedPoints;
    std::vector<Ray> rays = generateModifiedFibonacciPoints(25, 1, 0, point);

    Intersect intersect(mesh.getTriangles());
    for (auto &ray : rays) {
        std::vector<Vertex> intersectedVertices = intersect.rayIntersect(ray);

           if(!intersectedVertices.empty()) {
               intersectedPoints.push_back(intersectedVertices[0]);
           }
    }

    return intersectedPoints;

}
