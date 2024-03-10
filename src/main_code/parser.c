#include "3D_Viewer.h"


int fileReading(work_struct *Data, char *file_name) {
    printf("Ебучий случай, процесс пошел: %s\n", file_name);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Что то пошло по пизде.\n");
        return ERROR_FILE_OPEN;
    }

    init_data(Data);

    int error = count_VF(Data, file);
    if (error == OK) {
        Data->coord = (float *)calloc(Data->amount_coord, sizeof(float));
        Data->index = (int *)calloc(Data->amount_index, sizeof(int));
        if (Data->coord && Data->index) {
            error = add_points(Data, file);
        } else {
            error = ERROR_MEMORY;
        }
    }

    fclose(file); 
    return error;
}

void init_data(work_struct *Data) {
    Data->amount_coord = 0;
    Data->amount_index = 0;
    Data->coord = NULL;
    Data->index = NULL;
    for (int i = 0; i < 2; i++) {
        Data->minMaxX[i] = 0.0f;
        Data->minMaxY[i] = 0.0f;
        Data->minMaxZ[i] = 0.0f;
    }
}

void delete_data(work_struct *Data) {
    if (Data->coord) free(Data->coord);
    if (Data->index) free(Data->index);
}

int count_VF(work_struct *Data, FILE *file) {
    int error;
    char str_file[buff_size];

    while (fgets(str_file, sizeof(str_file), file)) {
        if (str_file[0] != '#') {
            printf("Читаем строчку: %s", str_file);
            if (check_symb(str_file, 'v')) {
                Data->amount_coord++;
            } else if (check_symb(str_file, 'f')) {
                Data->amount_index++;
            }
        }
    }
    error = (Data->amount_coord > 0 && Data->amount_index > 0) ? OK : ERROR_FILE_STRUCT;
    rewind(file);

    printf("Хуяк по координатам: %d\n", Data->amount_coord);
    printf("Херак по граням: %d\n", Data->amount_index);

    return error;
}

int check_symb(char *str, char c) {
    int res = 0;
    if (str[0] == c && str[1] == ' ') res = 1;
    return res;
}

int check_digit(const char *str) {
    return ((str[0] <= '9' && str[0] >= '0') ||
            ((str[0] == '-' || str[0] == '+') && strlen(str) > 1 &&
            str[1] <= '9' && str[1] >= '0'))
            ? 1
            : 0;
}

int add_points(work_struct *Data, FILE *file) {
    int count_coord = 0, count_index = 0;
    int error = OK;
    char str_file[buff_size];

    while (error == OK && (count_coord < Data->amount_coord || count_index < Data->amount_index) &&
            fgets(str_file, sizeof(str_file), file)) {
        if (str_file[0] != '#') { // впизду коментарии
            if (check_symb(str_file, 'v')) {
                error = add_coord(str_file, Data, count_coord);
                count_coord++;
            } else if (check_symb(str_file, 'f')) {
                error = add_index(str_file, Data, count_index);
                count_index++;
            }
        }
    }

    return error;
}

int add_coord(const char *str, work_struct *Data, int count_coord) {
    int error = OK;
    int i = 0;

    str = strchr(str, ' ');
    while (error == OK && str && i < 3) {
        str++;
        if (check_digit(str)) {
            Data->coord[count_coord * 3 + i] = atof(str);
            if (count_coord == 0) {
                Data->minMaxX[0] = Data->coord[count_coord * 3 + i];
                Data->minMaxX[1] = Data->coord[count_coord * 3 + i];
                Data->minMaxY[0] = Data->coord[count_coord * 3 + i + 1];
                Data->minMaxY[1] = Data->coord[count_coord * 3 + i + 1];
                Data->minMaxZ[0] = Data->coord[count_coord * 3 + i + 2];
                Data->minMaxZ[1] = Data->coord[count_coord * 3 + i + 2];
            } else {
                if (Data->coord[count_coord * 3 + i] < Data->minMaxX[0])
                    Data->minMaxX[0] = Data->coord[count_coord * 3 + i];
                else if (Data->coord[count_coord * 3 + i] > Data->minMaxX[1])
                    Data->minMaxX[1] = Data->coord[count_coord * 3 + i];

                if (Data->coord[count_coord * 3 + i + 1] < Data->minMaxY[0])
                    Data->minMaxY[0] = Data->coord[count_coord * 3 + i + 1];
                else if (Data->coord[count_coord * 3 + i + 1] > Data->minMaxY[1])
                    Data->minMaxY[1] = Data->coord[count_coord * 3 + i + 1];

                if (Data->coord[count_coord * 3 + i + 2] < Data->minMaxZ[0])
                    Data->minMaxZ[0] = Data->coord[count_coord * 3 + i + 2];
                else if (Data->coord[count_coord * 3 + i + 2] > Data->minMaxZ[1])
                    Data->minMaxZ[1] = Data->coord[count_coord * 3 + i + 2];
            }
            i++;
            str++;
            while ((str[0] <= '9' && str[0] >= '0') || str[0] == '.')
                str++;
        } else if (str[0] != ' ')
            error = ERROR_FILE_STRUCT;

        if (i < 3 && str - strchr(str, ' ') == 0)
            str = strchr(str, ' ');
        else if (i < 3) {
            error = ERROR_FILE_STRUCT;
        }
    }
    return error;
}

int add_index(const char *str, work_struct *Data, int count_index) {
    int error = OK;
    int i = 0;
    str++;
    str = strchr(str, ' ');
    while (error == OK && str) {
        str++;
        if (str[0] <= '9' && str[0] >= '0') {
            Data->index[count_index * 3 + i] = atoi(str);
            i++;
        }
        str = strchr(str, ' ');
    }
    return error;
}

void centering(work_struct *Data) {
    float center[3];
    for (int j = 0; j < 3; j++) {
        center[j] = (Data->minMaxX[j] + Data->minMaxY[j]) / 2;
    }
    for (int i = 0; i < Data->amount_coord; i++) {
        for (int j = 0; j < 3; j++) {
            Data->coord[i * 3 + j] -= center[j];
        }
    }
}
