#include "vectors.h"
#define nullptr (void*)0
void createVecVert(vecVert* vec){
    vec->data = nullptr;
    vec->capacity = 0;
    vec->size = 0;
}

void createVecInd(vecInd* vec) {
    vec->data = nullptr;
    vec->capacity = 0;
    vec->size = 0;
}

void clearVecVert(vecVert* vec) {
    if (vec->data != nullptr) {
        free(vec->data);
    }
    vec->capacity = 20;
    vec->size = 0;
    vec->data = (float*)malloc(sizeof(float) * 3 * vec->capacity);
}

void clearVecInd(vecInd* vec) {
    if (vec->data != nullptr) {
        free(vec->data);
    }
    vec->capacity = 20;
    vec->size = 0;
    vec->data = (int*)malloc(sizeof(int) * 2 * vec->capacity);
}

void addToVecVert(vecVert* vec, float xyz[3]) {
    if (vec->capacity - vec->size == 0) {
        vec->capacity *= 2;
        vec->data = (float*)realloc(vec->data, sizeof(float) * 3 * vec->capacity);
    }
    memcpy(vec->data + vec->size * 3, xyz, sizeof(float) * 3);
    vec->size++;
}

void addToVecInd(vecInd* vec, int ind[2]) {
    if (vec->capacity - vec->size == 0) {
        vec->capacity *= 2;
        vec->data = (int*)realloc(vec->data, sizeof(int) * 2 * vec->capacity);
    }

    if (ind[0] > ind[1]) {
        int t = ind[0];
        ind[0] = ind[1];
        ind[1] = t;
    }

    int dub=0;
    for (int i = 0; i < vec->size; i++) {
        if (vec->data[2*i] == ind[0] && vec->data[2*i + 1] == ind[1]) {
            dub = 1;
            break;
        }
    }

    if (dub == 0) {
        memcpy(vec->data + vec->size * 2, ind, sizeof(int) * 2);
        vec->size++;
    }
}
