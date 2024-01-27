//
// Created by Simarpal Kalsi on 2024-01-26.
//

#ifndef SCULPTPATH_GLOBULARRESULT_H
#define SCULPTPATH_GLOBULARRESULT_H

#include <CGAL/Simple_cartesian.h>

class GlobularResult {
public:
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Ray_3 Ray_3;
    typedef Kernel::Point_3 Point_3;

    Point_3 originPoint;
    Ray_3 ray;
    Point_3 intersectionPoint;

    GlobularResult(const Point_3& origin, const Ray_3& r, const Point_3& intersection)
            : originPoint(origin), ray(r), intersectionPoint(intersection) {
    }
};


#endif //SCULPTPATH_GLOBULARRESULT_H
