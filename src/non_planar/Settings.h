//
// Created by simar on 11/15/2023.
//

#ifndef SCULPTPATH_SETTINGS_H
#define SCULPTPATH_SETTINGS_H

#include <string>

class Settings {

public:
    Settings(double nozzleSize, double bedTemp, double extruderTemp, double maxLayerHeight, double minLayerHeight);
    Settings();
private:
    double nozzleSize;
    double bedTemp;
    double extruderTemp;
    double maxLayerHeight;
    double minLayerHeight;

public:

    double getNozzleSize() const;

    void setNozzleSize(double nozzleSize);

    double getBedTemp() const;

    void setBedTemp(double bedTemp);

    double getExtruderTemp() const;

    void setExtruderTemp(double extruderTemp);

    double getMaxLayerHeight() const;

    void setMaxLayerHeight(double maxLayerHeight);

    double getMinLayerHeight() const;

    void setMinLayerHeight(double minLayerHeight);
};


#endif //SCULPTPATH_SETTINGS_H
