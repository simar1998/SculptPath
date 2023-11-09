//
// Created by simar on 11/8/2023.
//

#ifndef SCULPTPATH_MESHLOAD_H
#define SCULPTPATH_MESHLOAD_H


#include <string>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>

enum FileType {STL, OBJ};
class MeshLoad {

    std::string filePath;

    explicit MeshLoad(std::string& filePath);

public:
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Point_3 Point;
    typedef CGAL::Surface_mesh<Point> Mesh;
    void loadMesh();

private:

    Mesh mesh;  // Declare the mesh variable
    FileType getMeshFormat(bool check);


};


#endif //SCULPTPATH_MESHLOAD_H
