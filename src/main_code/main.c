#include <stdio.h>
#include "3D_Viewer.h"

int main() {
   
    work_struct Data;
    char file_name[] = "test.obj"; 

    // Чтение файла и загрузка данных
    int result = fileReading(&Data, file_name);

    if (result == OK) {
        printf("Всего координат: %d\n", Data.amount_coord);
        printf("Всего граней: %d\n", Data.amount_index);

        // Вывод координат и индексов для проверки
        printf("Координаты:\n");
        for (int i = 0; i < Data.amount_coord; i++) {
            printf("%.2f %.2f %.2f\n", Data.coord[i * 3], Data.coord[i * 3 + 1], Data.coord[i * 3 + 2]);
        }

        printf("Грани:\n");
        for (int i = 0; i < Data.amount_index; i++) {
            printf("%d %d %d\n", Data.index[i * 3], Data.index[i * 3 + 1], Data.index[i * 3 + 2]);
        }

        // Вывод минимальных и максимальных значений по осям
        printf("МинМакс X: %.2f %.2f\n", Data.minMaxX[0], Data.minMaxX[1]);
        printf("МинМакс Y: %.2f %.2f\n", Data.minMaxY[0], Data.minMaxY[1]);
        printf("МинМакс Z: %.2f %.2f\n", Data.minMaxZ[0], Data.minMaxZ[1]);
    } else {
        printf("Что-то пошло не так.\n");
    }

    // Освобождение памяти, выделенной под координаты и индексы
    delete_data(&Data);

    return 0;
}
