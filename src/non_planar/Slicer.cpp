//
// Created by simar on 11/14/2023.
//

#include "Slicer.h"
#include "../mesh_loader/MeshLoad.h"
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include "MeshBoolean.h"
#include "volume_navigation/MeshTriangulation.h"
//#include "volume_labeling/MeshLabeling.h"
#include "volume_labeling/Segmentation.h"
#include "surface_labeling/MeshSurfaceEstimation.h"


//typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Ray_3 Ray_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;
typedef CGAL::AABB_face_graph_triangle_primitive<Mesh> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> AABB_mesh_traits;
typedef CGAL::AABB_tree<AABB_mesh_traits> Tree;

//Test Slice function
void Slicer::sliceFile(std::string filePath, Settings settings) {

    /**
    std::string filePath1 = R"(C:\Code\SculptPath\assets\Body1.obj)";
    MeshLoad load(filePath1);
    load.loadMesh();
    Mesh mesh1 = load.getMesh();//Gets the mesh to start ray intersection Test
    std::string filePath2 = R"(C:\Code\SculptPath\assets\cube.obj)";
    MeshLoad load2(filePath2);
    load2.loadMesh();
    Mesh mesh2 = load.getMesh();

    MeshBoolean meshBool(filePath1,filePath2);

    meshBool.meshUnion();
**/

    std::string objFilePath = "C:\\Code\\SculptPath\\assets\\test_mp_2.off";
   // MeshTriangulation triangulator(objFilePath);
    //triangulator.iterateVolume();

   // MeshLabeling label(objFilePath);
   // label.performSegmentation();
    //label.computeSDF();

    //Segmentation segmentation(objFilePath);
    //segmentation.performSegSDF();

    MeshSurfaceEstimation surfaceEstimation(objFilePath);

    surfaceEstimation.performEstimationPointCloud();

}
