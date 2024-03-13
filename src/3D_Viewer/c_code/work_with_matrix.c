#include "cModules.h"
#include <math.h>

void create4mat(float arr[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      arr[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; i++) {
    arr[i][i] = 1;
  }
}

void mult4matToRes(float m1[4][4], float m2[4][4], float res[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      res[i][j] = 0;
      for (int k = 0; k < 4; k++) {
        res[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
}

void mult4mat(float m1[4][4], float m2[4][4]) {
  float res[4][4];
  mult4matToRes(m1, m2, res);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m2[i][j] = res[i][j];
    }
  }
}

void offset4mat(float xyz[3], float mat[4][4]) {
  float offset[4][4];
  create4mat(offset);
  offset[0][3] = xyz[0];
  offset[1][3] = xyz[1];
  offset[2][3] = xyz[2];
  mult4mat(offset, mat);
}

void scale4mat(float scaleVal, float mat[4][4]) {
  float scale[4][4];
  create4mat(scale);
  scale[0][0] = scale[1][1] = scale[2][2] = scaleVal;
  mult4mat(scale, mat);
}

void rotate4mat(float xyz[4], float mat[4][4]) {
  float rotate[4][4];
  float x, y, z, w;
  x = xyz[0];
  y = xyz[1];
  z = xyz[2];
  w = xyz[3];
  rotate[0][0] = 1 - 2 * y * y - 2 * z * z;
  rotate[0][1] = 2 * x * y - 2 * z * w;
  rotate[0][2] = 2 * x * z + 2 * y * w;
  rotate[1][0] = 2 * x * y + 2 * z * w;
  rotate[1][1] = 1 - 2 * x * x - 2 * z * z;
  rotate[1][2] = 2 * y * z - 2 * x * w;
  rotate[2][0] = 2 * x * z - 2 * y * w;
  rotate[2][1] = 2 * y * z + 2 * x * w;
  rotate[2][2] = 1 - 2 * x * x - 2 * y * y;
  for (int i = 0; i < 3; i++) {
    rotate[3][i] = rotate[i][3] = 0;
  }
  rotate[3][3] = 1;
  mult4mat(rotate, mat);
}

void quanterionFromDmouse(float dPos[2], float quanterion[4]) {

  float len = sqrt(pow(dPos[0], 2) + pow(dPos[1], 2));
  float w = cos(len / 200);

  float scaleParam =
      sqrt((pow(dPos[0], 2) + pow(dPos[1], 2)) / (1 - pow(w, 2)));
  quanterion[0] = -dPos[1] / scaleParam;
  quanterion[1] = dPos[0] / scaleParam;
  quanterion[2] = 0;
  quanterion[3] = w;
}
