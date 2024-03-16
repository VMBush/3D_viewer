#include "tests.h"
#define CK_FORK no

START_TEST(test_loadObj_empty_file) {
  struct Object object;
  int result = loadObj("/test_files/empty.obj", &object);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_loadObj_single_vertex) {
  struct Object object;
  int result = loadObj("/test_files/single_vertex.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(object.vertices.data[0], 1.0);
  ck_assert_float_eq(object.vertices.data[1], 2.0);
  ck_assert_float_eq(object.vertices.data[2], 3.0);
}
END_TEST

START_TEST(test_loadObj_single_face) {
  struct Object object;
  int result = loadObj("/test_files/single_face.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(object.indices.data[0], 0);
  ck_assert_int_eq(object.indices.data[1], 1);
  ck_assert_int_eq(object.indices.data[2], 2);
}
END_TEST

START_TEST(test_loadObj_multiple_faces) {
  struct Object object;
  int result = loadObj("/test_files/multiple_faces.obj", &object);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(object.indices.data[0], 0);
  ck_assert_int_eq(object.indices.data[1], 1);
  ck_assert_int_eq(object.indices.data[2], 2);
  ck_assert_int_eq(object.indices.data[3], 2);
  ck_assert_int_eq(object.indices.data[4], 3);
  ck_assert_int_eq(object.indices.data[5], 0);
}
END_TEST

Suite *make_obj_loader_suite(void) {
  Suite *s = suite_create("obj_loader");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_loadObj_empty_file);
  tcase_add_test(tc, test_loadObj_single_vertex);
  tcase_add_test(tc, test_loadObj_single_face);
  tcase_add_test(tc, test_loadObj_multiple_faces);

  suite_add_tcase(s, tc);
  return s;
}
