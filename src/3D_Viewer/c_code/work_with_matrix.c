#include "cModules.h"

void create4mat(float arr[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        arr[i][i] = 1;
    }
}


void mult4matToRes(float m1[4][4], float m2[4][4], float res[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void mult4mat(float m1[4][4], float m2[4][4]) {
    float res[4][4];
    mult4matToRes(m1, m2, res);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m2[i][j] = res[i][j];
        }
    }
}

void offset4mat(float xyz[3], float mat[4][4]) {
    float offset[4][4];
    create4mat(offset);
    offset[0][3] = xyz[0];
    offset[1][3] = xyz[1];
    offset[2][3] = xyz[2];
    mult4mat(offset, mat);
}

void scale4mat(float scaleVal, float mat[4][4]) {
    float scale[4][4];
    create4mat(scale);
    scale[0][0] = scale[1][1] = scale[2][2] = scaleVal;
    mult4mat(scale, mat);
}

void rotate4mat(float xyz[3], float mat[4][4]) {
    float rotate[4][4];
    float x, y, z;
    x = xyz[0];
    y = xyz[1];
    z = xyz[2];
    rotate[0][0] = 1 - 2*y*y - 2*z*z;
    rotate[0][1] = 2*x*y - 2*z;
    rotate[0][2] = 2*x*z + 2*y;
    rotate[1][0] = 2*x*y + 2*z;
    rotate[1][1] = 1 - 2*x*x - 2*z*z;
    rotate[1][2] = 2*y*z - 2*x;
    rotate[2][0] = 2*x*z - 2*y;
    rotate[2][1] = 2*y*z + 2*x;
    rotate[2][2] = 1 - 2*x*x - 2*y*y;
    for (int i = 0; i < 3; i++) {
        rotate[3][i] = rotate[i][3] = 0;
    }
    rotate[3][3] = 0;
    mult4mat(rotate, mat);
}

// float** centralization (work_struct *All){
//     float centerX, centerY, centerZ;
//     centerX = All->minMaxX[0] + (All->minMaxX[1] - All->minMaxX[0])/2;
//     centerY = All->minMaxY[0] + (All->minMaxY[1] - All->minMaxY[0])/2;
//     centerZ = All->minMaxZ[0] + (All->minMaxZ[1] - All->minMaxZ[0])/2;
//     float move_center[4] = {-centerX, -centerY, -centerZ, 1};
//     float **move_matrix_center = matrix_move(move_center);
//     return move_matrix_center;
// }


