#include "../include_test/bitwise_functions.h"

START_TEST(bit_mul_1) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{25, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(x);
  flex_int y1 = decimal_to_flex(y);

  flex_int mul = flex_mul(x1, y1);

  for (int i = 0; i <= 3; i++) {
    ck_assert_int_eq(mul.data[i], z.bits[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_2) {
  s21_decimal x = {{11, 0, 0, 0}};
  s21_decimal y = {{11, 0, 0, 0}};
  s21_decimal z = {{121, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(x);
  flex_int y1 = decimal_to_flex(y);

  flex_int mul = flex_mul(x1, y1);

  for (int i = 0; i <= 3; i++) {
    ck_assert_int_eq(mul.data[i], z.bits[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_3) {
  s21_decimal x = {{141, 0, 0, 0}};
  s21_decimal y = {{256, 0, 0, 0}};
  s21_decimal z = {{36096, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(x);
  flex_int y1 = decimal_to_flex(y);

  flex_int mul = flex_mul(x1, y1);
  for (int i = 0; i <= 3; i++) {
    ck_assert_int_eq(mul.data[i], z.bits[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

Suite *bits_mul_case_1(void) {
  Suite *multiplication = suite_create("\nbits_mul (bits_mul case 1)\n");

  TCase *tc_bit_mul = tcase_create("bits multiplication test");
  tcase_add_test(tc_bit_mul, bit_mul_1);
  tcase_add_test(tc_bit_mul, bit_mul_2);
  tcase_add_test(tc_bit_mul, bit_mul_3);

  suite_add_tcase(multiplication, tc_bit_mul);

  return multiplication;
}
