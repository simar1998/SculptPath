//
// Created by simar on 11/15/2023.
//

#include "Settings.h"

Settings::Settings(double nozzleSize, double bedTemp, double extruderTemp, double maxLayerHeight, double minLayerHeight)
        : nozzleSize(nozzleSize), bedTemp(bedTemp), extruderTemp(extruderTemp), maxLayerHeight(maxLayerHeight),
          minLayerHeight(minLayerHeight) {}

Settings::Settings() {

}

double Settings::getNozzleSize() const {
    return nozzleSize;
}

void Settings::setNozzleSize(double nozzleSize) {
    Settings::nozzleSize = nozzleSize;
}

double Settings::getBedTemp() const {
    return bedTemp;
}

void Settings::setBedTemp(double bedTemp) {
    Settings::bedTemp = bedTemp;
}

double Settings::getExtruderTemp() const {
    return extruderTemp;
}

void Settings::setExtruderTemp(double extruderTemp) {
    Settings::extruderTemp = extruderTemp;
}

double Settings::getMaxLayerHeight() const {
    return maxLayerHeight;
}

void Settings::setMaxLayerHeight(double maxLayerHeight) {
    Settings::maxLayerHeight = maxLayerHeight;
}

double Settings::getMinLayerHeight() const {
    return minLayerHeight;
}

void Settings::setMinLayerHeight(double minLayerHeight) {
    Settings::minLayerHeight = minLayerHeight;
}
