/**
 * @file debug.c
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/utils/debug.h"

#include <stdio.h>

void print_int_bits(int x) {
  for (int i = SIZE(x) - 1; i >= 0; i--) {
    printf("%d", CHECK_BIT(x, i));
  }
}

void print_decimal(s21_decimal *x) {
  printf("%c ", GET_SIGN(x->bits[3]) == 1 ? '-' : '+');

  for (int i = significants_count(x) - 1; i >= 0; i--) {
    // for (int i = 95; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x->bits, i, i));
    if (i % 32 == 0) {
      printf(" ");
    }
  }

  printf(" * 10^%d", GET_SCALE(x->bits[3]));
  printf("\nend_decimal\n");
}

void print_flex_all(flex_int x) {
  printf("%c ", GET_SIGN_FLEX(x.service) == 1 ? '-' : '+');
  print_flex(x.data, x.data_size);
  printf(" * 10^%d", GET_SCALE_FLEX(x.service));
  printf("\n");
  // printf("size in bits: %d\n", x.data_size);
}

int main() {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 0}};

  print_decimal(&x);
  print_decimal(&y);
  uint8_t remainder = 1u;
  // printf("comparisons: <%d>\n", less);

  // s21_decimal z = {{1, 1, 1, 0}};

  flex_int x1 = decimal_to_flex(&x);
  flex_int y1 = decimal_to_flex(&y);

  int crt = binary_remainder(&remainder, 1, y1);

  // print_flex_all(x1);
  // printf("/\n");
  // print_flex_all(y1);
  // printf("=\n");

  // normalization(&x1, &y1);
  // flex_int sum = flex_div(&x1, &y1);

  printf("\nnormalization:\n<><><><><>\n");
  print_flex_all(x1);
  print_flex_all(y1);
  printf("<><><><><>\n");

  // print_flex(sum.data, sum.data_size);
  // print_flex(sum.remainder, sum.remainder_size);
  // printf("expected\n");

  free(x1.data);
  free(y1.data);
  // free(sum.data);
  // free(sum.remainder);

  return 0;
}
