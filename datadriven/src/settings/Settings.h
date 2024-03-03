//
// Created by Simarpal Kalsi on 2024-02-20.
//

#ifndef NONPLANAR_SETTINGS_H
#define NONPLANAR_SETTINGS_H

#include <string>

class Settings {

    double layerHeight;
    double printSpeed;
    double extruderTemperature;
    double bedTemperature;
    int infillPercentage;
    std::string infillPattern;
    double retractionDistance;
    double retractionSpeed;
    int printCoolingFanSpeed;
    bool supportStructures;
    double supportOverhangAngle;
    int supportDensity;
    std::string buildPlateAdhesionType;
    double flowRate;
    double nozzleDiameter;
    double wallThickness;
    double topBottomThickness;
    bool zHopWhenRetracted;
    double initialLayerHeight;
    double initialLayerSpeed;
    double initialLayerFlow;
    double printAcceleration;
    double travelAcceleration;
    double printJerk;
    double travelJerk;
    bool ironing;
    std::string seamPosition;
    double outerWallWipeDistance;
    double minimumLayerTime;
    std::string coolingThresholds;
    bool outerBeforeInnerWalls;
    double minimumTravelForRetraction;
    int skirtBrimLineCount;
    double skirtBrimDistanceFromObject;
    double raftAirGap;
    int raftTopLayers;
    double raftBaseThickness;
    double raftBaseSpeed;
    double filamentDiameter;
    double filamentDensity;
    double filamentSpecificHeatCapacity;
    double filamentFlowTemperature;
    std::string bedLevelingPattern;
    bool spiralizeOuterContour;
    std::string postProcessingScripts;
    std::string topBottomPattern;
    std::string bridgeSettings;
    bool coasting;
    std::string layerStartPoints;
    std::string combingMode;

    std::string settingsFile;
public:
    Settings(const std::string &settingsFile);

    double getLayerHeight() const;

    double getPrintSpeed() const;

    double getExtruderTemperature() const;

    double getBedTemperature() const;

    int getInfillPercentage() const;

    const std::string &getInfillPattern() const;

    double getRetractionDistance() const;

    double getRetractionSpeed() const;

    int getPrintCoolingFanSpeed() const;

    bool isSupportStructures() const;

    double getSupportOverhangAngle() const;

    int getSupportDensity() const;

    const std::string &getBuildPlateAdhesionType() const;

    double getFlowRate() const;

    double getNozzleDiameter() const;

    double getWallThickness() const;

    double getTopBottomThickness() const;

    bool isZHopWhenRetracted() const;

    double getInitialLayerHeight() const;

    double getInitialLayerSpeed() const;

    double getInitialLayerFlow() const;

    double getPrintAcceleration() const;

    double getTravelAcceleration() const;

    double getPrintJerk() const;

    double getTravelJerk() const;

    bool isIroning() const;

    const std::string &getSeamPosition() const;

    double getOuterWallWipeDistance() const;

    double getMinimumLayerTime() const;

    const std::string &getCoolingThresholds() const;

    bool isOuterBeforeInnerWalls() const;

    double getMinimumTravelForRetraction() const;

    int getSkirtBrimLineCount() const;

    double getSkirtBrimDistanceFromObject() const;

    double getRaftAirGap() const;

    int getRaftTopLayers() const;

    double getRaftBaseThickness() const;

    double getRaftBaseSpeed() const;

    double getFilamentDiameter() const;

    double getFilamentDensity() const;

    double getFilamentSpecificHeatCapacity() const;

    double getFilamentFlowTemperature() const;

    const std::string &getBedLevelingPattern() const;

    bool isSpiralizeOuterContour() const;

    const std::string &getPostProcessingScripts() const;

    const std::string &getTopBottomPattern() const;

    const std::string &getBridgeSettings() const;

    bool isCoasting() const;

    const std::string &getLayerStartPoints() const;

    const std::string &getCombingMode() const;

    Settings();
};


#endif //NONPLANAR_SETTINGS_H
