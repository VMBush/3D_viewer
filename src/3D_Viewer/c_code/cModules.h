#ifndef CMODULES_H
#define CMODULES_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
void offset4mat(float x, float y, float z, float mat[4][4]);

// / \brief Создает матрицу, которая централизут объект на сцене
// / \param All Структура, в которой хранятся спарсенные ранее данные об объекте
// / \return указатель на матрицу
// / \attention необходимо очистить память после использования
// float** centralization (work_struct *All);


// /// \brief Создает матрицу перемещения
// /// \param xyz Массив из 4 элементов, где хранятся данные по смещению объекта по каждой оси
// /// \example xyz = "1231", где x = 1, y = 2, z = 3, четвертый параметр всегда 1
// /// \return указатель на матрицу перемещения
// /// \attention необходимо очистить память после использования
// float **matrix_move (float *xyz);

// /// \brief Создает матрицу поворота объекта вокруг оси x
// /// \param corner Угол поворота в радианах
// /// \return указатель на матрицу поворота объекта вокруг оси x
// /// \attention необходимо очистить память после использования
// float **matrix_turn_x(float corner);

// /// \brief Создает матрицу поворота объекта вокруг оси y
// /// \param corner Угол поворота в радианах
// /// \return указатель на матрицу поворота объекта вокруг оси y
// /// \attention необходимо очистить память после использования
// float **matrix_turn_y(float corner);

// /// \brief Создает матрицу поворота объекта вокруг оси z
// /// \param corner Угол поворота в радианах
// /// \return указатель на матрицу поворота объекта вокруг оси z
// /// \attention необходимо очистить память после использования
// float **matrix_turn_z(float corner);

// /// \brief Создает матрицу масштабирования
// /// \param xyz Массив из 4 элементов, где хранятся данные по масштабированию объекта по каждой оси
// /// \example xyz = "1231", где x = 1, y = 2, z = 3, четвертый параметр всегда 1
// /// \return указатель на матрицу масштабирования
// /// \attention необходимо очистить память после использования
// float **matrix_scaling(float *xyz);

// /// \brief Динамически создает матрицу размером 4x4, сразу заполняя ее 0
// /// \return указатель на матрицу
// /// \attention необходимо очистить память после использования
// float **create_matrix_4x4();

// /// \brief Очищает память для матрицы размером 4x4
// /// \param A указатель на матрицу, которую необходимо удалить
// void remove_matrix_4x4(float **A);


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
