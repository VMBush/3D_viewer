#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  vecVert vert;
  vecInd ind;

  createVecVert(&vert);
  createVecInd(&ind);

  ck_assert_ptr_null(vert.data);
  ck_assert_ptr_null(ind.data);
  ck_assert_int_eq(vert.capacity, 0);
  ck_assert_int_eq(vert.size, 0);
  ck_assert_int_eq(ind.capacity, 0);
  ck_assert_int_eq(ind.size, 0);
}
END_TEST

START_TEST(test_2) {
  vecVert vert;
  vecInd ind;

  createVecVert(&vert);
  createVecInd(&ind);
  clearVecVert(&vert);
  clearVecInd(&ind);

  ck_assert_ptr_nonnull(vert.data);
  ck_assert_ptr_nonnull(ind.data);
  ck_assert_int_eq(vert.capacity, 20);
  ck_assert_int_eq(vert.size, 0);
  ck_assert_int_eq(ind.capacity, 20);
  ck_assert_int_eq(ind.size, 0);
}
END_TEST

START_TEST(test_3) {
  vecVert vert;
  vecInd ind;

  createVecVert(&vert);
  createVecInd(&ind);
  clearVecVert(&vert);
  clearVecInd(&ind);

  for (int i = 0; i < 21; i++) {
    float v[3] = {i, i + 1, i + 2};
    int in[2] = {i, i - 1};
    addToVecVert(&vert, v);
    addToVecInd(&ind, in);
  }
  int in[2] = {3, 2};
  addToVecInd(&ind, in);

  ck_assert_ptr_nonnull(vert.data);
  ck_assert_ptr_nonnull(ind.data);
  ck_assert_int_eq(vert.capacity, 40);
  ck_assert_int_eq(vert.size, 21);
  ck_assert_int_eq(ind.capacity, 40);
  ck_assert_int_eq(ind.size, 21);

  clearVecVert(&vert);
  clearVecInd(&ind);

  ck_assert_ptr_nonnull(vert.data);
  ck_assert_ptr_nonnull(ind.data);
  ck_assert_int_eq(vert.capacity, 20);
  ck_assert_int_eq(vert.size, 0);
  ck_assert_int_eq(ind.capacity, 20);
  ck_assert_int_eq(ind.size, 0);
}
END_TEST

Suite *make_vector_suite(void) {
  Suite *s = suite_create("vector");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
