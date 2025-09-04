#include "../include_test/bitwise_functions.h"

#include <stdio.h>

START_TEST(bit_mul_1) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);

  uint8_t res[] = {25, 0, 0};

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_2) {
  s21_decimal x = {{11, 0, 0, 0}};
  s21_decimal y = {{11, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);
  uint8_t res[] = {121, 0, 0};

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_3) {
  s21_decimal x = {{141, 0, 0, 0}};
  s21_decimal y = {{256, 0, 0, 0}};
  s21_decimal z = {{0, 141, 0, 0}};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], z.bits[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_4) {
  s21_decimal x = {{141, 432525, 4324, 0}};
  s21_decimal y = {{256, 5436532, 53451, 0}};

  uint8_t res[] = {0, 141, 0,  0,  228, 48,  74,  52,  179, 219,
                   5, 125, 66, 76, 39,  219, 214, 164, 198, 13};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_5) {
  s21_decimal x = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal y = {{4294967295u, 4294967295u, 4294967295u, 0}};

  uint8_t res[] = {1,    0,    0,    0,    0,    0,    0,    0,
                   0,    0,    0,    0,    254u, 255u, 255u, 255u,
                   255u, 255u, 255u, 255u, 255u, 255u, 255u, 255u};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(mul.data);
}
END_TEST

START_TEST(bit_mul_6) {
  s21_decimal x = {{0, 4095, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};

  uint8_t res[] = {0, 0, 0, 0, 254, 31, 0, 0, 0, 0,
                   0, 0, 0, 0, 0,   0,  0, 0, 0, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int mul = flex_mul(&x1, &y1);

  for (int i = 0; i < ((mul.data_size + 7) / 8); i++) {
    ck_assert_int_eq(mul.data[i], res[i]);
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
  tcase_add_test(tc_bit_mul, bit_mul_4);
  tcase_add_test(tc_bit_mul, bit_mul_5);
  tcase_add_test(tc_bit_mul, bit_mul_6);

  suite_add_tcase(multiplication, tc_bit_mul);

  return multiplication;
}

START_TEST(bit_sub_1) {
  s21_decimal x = {{10, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};

  uint8_t res[] = {5, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sub = flex_sub(&x1, &y1);

  for (int i = 0; i < ((sub.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sub.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sub.data);
}
END_TEST

START_TEST(bit_sub_2) {
  s21_decimal x = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal y = {{4294967294u, 4294967294u, 4294967294u, 0}};

  uint8_t res[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sub = flex_sub(&x1, &y1);

  for (int i = 0; i < ((sub.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sub.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sub.data);
}
END_TEST

START_TEST(bit_sub_3) {
  s21_decimal x = {{1u, 0u, 0u, 0}};
  s21_decimal y = {{0u, 0u, 0u, 0}};

  uint8_t res[] = {1, 0, 0, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sub = flex_sub(&x1, &y1);

  for (int i = 0; i < ((sub.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sub.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sub.data);
}
END_TEST

START_TEST(bit_sub_4) {
  s21_decimal x = {{123456u, 0u, 0u, 0}};
  s21_decimal y = {{123456u, 0u, 0u, 0}};

  uint8_t res[] = {0, 0, 0, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sub = flex_sub(&x1, &y1);

  for (int i = 0; i < ((sub.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sub.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sub.data);
}
END_TEST

START_TEST(bit_sub_5) {
  s21_decimal x = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal y = {{1u, 0, 0, 0}};

  uint8_t res[] = {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  flex_int sub = flex_sub(&x1, &y1);

  for (int i = 0; i < ((sub.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sub.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sub.data);
}
END_TEST

Suite *bits_sub_case_1(void) {
  Suite *subtraction = suite_create("\nbits_sub (bits_sub case 1)\n");

  TCase *tc_bit_sub = tcase_create("bits subtraction test");
  tcase_add_test(tc_bit_sub, bit_sub_1);
  tcase_add_test(tc_bit_sub, bit_sub_2);
  tcase_add_test(tc_bit_sub, bit_sub_3);
  tcase_add_test(tc_bit_sub, bit_sub_4);
  tcase_add_test(tc_bit_sub, bit_sub_5);

  suite_add_tcase(subtraction, tc_bit_sub);

  return subtraction;
}

START_TEST(bit_sum_1) {
  s21_decimal x = {{1, 2, 3, 0}};
  s21_decimal y = {{4, 5, 6, 0}};

  uint8_t res[] = {5, 0, 0, 0, 7, 0, 0, 0, 9};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sum = flex_sum(&x1, &y1);

  for (int i = 0; i < ((sum.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sum.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sum.data);
}
END_TEST

START_TEST(bit_sum_2) {
  s21_decimal x = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal y = {{1u, 0, 0, 0}};

  uint8_t res[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sum = flex_sum(&x1, &y1);

  for (int i = 0; i < ((sum.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sum.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sum.data);
}
END_TEST

START_TEST(bit_sum_3) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{123, 456, 789, 0}};

  uint8_t res[] = {123, 0, 0, 0, 200, 1, 0, 0, 21, 3, 0, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sum = flex_sum(&x1, &y1);

  for (int i = 0; i < ((sum.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sum.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sum.data);
}
END_TEST

START_TEST(bit_sum_4) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};

  uint8_t res[] = {0, 0, 0, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sum = flex_sum(&x1, &y1);

  for (int i = 0; i < ((sum.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sum.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sum.data);
}
END_TEST

START_TEST(bit_sum_5) {
  s21_decimal x = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};

  uint8_t res[] = {0, 0, 0, 0, 1};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int sum = flex_sum(&x1, &y1);

  for (int i = 0; i < ((sum.data_size + 7) / 8); i++) {
    ck_assert_int_eq(sum.data[i], res[i]);
  }

  free(x1.data);
  free(y1.data);
  free(sum.data);
}
END_TEST

Suite *bits_sum_case_1(void) {
  Suite *sum = suite_create("\nbits_sum (bits_sum case 1)\n");

  TCase *tc_bit_sum = tcase_create("bits sum test");
  tcase_add_test(tc_bit_sum, bit_sum_1);
  tcase_add_test(tc_bit_sum, bit_sum_2);
  tcase_add_test(tc_bit_sum, bit_sum_3);
  tcase_add_test(tc_bit_sum, bit_sum_4);
  tcase_add_test(tc_bit_sum, bit_sum_5);

  suite_add_tcase(sum, tc_bit_sum);

  return sum;
}

START_TEST(bit_div_1) {
  s21_decimal x = {{10, 10, 10, 0}};
  s21_decimal y = {{5, 10, 10, 0}};

  uint8_t res[] = {1};
  uint8_t remaind[] = {5};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  flex_int div = flex_div(&x1, &y1);

  for (int i = 0; i < ((div.data_size + 7) / 8); i++) {
    ck_assert_int_eq(div.data[i], res[i]);
  }

  for (int i = 0; i < ((div.remainder_size + 7) / 8); i++) {
    ck_assert_int_eq(div.remainder[i], remaind[i]);
  }

  free(x1.data);
  free(y1.data);
  free(div.data);
  free(div.remainder);
}
END_TEST

START_TEST(bit_div_2) {
  s21_decimal x = {{123456, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};

  uint8_t res[] = {0x40, 0xe2, 0x01};
  uint8_t remaind[] = {0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  flex_int div = flex_div(&x1, &y1);

  for (int i = 0; i < ((div.data_size + 7) / 8); i++) {
    ck_assert_int_eq(div.data[i], res[i]);
  }

  for (int i = 0; i < ((div.remainder_size + 7) / 8); i++) {
    ck_assert_int_eq(div.remainder[i], remaind[i]);
  }

  free(x1.data);
  free(y1.data);
  free(div.data);
  free(div.remainder);
}
END_TEST

START_TEST(bit_div_3) {
  s21_decimal x = {{999, 0, 0, 0}};
  s21_decimal y = {{999, 0, 0, 0}};

  uint8_t res[] = {1};
  uint8_t remaind[] = {0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  flex_int div = flex_div(&x1, &y1);

  for (int i = 0; i < ((div.data_size + 7) / 8); i++) {
    ck_assert_int_eq(div.data[i], res[i]);
  }

  for (int i = 0; i < ((div.remainder_size + 7) / 8); i++) {
    ck_assert_int_eq(div.remainder[i], remaind[i]);
  }

  free(x1.data);
  free(y1.data);
  free(div.data);
  free(div.remainder);
}
END_TEST

START_TEST(bit_div_4) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{10, 0, 0, 0}};

  uint8_t res[] = {0};
  uint8_t remaind[] = {5};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  flex_int div = flex_div(&x1, &y1);

  for (int i = 0; i < ((div.data_size + 7) / 8); i++) {
    ck_assert_int_eq(div.data[i], res[i]);
  }

  for (int i = 0; i < ((div.remainder_size + 7) / 8); i++) {
    ck_assert_int_eq(div.remainder[i], remaind[i]);
  }

  free(x1.data);
  free(y1.data);
  free(div.data);
  free(div.remainder);
}
END_TEST

START_TEST(bit_div_5) {
  s21_decimal x = {{1234567890, 0, 0, 0}};
  s21_decimal y = {{1000000000, 0, 0, 0}};

  uint8_t res[] = {1};
  uint8_t remaind[] = {210, 56, 251, 13};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  flex_int div = flex_div(&x1, &y1);

  for (int i = 0; i < ((div.data_size + 7) / 8); i++) {
    ck_assert_int_eq(div.data[i], res[i]);
  }

  for (int i = 0; i < ((div.remainder_size + 7) / 8); i++) {
    ck_assert_int_eq(div.remainder[i], remaind[i]);
  }

  free(x1.data);
  free(y1.data);
  free(div.data);
  free(div.remainder);
}
END_TEST

Suite *bits_div_case_1(void) {
  Suite *div = suite_create("\nbits_div (bits_div case 1)\n");

  TCase *tc_bit_div = tcase_create("bits div test");
  tcase_add_test(tc_bit_div, bit_div_1);
  tcase_add_test(tc_bit_div, bit_div_2);
  tcase_add_test(tc_bit_div, bit_div_3);
  tcase_add_test(tc_bit_div, bit_div_4);
  tcase_add_test(tc_bit_div, bit_div_5);

  suite_add_tcase(div, tc_bit_div);

  return div;
}

/**
 * @brief Test with boundary normalization. It normalizes a 96-bit number with
 * an exponent of 10 to the power of 21 to the power of 68. The maximum
 * difference between exponents is 47 (provided that all bits of the 96-bit
 * number are filled).
 */
START_TEST(bit_normal_1) {
  int error = 0;
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1376256u}};
  s21_decimal y = {{543, 342, 364, 4456448u}};

  uint8_t normal_x[] = {0,   0,   0,   0,  0,   128, 121, 166, 123, 33,  91,
                        87,  55,  164, 95, 75,  76,  88,  2,   72,  132, 222,
                        164, 168, 200, 91, 160, 180, 179, 39,  132, 17};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  error = normalization(&x1, &y1);

  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(GET_SCALE_FLEX(y1.service), GET_SCALE_FLEX(x1.service));

  for (int i = 0; i < ((x1.data_size + 7) / 8); i++) {
    ck_assert_int_eq(x1.data[i], normal_x[i]);
  }

  free(x1.data);
  free(y1.data);
}
END_TEST

START_TEST(bit_normal_2) {
  int error = 0;
  s21_decimal x = {{100, 0, 0, 65536u}};
  s21_decimal y = {{200, 0, 0, 65536u}};

  uint8_t normal_x[] = {100};
  uint8_t normal_y[] = {200};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  error = normalization(&x1, &y1);

  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(GET_SCALE_FLEX(y1.service), GET_SCALE_FLEX(x1.service));

  ck_assert_int_eq(x1.data[0], normal_x[0]);
  ck_assert_int_eq(y1.data[0], normal_y[0]);

  free(x1.data);
  free(y1.data);
}
END_TEST

START_TEST(bit_normal_3) {
  int error = 0;
  s21_decimal x = {{10, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 65536u}};

  uint8_t normal_x[] = {100};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  error = normalization(&x1, &y1);

  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(GET_SCALE_FLEX(y1.service), GET_SCALE_FLEX(x1.service));

  ck_assert_int_eq(x1.data[0], normal_x[0]);

  free(x1.data);
  free(y1.data);
}
END_TEST

START_TEST(bit_normal_4) {
  int error = 0;
  s21_decimal x = {{1, 0, 0, 65536u}};
  s21_decimal y = {{100, 0, 0, 0}};

  uint8_t normal_y[] = {232, 3};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  error = normalization(&x1, &y1);

  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(GET_SCALE_FLEX(y1.service), GET_SCALE_FLEX(x1.service));

  for (int i = 0; i < (y1.data_size + 7) / 8; i++) {
    ck_assert_int_eq(y1.data[i], normal_y[i]);
  }

  free(x1.data);
  free(y1.data);
}
END_TEST

START_TEST(bit_normal_5) {
  int error = 0;
  s21_decimal x = {{100000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 131072u}};

  uint8_t normal_x[] = {128, 150, 152, 0};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);
  error = normalization(&x1, &y1);

  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(GET_SCALE_FLEX(y1.service), GET_SCALE_FLEX(x1.service));

  for (int i = 0; i < x1.data_size / 8; i++) {
    ck_assert_int_eq(x1.data[i], normal_x[i]);
  }

  free(x1.data);
  free(y1.data);
}
END_TEST

Suite *bits_normal_case_1(void) {
  Suite *normal =
      suite_create("\nbits_normalization (bits_normalization case 1)\n");

  TCase *tc_bit_normalization = tcase_create("bits normalization test");
  tcase_add_test(tc_bit_normalization, bit_normal_1);
  tcase_add_test(tc_bit_normalization, bit_normal_2);
  tcase_add_test(tc_bit_normalization, bit_normal_3);
  tcase_add_test(tc_bit_normalization, bit_normal_4);
  tcase_add_test(tc_bit_normalization, bit_normal_5);

  suite_add_tcase(normal, tc_bit_normalization);

  return normal;
}
