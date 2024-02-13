#include "3D_Viewer.h"


void centralization (work_strust *All){
    double centerX, centerY, centerZ;
    centerX = All->v->minMaxX[0] + (All->v->minMaxX[1] - All->v->minMaxX[0])/2;
    centerY = All->v->minMaxY[0] + (All->v->minMaxY[1] - All->v->minMaxY[0])/2;
    centerZ = All->v->minMaxZ[0] + (All->v->minMaxZ[1] - All->v->minMaxZ[0])/2;

    // какой цикл? при парсинге данные в массиве или в связанной структуре?
    for (int i = 0; i < All->v->amount_v; i++){
        All->v->coord->X -= centerX;
        All->v->coord->Y -= centerY;
        All->v->coord->Z -= centerZ;
    }
}

void normalization (work_strust *All){
    
}


double ** mult_matrix(double **move_matrix, work_strust *All) {

  
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  
}
