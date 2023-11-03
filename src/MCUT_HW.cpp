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


}
