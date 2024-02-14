#include "3D_Viewer.h"

// //дорыботать по икса и игрикам
// void centralization (work_struct *All){
//     double centerX, centerY, centerZ;
//     centerX = All->v->minMaxX[0] + (All->v->minMaxX[1] - All->v->minMaxX[0])/2;
//     centerY = All->v->minMaxY[0] + (All->v->minMaxY[1] - All->v->minMaxY[0])/2;
//     centerZ = All->v->minMaxZ[0] + (All->v->minMaxZ[1] - All->v->minMaxZ[0])/2;
//     for (int i = 0; i < All->v->amount_v; i++){
//         All->v->coord[i].X -= centerX;
//         All->v->coord[i].Y -= centerY;
//         All->v->coord[i].Z -= centerZ;
//     }
// }

// void normalization (work_struct *All){

// }


// float **mult_matrix(float **move_matrix, float **coord) {
//     int cols = 1;
//     int rows = 3;
//     float res[rows][cols];
//     for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//         for (int k = 0; k < 3; k++) {
//           res[i][j] += move_matrix[i][k] * coord[k][j];
//         }
//       }
//     }
//    return res;
// }
