//
// Created by simar on 11/30/2023.
//

#ifndef SCULPTPATH_MESHSURFACEESTIMATION_H
#define SCULPTPATH_MESHSURFACEESTIMATION_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Monge_via_jet_fitting.h>
#include <fstream>
#include <vector>
#include <string>

//This class will take the mesh and convert it to a point cloud to utilize the CGAL single points surface estimation
class MeshSurfaceEstimation {

    //Typedefs
    typedef double                   DFT;
    typedef CGAL::Simple_cartesian<DFT>     Data_Kernel;
    typedef Data_Kernel::Point_3     DPoint;
    typedef CGAL::Monge_via_jet_fitting<Data_Kernel> My_Monge_via_jet_fitting;
    typedef My_Monge_via_jet_fitting::Monge_form     My_Monge_form;

    std::string filePath;

public:

    explicit MeshSurfaceEstimation(const std::string& filePath);

    void performEstimationPointCloud();
};


#endif //SCULPTPATH_MESHSURFACEESTIMATION_H
