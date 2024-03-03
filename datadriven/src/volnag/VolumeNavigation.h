//
// Created by Simarpal Kalsi on 2024-02-17.
//

#ifndef NONPLANAR_VOLUMENAVIGATION_H
#define NONPLANAR_VOLUMENAVIGATION_H
#include "../Mesh.h"
#include "VolnavPoint.h"
#include "../settings/Settings.h"
#include "../Intersect.h"

class VolumeNavigation {
public:

    struct GcodePoint {
        float x, y, z;
    };

    struct GcodeBounds {
        glm::vec3 min, max;
    };

    VolumeNavigation();
    VolumeNavigation(std::string meshFile, std::string gcodeFile, std::string outputLoc);
    VolumeNavigation(const Mesh &mesh, const Settings &settings);

    Mesh mesh;
    void startVolNav();
    Settings settings;
    Intersect intersect;
    Vertex meshCentroid;
    GcodeBounds gcodeBounds;
    glm::vec3 gcodeCentroid;
    std::vector<VolnavPoint> volnavPoints;

private:



    Vertex initPoint();
    Vertex nextPoint();

    float volnavFinished();
    float costPerimeter();
    std::vector<Vertex> initBottom(Vertex* initPoint);
    float costInfill();
    bool inTemporalWindow();
    void updateTemporalWindow();
    std::vector<Vertex> randomPointGen(Vertex point, float radius = 3, int numPoints = 50);
    Vertex centroidShifting(Vertex* vertex);

    glm::vec3 calculateGcodeCentroid(const std::string &gcodeFilePath,GcodeBounds& bounds);

    std::vector<GcodePoint> filterOutliers(const std::vector<GcodePoint> &points);

    glm::vec3
    transformGcodePointToMesh(const glm::vec3 &gcodePoint);
};


#endif //NONPLANAR_VOLUMENAVIGATION_H
