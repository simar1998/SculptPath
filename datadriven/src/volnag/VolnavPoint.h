//
// Created by Simarpal Kalsi on 2024-02-20.
//

#ifndef NONPLANAR_VOLNAVPOINT_H
#define NONPLANAR_VOLNAVPOINT_H
#include "../Geometry.h"


enum POINT_CLASSIFICATION {
    PERIMETER,
    INFILL,
    BOTTOM,
    TOP
};

struct VolnavPoint {
    VolnavPoint(POINT_CLASSIFICATION classification, const glm::vec3 &position) : classification(classification),
                                                                                  position(position) {}
    VolnavPoint() = default;

    POINT_CLASSIFICATION classification;
    glm::vec3 position{};
};




#endif //NONPLANAR_VOLNAVPOINT_H
