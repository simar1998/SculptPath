//
// Created by Simarpal Kalsi on 2024-02-26.
//

#ifndef NONPLANAR_FACTORYGCODE_H
#define NONPLANAR_FACTORYGCODE_H


#include <string>

class FactoryGCODE {
    enum SLICER{
        ORCA,
        CURA,
        SLIC3R
    };

    explicit FactoryGCODE(SLICER slicer,const std::string& meshDir = "meshDir");
    FactoryGCODE(){};
    void startDataCollection (std::string meshFile, std::string gcodeFile, std::string outputLoc);

};


#endif //NONPLANAR_FACTORYGCODE_H
