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

    initMesh();

    // Create a Side_of_triangle_mesh object
    CGAL::Side_of_triangle_mesh<Mesh, K> inside_tester(tree);

    //Call inside mesh using [inside_tester(point) == CGAL::ON_BOUNDED_SIDE] return value proves exist in volume

    bool done = false;
    while (!done){
        std::vector<Intersect::Point_3> points;
        Intersect intersectPoints(filePath);
        points = intersectPoints.gridIntersect(10,0.5);
        Intersect::Point_3 arbitraryPoint(0, 0, 0);
        intersectPoints.globularIntersectionAtPoint(arbitraryPoint,1.0,load);
        intersectPoints.planarIntersect(1.0);
        // Call the isPointInMesh method with the arbitrary point
        bool isInside = intersectPoints.isPointInMesh(arbitraryPoint, mesh);

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

//Creates the inital point from where volnag takes place
void VolumeIterator::initVolumeTraversal() {
    //Create an arbitrary point in and check if it is in the mesh and then shift if so that a function gets minimized
    //function will shift it to boundary of mesh
    std::cout << "Starting volume traversal" << std::endl;
    Intersect::Point_3 originPoint(0, 0, 0);
    CGAL::Side_of_triangle_mesh<Mesh, K> inside_tester(tree);
    // Check if the point is inside the mesh
    bool isPointIn = inside_tester(originPoint) == CGAL::ON_BOUNDED_SIDE;
    if (isPointIn) {
        std::cout << "The point is inside the mesh." << std::endl;
    } else {
        std::cout << "The point is not inside the mesh. and there is no logic to move it inside" << std::endl;
        
    }
    //If the point is inside the mesh we can continue with the logic to move it to the boundary of the mesh close to the bottom
    //Start from origin point and move down towards the bottom of the mesh and offset of the bottom point

    Intersect intersect(filePath);
    //This should be the bottom point of the mesh
    Point_3 bottomPoint = intersect.rayIntersect(Ray_3(originPoint, Vector_3(0, 0, 0)), one_point)[0];
    std::cout << "Bottom Point: (" << bottomPoint.x() << ", " << bottomPoint.y() << ", " << bottomPoint.z() << ")" << std::endl;

    
    //Take this bottom point and create ray intersection tests to see where the edge is.
    std::cout << "TFLAG" << std::endl;
std::vector<Point_3> bottomPoints;
// Create a for loop to sweep 360 degrees across the bottom of the mesh
for (int angle = 0; angle < 360; angle++) {
    // Calculate the direction vector for the ray based on the current angle
    double radian = angle * M_PI / 180.0;
    double dx = cos(radian);
    double dy = sin(radian);
    Point_3 direction(dx, dy, 0);

    // Create a ray originating from the bottom point in the current direction
    Ray_3 ray(bottomPoint, direction);

    // Perform ray intersection test with the mesh
    std::vector<Point_3> intersectionPoints = intersect.rayIntersect(ray, one_point);

    // Find the point at the edge of the mesh
    Point_3 edgePoint;
    for (const Point_3& point : intersectionPoints) {
        if (inside_tester(point) == CGAL::ON_UNBOUNDED_SIDE) {
            std::cout << "Edge Point: (" << edgePoint.x() << ", " << edgePoint.y() << ", " << edgePoint.z() << ")" << std::endl;
            edgePoint = point;
            bottomPoints.push_back(edgePoint);
            break;
        }
    }
}

}

/**
 * Inits the volume for the mesh and creates the AABB tree
 */
void VolumeIterator::initMesh() {
    MeshLoad loading(filePath);
    load = loading;
    load.loadMesh();
    mesh = load.getMesh();

    // Build an AABB tree for the mesh
    tree = Tree(faces(mesh).first, faces(mesh).second, mesh);
}

