#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cModules.h"




int loadObj(const char* filename, struct Object* object) {
    FILE* file = fopen(filename, "r"); 
    if (!file) { 
        return 0; 
    }

    int numVertices = 0;
    int numIndices = 0;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // Обрабатываем вершины
        if (line[0] == 'v' && line[1] == ' ') {
            struct vec3 vertex; // Создаем структуру для хранения вершины
            char* num;
            float input[3] = {0,0,0};
            num = strtok(line, " ");
            num = strtok(NULL, " ");
            sscanf(num, "%f", &(input[0]));
            num = strtok(NULL, " ");
            sscanf(num, "%f", &(input[1]));
            num = strtok(NULL, " ");
            sscanf(num, "%f", &(input[2]));
            addToVecVert(&(object->vertices), input);
        } else if (line[0] == 'f') {
            char* tok;
            // idx[0] - первый, idx[1] и idx[2] - пары для заполнения
            int idx[3];
            tok = strtok(line, " ");
            tok = strtok(NULL, " ");
            sscanf(tok, "%d", &(idx[0]));
            idx[1] = idx[0];
            idx[2] = idx[1];
            tok = strtok(NULL, " ");
            while (tok != NULL) {
                sscanf(tok, "%d", &(idx[2]));
                int toAdd[2] = {idx[1], idx[2]};
                addToVecInd(&(object->indices), toAdd);
                idx[1] = idx[2];
                tok = strtok(NULL, " ");
            }
            addToVecInd(&(object->indices), idx);
        }
    }

    fclose(file); 

    return 0;
}
