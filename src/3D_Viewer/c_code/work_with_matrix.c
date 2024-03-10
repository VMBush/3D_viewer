#include "3D_Viewer.h"

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
            for (int k = 0; k < 4; k++) {
                res[i][j] = m1[i][k] * m2[k][j];
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

void offset4mat(float x, float y, float z, float mat[4][4]) {
    float res[4][4];
    create4mat(res);
    res[0][3] = x;
    res[1][3] = y;
    res[2][3] = z;

}

float** centralization (work_struct *All){
    float centerX, centerY, centerZ;
    centerX = All->minMaxX[0] + (All->minMaxX[1] - All->minMaxX[0])/2;
    centerY = All->minMaxY[0] + (All->minMaxY[1] - All->minMaxY[0])/2;
    centerZ = All->minMaxZ[0] + (All->minMaxZ[1] - All->minMaxZ[0])/2;
    float move_center[4] = {-centerX, -centerY, -centerZ, 1};
    float **move_matrix_center = matrix_move(move_center);
    return move_matrix_center;
}


float **matrix_move (float *xyz){
    float **res = create_matrix_4x4();
    res[0][0] = 1; res[0][3] = xyz[0];
    res[1][1] = 1; res[1][3] = xyz[1];
    res[2][2] = 1; res[2][3] = xyz[2];
    res[3][3] = 1;
    return res;
}

float **matrix_turn_x(float corner){
    float **res = create_matrix_4x4();
    res[0][0] = 1;
    res[1][1] = cos(corner); res[1][2] = sin(corner);
    res[2][1]= -sin(corner); res[2][2] = cos(corner);
    res[3][3] = 1;
    return res;
}

float **matrix_turn_y(float corner){
    float **res = create_matrix_4x4();
    res[0][0] = cos(corner); res[0][2] = -sin(corner);
    res[1][1] = 1;
    res[2][0] = sin(corner); res[2][2] = cos(corner);
    res[3][3] = 1;
    return res;
}

float **matrix_turn_z(float corner){
    float **res = create_matrix_4x4();
    res[0][0] = cos(corner); res[0][1] = sin(corner);
    res[1][0] = -sin(corner); res[1][1] = cos(corner);
    res[2][2] = 1;
    res[3][3] = 1;
    return res;
}

float **matrix_scaling(float *xyz){
    float **res = create_matrix_4x4();
    res[0][0] = xyz[0];
    res[1][1] = xyz[1];
    res[2][2] = xyz[2];
    res[3][3] = 1;
    return res;
}


float **create_matrix_4x4() {
    float **result;
    result = (float **)malloc(4 * sizeof(float *));
    for (int i = 0; i < 4; i++) {
      result[i] = malloc(4 * sizeof(float));
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result[i][j] = 0;
      }
    }
    return result;
}

void remove_matrix_4x4(float **A) {
  if (A != NULL) {
    for (int i = 0; i < 4; i++) {
      free(A[i]);
    }
    free(A);
   }
}


