//
// Created by Simarpal Kalsi on 2024-02-20.
//

#include "Settings.h"
#include <json.hpp>
#include <fstream>

double Settings::getLayerHeight() const {
    return layerHeight;
}

double Settings::getPrintSpeed() const {
    return printSpeed;
}

double Settings::getExtruderTemperature() const {
    return extruderTemperature;
}

double Settings::getBedTemperature() const {
    return bedTemperature;
}

int Settings::getInfillPercentage() const {
    return infillPercentage;
}

const std::string &Settings::getInfillPattern() const {
    return infillPattern;
}

double Settings::getRetractionDistance() const {
    return retractionDistance;
}

double Settings::getRetractionSpeed() const {
    return retractionSpeed;
}

int Settings::getPrintCoolingFanSpeed() const {
    return printCoolingFanSpeed;
}

bool Settings::isSupportStructures() const {
    return supportStructures;
}

double Settings::getSupportOverhangAngle() const {
    return supportOverhangAngle;
}

int Settings::getSupportDensity() const {
    return supportDensity;
}

const std::string &Settings::getBuildPlateAdhesionType() const {
    return buildPlateAdhesionType;
}

double Settings::getFlowRate() const {
    return flowRate;
}

double Settings::getNozzleDiameter() const {
    return nozzleDiameter;
}

double Settings::getWallThickness() const {
    return wallThickness;
}

double Settings::getTopBottomThickness() const {
    return topBottomThickness;
}

bool Settings::isZHopWhenRetracted() const {
    return zHopWhenRetracted;
}

double Settings::getInitialLayerHeight() const {
    return initialLayerHeight;
}

double Settings::getInitialLayerSpeed() const {
    return initialLayerSpeed;
}

double Settings::getInitialLayerFlow() const {
    return initialLayerFlow;
}

double Settings::getPrintAcceleration() const {
    return printAcceleration;
}

double Settings::getTravelAcceleration() const {
    return travelAcceleration;
}

double Settings::getPrintJerk() const {
    return printJerk;
}

double Settings::getTravelJerk() const {
    return travelJerk;
}

bool Settings::isIroning() const {
    return ironing;
}

const std::string &Settings::getSeamPosition() const {
    return seamPosition;
}

double Settings::getOuterWallWipeDistance() const {
    return outerWallWipeDistance;
}

double Settings::getMinimumLayerTime() const {
    return minimumLayerTime;
}

const std::string &Settings::getCoolingThresholds() const {
    return coolingThresholds;
}

bool Settings::isOuterBeforeInnerWalls() const {
    return outerBeforeInnerWalls;
}

double Settings::getMinimumTravelForRetraction() const {
    return minimumTravelForRetraction;
}

int Settings::getSkirtBrimLineCount() const {
    return skirtBrimLineCount;
}

double Settings::getSkirtBrimDistanceFromObject() const {
    return skirtBrimDistanceFromObject;
}

double Settings::getRaftAirGap() const {
    return raftAirGap;
}

int Settings::getRaftTopLayers() const {
    return raftTopLayers;
}

double Settings::getRaftBaseThickness() const {
    return raftBaseThickness;
}

double Settings::getRaftBaseSpeed() const {
    return raftBaseSpeed;
}

double Settings::getFilamentDiameter() const {
    return filamentDiameter;
}

double Settings::getFilamentDensity() const {
    return filamentDensity;
}

double Settings::getFilamentSpecificHeatCapacity() const {
    return filamentSpecificHeatCapacity;
}

double Settings::getFilamentFlowTemperature() const {
    return filamentFlowTemperature;
}

const std::string &Settings::getBedLevelingPattern() const {
    return bedLevelingPattern;
}

bool Settings::isSpiralizeOuterContour() const {
    return spiralizeOuterContour;
}

const std::string &Settings::getPostProcessingScripts() const {
    return postProcessingScripts;
}

const std::string &Settings::getTopBottomPattern() const {
    return topBottomPattern;
}

const std::string &Settings::getBridgeSettings() const {
    return bridgeSettings;
}

bool Settings::isCoasting() const {
    return coasting;
}

const std::string &Settings::getLayerStartPoints() const {
    return layerStartPoints;
}

const std::string &Settings::getCombingMode() const {
    return combingMode;
}

Settings::Settings() {}

Settings::Settings(const std::string &settingsFile) : settingsFile(settingsFile) {
    std::ifstream i(settingsFile);
    nlohmann::json j;
    i >> j;

    layerHeight = j["layerHeight"];
    printSpeed = j["printSpeed"];
    extruderTemperature = j["extruderTemperature"];
    bedTemperature = j["bedTemperature"];
    infillPercentage = j["infillPercentage"];
    infillPattern = j["infillPattern"];
    retractionDistance = j["retractionDistance"];
    retractionSpeed = j["retractionSpeed"];
    printCoolingFanSpeed = j["printCoolingFanSpeed"];
    supportStructures = j["supportStructures"];
    supportOverhangAngle = j["supportOverhangAngle"];
    supportDensity = j["supportDensity"];
    buildPlateAdhesionType = j["buildPlateAdhesionType"];
    flowRate = j["flowRate"];
    nozzleDiameter = j["nozzleDiameter"];
    wallThickness = j["wallThickness"];
    topBottomThickness = j["topBottomThickness"];
    zHopWhenRetracted = j["zHopWhenRetracted"];
    initialLayerHeight = j["initialLayerHeight"];
    initialLayerSpeed = j["initialLayerSpeed"];
    initialLayerFlow = j["initialLayerFlow"];
    printAcceleration = j["printAcceleration"];
    travelAcceleration = j["travelAcceleration"];
    printJerk = j["printJerk"];
    travelJerk = j["travelJerk"];
    ironing = j["ironing"];
    seamPosition = j["seamPosition"];
    outerWallWipeDistance = j["outerWallWipeDistance"];
    minimumLayerTime = j["minimumLayerTime"];
    coolingThresholds = j["coolingThresholds"];
    outerBeforeInnerWalls = j["outerBeforeInnerWalls"];
    minimumTravelForRetraction = j["minimumTravelForRetraction"];
    skirtBrimLineCount = j["skirtBrimLineCount"];
    skirtBrimDistanceFromObject = j["skirtBrimDistanceFromObject"];
    raftAirGap = j["raftAirGap"];
    raftTopLayers = j["raftTopLayers"];
    raftBaseThickness = j["raftBaseThickness"];
    raftBaseSpeed = j["raftBaseSpeed"];
    filamentDiameter = j["filamentDiameter"];
    filamentDensity = j["filamentDensity"];
    filamentSpecificHeatCapacity = j["filamentSpecificHeatCapacity"];
    filamentFlowTemperature = j["filamentFlowTemperature"];
    bedLevelingPattern = j["bedLevelingPattern"];
    spiralizeOuterContour = j["spiralizeOuterContour"];
    postProcessingScripts = j["postProcessingScripts"];
    topBottomPattern = j["topBottomPattern"];
    bridgeSettings = j["bridgeSettings"];
    coasting = j["coasting"];
    layerStartPoints = j["layerStartPoints"];
    combingMode = j["combingMode"];
}