#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  float mat[4][4];
  create4mat(mat);

  ck_assert_float_eq(mat[0][0], 1);
  ck_assert_float_eq(mat[0][1], 0);
  ck_assert_float_eq(mat[0][2], 0);
  ck_assert_float_eq(mat[0][3], 0);
  ck_assert_float_eq(mat[1][0], 0);
  ck_assert_float_eq(mat[1][1], 1);
  ck_assert_float_eq(mat[1][2], 0);
  ck_assert_float_eq(mat[1][3], 0);
  ck_assert_float_eq(mat[2][0], 0);
  ck_assert_float_eq(mat[2][1], 0);
  ck_assert_float_eq(mat[2][2], 1);
  ck_assert_float_eq(mat[2][3], 0);
  ck_assert_float_eq(mat[3][0], 0);
  ck_assert_float_eq(mat[3][1], 0);
  ck_assert_float_eq(mat[3][2], 0);
  ck_assert_float_eq(mat[3][3], 1);
}
END_TEST

START_TEST(test_2) {
  float mat1[4][4];
  float mat2[4][4];
  float res[4][4];
  float check[4][4];

  create4mat(mat1);
  create4mat(mat2);
  create4mat(res);
  create4mat(check);

  mult4matToRes(mat1, mat2, res);
  mult4mat(mat1, mat2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_float_eq(res[i][j], check[i][j]);
      ck_assert_float_eq(mat2[i][j], check[i][j]);
    }
  }
}
END_TEST

START_TEST(test_3) {
  float mat[4][4];
  float check[4][4];

  create4mat(mat);
  create4mat(check);
  check[0][3] = 5;
  check[1][3] = 4;
  check[2][3] = 3;

  float offset[3] = {5, 4, 3};
  offset4mat(offset, mat);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_float_eq(mat[i][j], check[i][j]);
    }
  }
}
END_TEST

START_TEST(test_4) {
  float mat[4][4];
  float check[4][4];

  create4mat(mat);
  create4mat(check);
  check[0][0] = 5;
  check[1][1] = 5;
  check[2][2] = 5;

  scale4mat(5, mat);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_float_eq(mat[i][j], check[i][j]);
    }
  }
}
END_TEST

START_TEST(test_5) {
  float quan[4];
  float check[4];
  float dmouse[2];

  dmouse[0] = 1;
  dmouse[1] = 1;
  check[0] = -0.0049974;
  check[1] = 0.0049974;
  check[2] = 0;
  check[3] = 0.999975;

  quanterionFromDmouse(dmouse, quan);
  for (int i = 0; i < 4; i++) {
    ck_assert_float_eq_tol(quan[i], check[i], 10e-4);
  }
}
END_TEST

START_TEST(test_6) {
  float quan[4];
  float mat[4][4];
  float check[4][4];

  quan[0] = 0;
  quan[1] = 0;
  quan[2] = 0;
  quan[3] = 1;

  create4mat(check);
  create4mat(mat);
  rotate4mat(quan, mat);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_float_eq_tol(mat[i][j], check[i][j], 10e-5);
    }
  }
}
END_TEST

Suite *make_matrix_suite(void) {
  Suite *s = suite_create("matrix_operations");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);
  return s;
}
