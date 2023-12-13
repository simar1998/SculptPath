//
// Created by simar on 12/10/2023.
//

#include <CGAL/Side_of_triangle_mesh.h>
#include "VolumeIterator.h"
#include "../../mesh_loader/MeshLoad.h"
#include "../Intersect.h"

std::string VolumeIterator::startIteratorOperations() {

    //TODO create the code for the volume iterator process

    //Load mesh from using meshloader

    MeshLoad load(filePath);

    load.loadMesh();
    mesh = load.getMesh();

    //Now we perform some mesh analyzing techniques to get ray intersect values

    // Build an AABB tree for the mesh
    Tree tree(faces(mesh).first, faces(mesh).second, mesh);

    // Create a Side_of_triangle_mesh object
    CGAL::Side_of_triangle_mesh<Mesh, K> inside_tester(tree);

    //Call inside mesh using [inside_tester(point) == CGAL::ON_BOUNDED_SIDE] return value proves exist in volume

    bool done = false;
    while (!done){
        std::vector<Intersect::Point_3> points;
        Intersect intersectPoints(filePath);
        points = intersectPoints.gridIntersect(10,0.5);
        Intersect::Point_3 arbitraryPoint(0, 0, 0);
        // Call the isPointInMesh method with the arbitrary point
        bool isInside = intersectPoints.isPointInMesh(arbitraryPoint);

        // Output the result
        if (isInside) {
            std::cout << "The point is inside the mesh." << std::endl;
        } else {
            std::cout << "The point is not inside the mesh." << std::endl;
        }

        //Perform in volume mesh traversal

        //go through intsersect points and apply z shift and go through each point to check if its in mesh
        std::vector<Intersect::Point_3> shiftedPoints;
        for(Intersect::Point_3 point : points){
            shiftedPoints.emplace_back(point.x(),point.y(),point.z()-0.1);
        }

        int insideCounter, outsideCounter = 0;
        for(Intersect::Point_3 point : shiftedPoints){
            if (inside_tester(point) == CGAL::ON_BOUNDED_SIDE){
                insideCounter++;
            }
            else{
                outsideCounter++;
            }
        }
        std::cout << "Inside count:" << insideCounter << " Outside count:" << outsideCounter << std::endl;
        done = true;
    }


    //TODO return gcode filepath
    return std::string();
}

std::vector<VolumeIterator::Point_3> VolumeIterator::createCandidatePoints(std::vector<Point_3> intersect) {
    return std::vector<Point_3>();
}

//TODO create traversal logic for in
void VolumeIterator::initVolumeTraversal() {

}

