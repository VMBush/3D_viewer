#include "tests.h"

int main() {
  Suite *s_matrix = make_matrix_suite();
  Suite *s_vector = make_vector_suite();
  Suite *s_parser = make_obj_loader_suite();

  SRunner *runner = srunner_create(s_matrix);
  srunner_add_suite(runner, s_vector);
  srunner_add_suite(runner, s_parser);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
