#include "main_test.h"

int main(void) {
  int number_failed = 0;
  SRunner *sr;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, bits_mul_case_1());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
