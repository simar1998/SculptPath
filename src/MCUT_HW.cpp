//
// Created by simar on 11/1/2023.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "MCUT_HW.h"

using namespace std;


void writeOFF(
        const char* fpath,
        float* pVertices,
        uint32_t* pFaceIndices,
        uint32_t* pFaceSizes,
        uint32_t numVertices,
        uint32_t numFaces);

void MCUT_HW::mcut_hw() {

    //Source Mesh
    float cubeVertices[] = {
            -5, -5, 5,  // 0
            5, -5, 5,   // 1
            5, 5, 5,    //2
            -5, 5, 5,   //3
            -5, -5, -5, //4
            5, -5, -5,  //5
            5, 5, -5,   //6
            -5, 5, -5   //7
    };
    uint32_t cubeFaces[] = {
            0, 1, 2, 3, //0
            7, 6, 5, 4, //1
            1, 5, 6, 2, //2
            0, 3, 7, 4, //3
            3, 2, 6, 7, //4
            4, 5, 1, 0  //5
    };
    uint32_t cubeFaceSizes[] = {
            4, 4, 4, 4, 4, 4};
    uint32_t numCubeVertices = 8;
    uint32_t numCubeFaces = 6;

    //Cut mesh

    float cutMeshVertices[] = {
            -20, -4, 0, //0
            0, 20, 20,  //1
            20, -4, 0,  //2
            0, 20, -20  //3
    };
    uint32_t cutMeshFaces[] = {
            0, 1, 2, //0
            0, 2, 3  //1
    };
    //uint32_t cutMeshFaceSizes[] = {
    //    3, 3};
    uint32_t numCutMeshVertices = 4;
    uint32_t numCutMeshFaces = 2;

    McContext context = MC_NULL_HANDLE;
    McResult err = mcCreateContext(&context, MC_NULL_HANDLE);

    if (err != MC_NO_ERROR) {
        fprintf(stderr, "could not create context (err=%d)\n", (int)err);
        exit(1);
    }

    err = mcDispatch(
            context,
            MC_DISPATCH_VERTEX_ARRAY_DOUBLE,
            cubeVertices,
            cubeFaces,
            cubeFaceSizes,
            numCubeVertices,
            numCubeFaces,
            cutMeshVertices,
            cutMeshFaces,
            nullptr, // cutMeshFaceSizes, // no need to give 'faceSizes' parameter since cut-mesh is a triangle mesh
            numCutMeshVertices,
            numCutMeshFaces);


    if (err != MC_NO_ERROR) {
        fprintf(stderr, "dispatch call failed (err=%d)\n", (int)err);
        exit(1);
    }

    //Querry number of components that are available  of all types

    //TODO


    cout << "TESTING" << std::endl;


}
