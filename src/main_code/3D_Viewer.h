#ifndef MAIN_CODE_H
#define MAIN_CODE_H

#include <stdlib.h>
#include <math.h>


typedef struct {
    int amount_coord;
    int amount_index;
    float *coord;
    int *index;
    float minMaxX[2];
    float minMaxY[2];
    float minMaxZ[2];
} work_struct;


//перемещение объекта относительно центра
float** centralization (work_struct *All);
float ** mult_matrix(float **matrix_1, float **matrix_2);

float **matrix_move (float *xyz);
float **matrix_turn_x(float corner);
float **matrix_turn_y(float corner);
float **matrix_turn_z(float corner);
float **matrix_scaling(float *xyz);
float **create_matrix(int rows, int columns);
void remove_matrix(float **A);

#endif
