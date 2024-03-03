//
// Created by Simarpal Kalsi on 2024-02-22.
//

#include "PlanarDispertionRayCast.h"
#include "../Intersect.h"

std::vector<Vertex> PlanarDispertionRayCast::init(Mesh &mesh, Vertex vertex, int points) {
    std::vector<Ray> rays;
    for (int i = 0; i < points; i++) {
        double angle = (double)i / points * 2.0 * M_PI;
        Vertex direction(cos(angle), sin(angle), 0);
        rays.emplace_back(vertex.position, direction.position);
    }
    //Perform intersect // Code block seperated between up and down for organization
    std::vector<Vertex> intersectionPoints;
    Intersect intersect(mesh.getTriangles());
    for(Ray r : rays){
        std::vector<Vertex> hit = intersect.rayIntersect(r);
        if (!hit.empty()){
            intersectionPoints.insert(intersectionPoints.end(), hit.begin(), hit.end());
        }
    }
    return intersectionPoints;
}
