#ifndef CMODULES_H
#define CMODULES_H

#include "vectors.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Object {
  vecVert vertices;
  vecInd indices;
};

#ifdef __cplusplus
extern "C" {
#endif

void create4mat(float arr[4][4]);
void mult4matToRes(float m1[4][4], float m2[4][4], float res[4][4]);
void mult4mat(float left[4][4], float res_right[4][4]);
void offset4mat(float xyz[3], float mat[4][4]);
void scale4mat(float scale, float mat[4][4]);
void rotate4mat(float xyz[4], float mat[4][4]);
void quanterionFromDmouse(float dpos[2], float quanterion[4]);

// Определение структуры для хранения вектора в трехмерном пространстве

int loadObj(const char *filename, struct Object *object);

#ifdef __cplusplus
}
#endif

#endif
