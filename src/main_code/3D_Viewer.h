#ifndef MAIN_CODE_H
#define MAIN_CODE_H

#include <stdlib.h>

typedef struct 
{
    int amount_v;
    points *coord;
    double minMaxX[2];
    double minMaxY[2];
    double minMaxZ[2];
} vertex;

typedef struct 
{
    double X;
    double Y;
    double Z;
} points;

typedef struct 
{   
    int *p;
    int amount_p;

} polygons;

typedef struct {
    vertex *v;
    polygons *p;
    int amount_polygons;
} work_strust;

void centralization (work_strust *All);
void normalization (work_strust *All);

#endif
