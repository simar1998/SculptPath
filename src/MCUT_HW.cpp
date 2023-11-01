//
// Created by simar on 11/1/2023.
//

#include "MCUT_HW.h"
#include "mcut/mcut.h"
void MCUT_HW::mcut_hw() {

    //Source mesh

    float cubeVertices[] = {
            -5, -5, 5, // 0
            5, -5, 5, // 1
            5, 5, 5, //2
            -5, 5, 5, //3
            -5, -5, -5, //4
            5, -5, -5, //5
            5, 5, -5, //6
            -5, 5, -5 //7
    };
    uint32_t cubeFaces[] = {
            0, 1, 2, 3, //0
            7, 6, 5, 4, //1
            1, 5, 6, 2, //2
            0, 3, 7, 4, //3
            3, 2, 6, 7, //4
            4, 5, 1, 0 //5
    };
    uint32_t cubeFaceSizes[] = {
            4, 4, 4, 4, 4, 4
    };
    uint32_t numCubeVertices = 8;
    uint32_t numCubeFaces = 6;

    //CUT Mesh

    float cutMeshVertices[] = {
            -20, -4, 0, //0
            0, 20, 20, //1
            20, -4, 0, //2
            0, 20, -20 //3
    };
    uint32_t cutMeshFaces[] = {
            0, 1, 2, //0
            0, 2, 3 //1
    };
    uint32_t cutMeshFaceSizes[] = {
            3, 3
    };
    uint32_t numCutMeshVertices = 4;
    uint32_t numCutMeshFaces = 2;

    //Creating context

    McContext context = MC_NULL_HANDLE;
    mcCreateContext(&context, MC_NULL_HANDLE);

    //Dispacthing call

    mcDispatch(
            context,
            MC_DISPATCH_VERTEX_ARRAY_FLOAT,
            cubeVertices,
            cubeFaces,
            cubeFaceSizes,
            numCubeVertices,
            numCubeFaces,
            cutMeshVertices,
            cutMeshFaces,
            cutMeshFaceSizes,
            numCutMeshVertices,
            numCutMeshFaces);



}
