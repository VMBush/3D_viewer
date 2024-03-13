#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cModules.h"

// Определение структуры для хранения вектора в трехмерном пространстве
struct vec3 {
    float x, y, z;
};


// Функция для увеличения емкости массива
void resize(void* array, int* capacity, int element_size) {
    int new_capacity = *capacity * 2;
    array = realloc(array, new_capacity * element_size);
    *capacity = new_capacity;
}

// Функция для добавления элемента в массив
void append(void* array, int* size, int* capacity, int element_size, void* element) {
    if (*size >= *capacity) {
        resize(array, capacity, element_size);
    }
    memcpy((char*)array + (*size) * element_size, element, element_size);
    (*size)++;
}

int loadObj(const char* filename, struct Object* object) {
    FILE* file = fopen(filename, "r"); 
    if (!file) { 
        return 0; 
    }

    int numVertices = 0; 
    int numIndices = 0; 
    int capacity = 16; 
    object->vertices.data = malloc(capacity * sizeof(struct vec3)); 
    object->vertices.capacity = capacity; 
    object->indices.data = malloc(capacity * sizeof(int)); 
    object->indices.capacity = capacity; 

    char line[1024]; 
    while (fgets(line, sizeof(line), file)) { 
        char* token = strtok(line, " \t"); //разбиваем на пробелы
        if (!token) { // Пропускаем пустые строки
            continue;
        }

        if (strcmp(token, "v") == 0) { // Обрабатываем вершины
            struct vec3 vertex; // Создаем структуру для хранения вершины
            if (sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z) != 3) { 
                continue; 
            }
            append(object->vertices.data, &(object->vertices.size), &(object->vertices.capacity), sizeof(struct vec3), &vertex); // Добавляем вершину в массив вершин
        } else if (strcmp(token, "f") == 0) { 
            int index[3]; 
            if (sscanf(line, "f %d %d %d", &index[0], &index[1], &index[2]) != 3) { 
                continue; 
            }
            for (int i = 0; i < 3; i++) { 
                append(object->indices.data, &(object->indices.size), &(object->indices.capacity), sizeof(int), &(index[i]));
            }
        }
    }

    fclose(file); 

    return 1; 
}
