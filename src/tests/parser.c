#include "tests.h"
#define CK_FORK no

START_TEST(test_loadObj_empty_file) {
  struct Object object;
  createVecVert(&(object.vertices));
  createVecInd(&(object.indices));
  clearVecVert(&(object.vertices));
  clearVecInd(&(object.indices));

  int result = loadObj("./tests/test_files/empty.obj", &object);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_loadObj_single_vertex) {
  struct Object object;
  createVecVert(&(object.vertices));
  createVecInd(&(object.indices));
  clearVecVert(&(object.vertices));
  clearVecInd(&(object.indices));

  int result = loadObj("./tests/test_files/single_vertex.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(object.vertices.data[0], 1.0);
  ck_assert_float_eq(object.vertices.data[1], 2.0);
  ck_assert_float_eq(object.vertices.data[2], 3.0);
}
END_TEST

START_TEST(test_loadObj_single_face) {
  struct Object object;
  createVecVert(&(object.vertices));
  createVecInd(&(object.indices));
  clearVecVert(&(object.vertices));
  clearVecInd(&(object.indices));

  int result = loadObj("./tests/test_files/single_face.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(object.indices.data[0], 0);
  ck_assert_int_eq(object.indices.data[1], 1);
  ck_assert_int_eq(object.indices.data[2], 1);
}
END_TEST

START_TEST(test_loadObj_multiple_faces) {
  struct Object object;
  createVecVert(&(object.vertices));
  createVecInd(&(object.indices));
  clearVecVert(&(object.vertices));
  clearVecInd(&(object.indices));

  int result = loadObj("./tests/test_files/multiple_faces.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(object.indices.data[0], 0);
  ck_assert_int_eq(object.indices.data[1], 1);
  ck_assert_int_eq(object.indices.data[2], 1);
  ck_assert_int_eq(object.indices.data[3], 2);
  ck_assert_int_eq(object.indices.data[4], 0);
  ck_assert_int_eq(object.indices.data[5], 2);
}
END_TEST

START_TEST(lol) {
  struct Object object;

  int result = loadObj("andrey_lol", &object);
  ck_assert_int_eq(result, 1);
}
END_TEST


Suite *make_obj_loader_suite(void) {
  Suite *s = suite_create("obj_loader");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_loadObj_empty_file);
  tcase_add_test(tc, test_loadObj_single_vertex);
  tcase_add_test(tc, test_loadObj_single_face);
  tcase_add_test(tc, test_loadObj_multiple_faces);
  tcase_add_test(tc, lol);

  suite_add_tcase(s, tc);
  return s;
}
