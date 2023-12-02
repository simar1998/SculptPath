//
// Created by simar on 11/30/2023.
//
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Monge_via_jet_fitting.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "MeshSurfaceEstimation.h"

typedef double DFT;
typedef CGAL::Simple_cartesian<DFT> Data_Kernel;
typedef Data_Kernel::Point_3 DPoint;
typedef CGAL::Monge_via_jet_fitting<Data_Kernel> My_Monge_via_jet_fitting;
typedef My_Monge_via_jet_fitting::Monge_form My_Monge_form;

//Default constructor
MeshSurfaceEstimation::MeshSurfaceEstimation(const std::string &filePath) {
this->filePath = filePath;
}

//Performing point cloud estimation
void MeshSurfaceEstimation::performEstimationPointCloud() {
    std::ifstream inFile(this->filePath);
    if (!inFile) {
        std::cerr << "Cannot open OFF file for input\n";
        exit(-1);
    }

    std::string line;
    // Skip the first line containing "OFF"
    std::getline(inFile, line);

    size_t numVertices, numFaces, numEdges;
    // Read the number of vertices, faces, and edges
    inFile >> numVertices >> numFaces >> numEdges;
    std::vector<DPoint> in_points;

    // Read vertices
    double x, y, z;
    for (size_t i = 0; i < numVertices; ++i) {
        std::cout << "XYZ" << x << "," << y << "," << z << std::endl;
        inFile >> x >> y >> z;
        DPoint p(x, y, z);
        in_points.push_back(p);
    }

    inFile.close();

    // CGAL Monge via jet fitting
    size_t d_fitting = 4; // example value, adjust as necessary
    size_t d_monge = 4;   // example value, adjust as necessary
    My_Monge_form monge_form;
    My_Monge_via_jet_fitting monge_fit;
    monge_form = monge_fit(in_points.begin(), in_points.end(), d_fitting, d_monge);

    // Output results
    CGAL::IO::set_ascii_mode(std::cout);
    std::cout << "vertex : " << in_points[0] << std::endl
              << "number of points used : " << in_points.size() << std::endl
              << monge_form;
    std::cout  << "condition_number : " << monge_fit.condition_number() << std::endl
               << "pca_eigen_vals and associated pca_eigen_vecs :"  << std::endl;
    for (int i = 0; i < 3; i++)
        std::cout << monge_fit.pca_basis(i).first << std::endl
                  << monge_fit.pca_basis(i).second  << std::endl;
}
