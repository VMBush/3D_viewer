#ifndef MAIN_CODE_H
#define MAIN_CODE_H

#include <stdlib.h>


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
void centralization (work_struct *All);
// первоначальное уменьшение объкта до размера виджета
void normalization (work_struct *All);
float ** mult_matrix(float **move_matrix, float **coord);

#endif
