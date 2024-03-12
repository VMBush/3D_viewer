#ifndef CMODULES_H
#define CMODULES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int amount_coord;
    int amount_index;
    int amount_edges;
    float *coord;
    int *index;
    float minMaxX[2];
    float minMaxY[2];
    float minMaxZ[2];
} work_struct;

void create4mat(float arr[4][4]);
void mult4matToRes(float m1[4][4], float m2[4][4], float res[4][4]);
void mult4mat(float left[4][4], float res_right[4][4]);
void offset4mat(float xyz[3], float mat[4][4]);
void scale4mat(float scale, float mat[4][4]);
void rotate4mat(float xyz[4], float mat[4][4]);
void quanterionFromDmouse(float dpos[2], float quanterion[4]);

// / \brief Создает матрицу, которая централизут объект на сцене
// / \param All Структура, в которой хранятся спарсенные ранее данные об объекте
// / \return указатель на матрицу
// / \attention необходимо очистить память после использования
// float** centralization (work_struct *All);


#define OK 0
#define ERROR_FILE_OPEN -1
#define ERROR_MEMORY -2
#define ERROR_FILE_STRUCT -3
#define buff_size 256 // поменять размер


int fileReading(work_struct *data, char *file_name);
void init_data(work_struct *data);
void delete_data(work_struct *data);
int count_VF(work_struct *data, FILE *file);
int check_symb(char *str, char c);
int check_digit(const char *str);
int add_points(work_struct *data, FILE *file);
int add_coord(const char *str, work_struct *data, int count_coord);
int add_index(const char *str, work_struct *data, int count_index);
void centering(work_struct *data);


#ifdef __cplusplus
}
#endif

#endif
