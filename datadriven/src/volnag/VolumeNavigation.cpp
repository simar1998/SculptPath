//
// Created by Simarpal Kalsi on 2024-02-17.
//

#include <iostream>
#include "VolumeNavigation.h"
#include "GlobularCast.h"
#include "../Intersect.h"
#include <random>
#include "PlanarDispertionRayCast.h"
#include "json.hpp"
#include <fstream>
#include <string>
#include <regex>

/**
 * SCALING AND VECTOR SHIFTING PROBLEMS ARE DIFFERENT
 */
/**
 * This method starts the volume navigation process
 * @param mesh
 */

using json = nlohmann::json; // Alias for easy use


void VolumeNavigation::startVolNav() {


    //Need logic to find point inside mesh to begin volnag process
    Vertex init = initPoint();
    Vertex shifted = centroidShifting(&init);



    std::vector<Vertex> intersectedPoints = globularRayIntersect(mesh, initPoint());
    std::cout << "Intersected Points: " << intersectedPoints.size() << std::endl;
        for (Vertex point: intersectedPoints) {
            //std::cout << "Intersected Point: " << point.position.x << " " << point.position.y << " " << point.position.z
               //       << std::endl;
        }

        std::vector<Vertex> points = randomPointGen(shifted);

}


Vertex VolumeNavigation::initPoint() {
    std::vector<float> boundingVals = intersect.getBoundingVals();

    // Calculate centroid
    glm::vec3 centroid(
            (boundingVals[0] + boundingVals[3]) / 2.0f,  // x
            (boundingVals[1] + boundingVals[4]) / 2.0f,  // y
            (boundingVals[2] + boundingVals[5]) / 2.0f   // z
    );

    // Create centroid vertex
    Vertex centroidVertex = Vertex(centroid);

    std::cout << "Centroid: " << centroidVertex.position.x << " " << centroidVertex.position.y << " " << centroidVertex.position.z << std::endl;


    std::cout << "Is centroid in mesh " << intersect.isPointInMesh(centroidVertex) << std::endl;
    return centroidVertex;
}

Vertex VolumeNavigation::nextPoint() {
    return Vertex();
}

/**
 * This method checks if  volume navigation process is finished using cost function
 * @float
 */
float VolumeNavigation::volnavFinished() {
    return false;
}

/**
 * This method calculates the cost of a set of points and if they are perimeter values
 * @return
 */
float VolumeNavigation::costPerimeter() {
    return 0;
}

float VolumeNavigation::costInfill() {
    return 0;
}

bool VolumeNavigation::inTemporalWindow() {
    return false;
}

/**
 * This method updates the temporal window
 */
void VolumeNavigation::updateTemporalWindow() {

}

/**
 * Method uses stochastic process to mimic brownian motion to generate points in a radius
 * @param point
 * @param radius
 * @param numPoints
 * @return
 */
std::vector<Vertex> VolumeNavigation::randomPointGen(Vertex point, float radius, int numPoints) {
    std::vector<Vertex> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, radius); // mean is 0 and standard deviation is radius

    for(int i = 0; i < numPoints; ++i) {
        // use normal distribution in each direction to generate random offsets in each direction
        float dx = dis(gen);
        float dy = dis(gen);
        float dz = dis(gen);

        // new point cords
        float newX = point.position.x + dx;
        float newY = point.position.y + dy;
        float newZ = point.position.z + dz;

        // add to list if point passes checks
        float distance = std::sqrt(dx*dx + dy*dy + dz*dz);
        if(distance <= radius) {
            //TODO check if the point is in the mesh before appending it to the return value
            if (intersect.isPointInMesh(Vertex(newX, newY, newZ))) {
                points.push_back(Vertex(newX, newY, newZ));
            }
        } else {
            // decrement if checks fail to redo loop
            --i;
        }
    }

    return points;
}

VolumeNavigation::VolumeNavigation(const Mesh &mesh, const Settings &settings) : mesh(mesh), settings(settings) {
    intersect = Intersect(mesh.getTriangles());
}

/**
 * Shifts centroid down and creates ray intersect at bottom of mesh
 * @param vertex
 * @return
 */
Vertex VolumeNavigation::centroidShifting(Vertex *vertex) {
    //Assume centroid valid and shift to bottom of mesh using circular ray shift
    //The indexes that are in hte point list contain candidate init points
    const float OFFSET = 0.1;
    const int NUM_POINTS = 1; //DEFAULT shoiuld be 100 but I put 1 to make faster atm
    std::vector<Vertex> downShoot = intersect.rayIntersect(Ray(vertex->position,Vertex(0.0f,0.0f,-1.0f).position), intersectionAlgorithm::MOLLER_TROMBORE);
    std::vector<Vertex> pointList;
    if (!downShoot.empty()){
        std::cout << "Down shoot has hit the bottom of the mesh" << std::endl;
        //apply offset before setting of planar dispertion ray cast
        Vertex offseted = Vertex (vertex->position.x,vertex->position.y,vertex->position.z + OFFSET);
        pointList =  PlanarDispertionRayCast::init(mesh,offseted,NUM_POINTS);
        std::cout <<"Bottom entry point candidates " << pointList.size() << std::endl;
    }

    //Just returning first index for now, TODO add logic for determining best point
    return pointList[0];
}

/**
 * Code to calculate the bottom of the mesh
 * @param initPoint
 * @return
 */
std::vector<Vertex> VolumeNavigation::initBottom(Vertex* initPoint){
    return PlanarDispertionRayCast::init(mesh, *initPoint, 100);
}

VolumeNavigation::VolumeNavigation(std::string meshFile, std::string gcodeFile, std::string outputLoc) {
    mesh = Mesh(meshFile);
    std::cout<< "Mesh loaded" << std::endl;
    intersect = Intersect(mesh.getTriangles());
    std::cout<< "Triangles num: " << mesh.getTriangles().size() << std::endl;
    std::ifstream inputFile(gcodeFile);
    std::ofstream outputFile(outputLoc);
    std::string line;
    float currentZ = 0.0f;
    // Regex to capture lines with X, Y, and optionally Z and E values
    std::regex extrusionRegex(R"(G1\s+.*X([-\d.]+)\s+Y([-\d.]+)(?:\s+Z([-\d.]+))?.*\s+E([-\d.]+))");
    // Additional regex to capture Z value updates
    std::regex zUpdateRegex(R"(G1\s+.*Z([-\d.]+))");
    std::smatch matches;
    json outputJson = json::array();

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Failed to open input or output file." << std::endl;
        return;
    }

    glm::vec3 prevPoint(0.0f, 0.0f, 0.0f);
    meshCentroid = initPoint();
    bool isFirstPoint = true;
    GcodeBounds bounds{};
    Vertex gcodeCentre = Vertex(calculateGcodeCentroid(gcodeFile, bounds));
    std::cout << "Gcode Bounds: " << bounds.min.x << " " << bounds.min.y << " " << bounds.min.z << " - "
              << bounds.max.x << " " << bounds.max.y << " " << bounds.max.z << "\n";
    std::cout << "G-code centroid: " << gcodeCentre.position.x << " " << gcodeCentre.position.y << " " << gcodeCentre.position.z << std::endl;

    while (getline(inputFile, line)) {
        // Check for Z value updates in any G1 command
        if (std::regex_search(line, matches, zUpdateRegex) && matches.size() > 1) {
            currentZ = std::stof(matches[1].str());
        }

        // Then check for full extrusion commands with X, Y, Z, and E
        if (std::regex_search(line, matches, extrusionRegex) && matches.size() == 5) {
            float x = std::stof(matches[1]);
            float y = std::stof(matches[2]);
            float e = std::stof(matches[4]); // Extrusion value, not always needed depending on your processing

            glm::vec3 currentPoint(x, y, currentZ);
            currentPoint = transformGcodePointToMesh(currentPoint);

            if (!isFirstPoint) {
                std::vector<Vertex> intersectedPoints = globularRayIntersect(mesh, Vertex(prevPoint));
                //std::cout << "Point being tested: " << prevPoint.x << " " << prevPoint.y << " " << prevPoint.z << "\n";
                //std::cout << "Is point in mesh" << intersect.isPointInMesh(Vertex(prevPoint)) << std::endl;
               // std::cout << "Intersected Points: " << intersectedPoints.size() << std::endl;

                json pointJson = {
                        {"current_point", {prevPoint.x, prevPoint.y, prevPoint.z}},
                        {"next_point", {currentPoint.x, currentPoint.y, currentPoint.z}},
                        {"mesh_features", json::array()}
                };

                for (const auto& point : intersectedPoints) {
                    //std::cout<< "Intersected Point: " << point.position.x << " " << point.position.y << " " << point.position.z << std::endl;
                    pointJson["mesh_features"].push_back({
                                                                 {"intersection_point", {point.position.x, point.position.y, point.position.z}},
                                                                 {"distance_to_intersection", getDistance(Vertex{prevPoint}, point)} // Assuming a suitable getDistance function
                                                         });
                }

                outputJson.push_back(pointJson);
            } else {
                isFirstPoint = false;
            }

            prevPoint = currentPoint; // Update previous point for the next iteration
        }
    }

    outputFile << outputJson.dump(4); // Write formatted JSON to file

    inputFile.close();
    outputFile.close();
}

/**
 * Helper function to calculate IQR and filter points
 * @param points
 * @return
 */
std::vector<VolumeNavigation::GcodePoint> VolumeNavigation::filterOutliers(const std::vector<GcodePoint>& points) {
    if (points.empty()) {
        return {};
    }

    // Helper lambda to calculate IQR and return lower and upper bounds for filtering
    auto calculateIQRBounds = [](const std::vector<float>& sortedValues) -> std::pair<float, float> {
        size_t n = sortedValues.size();
        float q1 = sortedValues[n / 4]; // First quartile
        float q3 = sortedValues[3 * n / 4]; // Third quartile
        float iqr = q3 - q1;
        return {q1 - 1.5f * iqr, q3 + 1.5f * iqr};
    };

    // Extract and sort X, Y, Z values separately
    std::vector<float> xValues(points.size()), yValues(points.size()), zValues(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        xValues[i] = points[i].x;
        yValues[i] = points[i].y;
        zValues[i] = points[i].z;
    }
    std::sort(xValues.begin(), xValues.end());
    std::sort(yValues.begin(), yValues.end());
    std::sort(zValues.begin(), zValues.end());

    // Calculate IQR bounds for X, Y, Z
    auto [xLower, xUpper] = calculateIQRBounds(xValues);
    auto [yLower, yUpper] = calculateIQRBounds(yValues);
    auto [zLower, zUpper] = calculateIQRBounds(zValues);

    // Filter points based on calculated IQR bounds
    std::vector<GcodePoint> filteredPoints;
    for (const auto& point : points) {
        if (point.x >= xLower && point.x <= xUpper &&
            point.y >= yLower && point.y <= yUpper &&
            point.z >= zLower && point.z <= zUpper) {
            filteredPoints.push_back(point);
        }
    }

    return filteredPoints;
}

/**
 * Helper function to calculate the centroid of a G-code file
 * @param gcodeFilePath
 * @param bounds
 * @return
 */
glm::vec3 VolumeNavigation::calculateGcodeCentroid(const std::string& gcodeFilePath, GcodeBounds& bounds) {
    std::ifstream inputFile(gcodeFilePath);
    std::string line;
    std::vector<GcodePoint> points;
    std::regex extrusionRegex(R"(G1\s+.*X([-\d.]+)\s+Y([-\d.]+)(?:\s+Z([-\d.]+))?.*\s+E([-\d.]+))");
    std::regex zUpdateRegex(R"(G1\s+.*Z([-\d.]+))");
    std::smatch matches;
    float currentZ = 0.0f;

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open G-code file: " << gcodeFilePath << "\n";
        return glm::vec3(0.0f); // Return a default vector in case of failure
    }

    while (getline(inputFile, line)) {
        if (std::regex_search(line, matches, zUpdateRegex) && matches.size() > 1) {
            currentZ = std::stof(matches[1].str());
        }

        if (std::regex_search(line, matches, extrusionRegex) && matches.size() == 5) {
            GcodePoint point = {std::stof(matches[1].str()), std::stof(matches[2].str()), currentZ};
            points.push_back(point);
        }
    }

    inputFile.close();

    // Filter outliers
    std::vector<GcodePoint> filteredPoints = filterOutliers(points);

    // Calculate bounds and centroid from filtered points
    float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
    bounds.min = glm::vec3(std::numeric_limits<float>::max());
    bounds.max = glm::vec3(std::numeric_limits<float>::lowest());
    for (const auto& point : filteredPoints) {
        bounds.min.x = std::min(bounds.min.x, point.x);
        bounds.min.y = std::min(bounds.min.y, point.y);
        bounds.min.z = std::min(bounds.min.z, point.z);
        bounds.max.x = std::max(bounds.max.x, point.x);
        bounds.max.y = std::max(bounds.max.y, point.y);
        bounds.max.z = std::max(bounds.max.z, point.z);

        sumX += point.x;
        sumY += point.y;
        sumZ += point.z;
    }

    if (!filteredPoints.empty()) {
        return glm::vec3(sumX / filteredPoints.size(), sumY / filteredPoints.size(), sumZ / filteredPoints.size());
    } else {
        return glm::vec3(0.0f); // Return a default vector if no points were found
    }
}

glm::vec3 VolumeNavigation::transformGcodePointToMesh(const glm::vec3& gcodePoint) {
    // Fetch mesh bounds using getBoundingVals
    std::vector<float> meshBoundingVals = intersect.getBoundingVals();

    GcodeBounds meshBounds{};
    meshBounds.min = glm::vec3(meshBoundingVals[0], meshBoundingVals[1], meshBoundingVals[2]);
    meshBounds.max = glm::vec3(meshBoundingVals[3], meshBoundingVals[4], meshBoundingVals[5]);


    glm::vec3 scaleFactors(
            (meshBounds.max.x - meshBounds.min.x) / (gcodeBounds.max.x - gcodeBounds.min.x),
            (meshBounds.max.y - meshBounds.min.y) / (gcodeBounds.max.y - gcodeBounds.min.y),
            (meshBounds.max.z - meshBounds.min.z) / (gcodeBounds.max.z - gcodeBounds.min.z)
    );


    glm::vec3 translation = meshCentroid.position - gcodeCentroid;

    glm::vec3 scaledPoint = glm::vec3(
            (gcodePoint.x - gcodeCentroid.x) * scaleFactors.x + gcodeCentroid.x,
            (gcodePoint.y - gcodeCentroid.y) * scaleFactors.y + gcodeCentroid.y,
            (gcodePoint.z - gcodeCentroid.z) * scaleFactors.z + gcodeCentroid.z
    );


    glm::vec3 transformedPoint = scaledPoint + translation;


    return transformedPoint;
}