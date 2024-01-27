//
// Created by simar on 11/14/2023.
//

#include "Slicer.h"
#include <boost/optional.hpp>
#include "Slicer.h"
#include "volume_iterator/VolumeIterator.h"

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

    std::string offFilePath = "C:\\Code\\SculptPath\\assets\\test_mp_2.off";
    std::string objFilePath = "/Users/simar/SculptPath/assets/test_mp_2.obj";
   // MeshTriangulation triangulator(objFilePath);
    //triangulator.iterateVolume();

   // MeshLabeling label(objFilePath);
    //label.performSegmentation();
    //label.computeSDF();

    //Segmentation segmentation(offFilePath);
    //segmentation.performSegSDF();

    //MeshSurfaceEstimation surfaceEstimation(offFilePath);

    //surfaceEstimation.performEstimationPointCloud();

    //Intersect intersect(objFilePath);
    //intersect.gridIntersect(10,0.5);
   // intersect.gridIntersectRefined(10,0.1,0.005);

    VolumeIterator iterator(objFilePath);
    iterator.startIteratorOperations();

}
