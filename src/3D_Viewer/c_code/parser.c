#include "cModules.h"


int fileReading(work_struct *data, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return ERROR_FILE_OPEN;
    }

    init_data(data);

    int error = count_VF(data, file);
    if (error == OK) {
        data->coord = (float *)calloc(data->amount_coord, sizeof(float));
        data->index = (int *)calloc(data->amount_index, sizeof(int));
        data->amount_edges = (int *)calloc(data->amount_edges, sizeof(int));
        if (data->amount_coord && data->amount_index && data->amount_edges) {
            add_points(data, file);
        }
    }

    fclose(file);
    return error;
}


void init_data(work_struct *data) {
    data->amount_coord = 0;
    data->amount_index = 0;
    data->amount_edges = 0;
    data->coord = NULL;
    data->index = NULL;
    for (int i = 0; i < 2; i++) {
        data->minMaxX[i] = 0.0f;
        data->minMaxY[i] = 0.0f;
        data->minMaxZ[i] = 0.0f;
    }
}


void delete_data(work_struct *data) {
    if (data->coord) free(data->coord);
    if (data->index) free(data->index);
}


int count_VF(work_struct *data, FILE *file) {
    int error;
    char str_file[buff_size];

    while (fgets(str_file, sizeof(str_file), file)) {
        if (str_file[0] != '#') {
            if (check_symb(str_file, 'v')) {
                data->amount_coord++;
            } else if (check_symb(str_file, 'f')) {
                int v1, v2, v3;
                error = sscanf(str_file, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v1, &v2, &v3);
                if (error == 3) {
                    data->amount_index += 3;
                    data->amount_edges += 3;
                } else {
                    return ERROR_FILE_STRUCT;
                }
            }
        }
    }
    error = (data->amount_coord > 0 && data->amount_index > 0) ? OK : ERROR_FILE_STRUCT;
    rewind(file);
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

int add_points(work_struct *data, FILE *file) {
    int count_coord = 0, count_index = 0, count_edges = 0;
    int error = OK;
    char str_file[buff_size];

    while (error == OK && (count_coord < data->amount_coord || count_index < data->amount_index || count_edges < data->amount_edges) &&
            fgets(str_file, sizeof(str_file), file)) {
        if (str_file[0] != '#') {
            if (check_symb(str_file, 'v')) {
                error = add_coord(str_file, data, count_coord);
                count_coord++;
            } else if (check_symb(str_file, 'f')) {
                error = add_index(str_file, data, count_index);
                count_index++;
            }
        }
    }

    return error;
}


int add_coord(const char *str, work_struct *data, int count_coord) {
    int error = OK;
    int i = 0;

    str = strchr(str, ' ');
    while (error == OK && str && i < 3) {
        str++;
        if (check_digit(str)) {
            data->coord[count_coord * 3 + i] = atof(str);
            if (count_coord == 0) {
                data->minMaxX[0] = data->coord[count_coord * 3 + i];
                data->minMaxX[1] = data->coord[count_coord * 3 + i];
                data->minMaxY[0] = data->coord[count_coord * 3 + i + 1];
                data->minMaxY[1] = data->coord[count_coord * 3 + i + 1];
                data->minMaxZ[0] = data->coord[count_coord * 3 + i + 2];
                data->minMaxZ[1] = data->coord[count_coord * 3 + i + 2];
            } else {
                if (data->coord[count_coord * 3 + i] < data->minMaxX[0])
                    data->minMaxX[0] = data->coord[count_coord * 3 + i];
                else if (data->coord[count_coord * 3 + i] > data->minMaxX[1])
                    data->minMaxX[1] = data->coord[count_coord * 3 + i];

                if (data->coord[count_coord * 3 + i + 1] < data->minMaxY[0])
                    data->minMaxY[0] = data->coord[count_coord * 3 + i + 1];
                else if (data->coord[count_coord * 3 + i + 1] > data->minMaxY[1])
                    data->minMaxY[1] = data->coord[count_coord * 3 + i + 1];

                if (data->coord[count_coord * 3 + i + 2] < data->minMaxZ[0])
                    data->minMaxZ[0] = data->coord[count_coord * 3 + i + 2];
                else if (data->coord[count_coord * 3 + i + 2] > data->minMaxZ[1])
                    data->minMaxZ[1] = data->coord[count_coord * 3 + i + 2];
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

int add_index(const char *str, work_struct *data, int count_index) {
    int error = OK;
    int i = 0;
    str++;
    str = strchr(str, ' ');
    while (error == OK && str && i < 3) {
        str++;
        if (str[0] <= '9' && str[0] >= '0') {
            int vertex_index = atoi(str);
            data->index[count_index * 3 + i] = vertex_index;
            i++;

            // добавление подсчета ребер
            if (i == 2) {
                int edge_index = data->amount_edges++;
                // data->edges[edge_index].v1 = data->index[count_index * 3];
                // data->edges[edge_index].v2 = data->index[count_index * 3 + 1];
            }
        }
        str = strchr(str, ' ');
    }
    return error;
}


void centering(work_struct *data) {
    float center[3];
    for (int j = 0; j < 3; j++) {
        center[j] = (data->minMaxX[j] + data->minMaxY[j]) / 2;
    }
    for (int i = 0; i < data->amount_coord; i++) {
        for (int j = 0; j < 3; j++) {
            data->coord[i * 3 + j] -= center[j];
        }
    }
}
