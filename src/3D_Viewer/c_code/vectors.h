#ifndef VECTORS_H
#define VECTORS_H

#include "stdlib.h"
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

// size и capacity измеряются в вершинах и парах индексов, а не в единицах!!!
typedef struct
{
    float *data;
    int size;
    int capacity;
} vecVert;

typedef struct
{
    int *data;
    int size;
    int capacity;
} vecInd;

void createVecVert(vecVert *vec);
void createVecInd(vecInd *vec);

void clearVecVert(vecVert *vec);
void clearVecInd(vecInd *vec);

void addToVecVert(vecVert *vec, float xyz[3]);
void addToVecInd(vecInd *vec, int ind[2]);

#ifdef __cplusplus
}
#endif

#endif // VECTORS_H
