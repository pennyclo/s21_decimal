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

void print_decimal(s21_decimal x) {
  // for (int i = significants_count(x); i >= 0; i--) {
  for (int i = 95; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.bits, i, i));
    if (i % 32 == 0) {
      printf(" ");
    }
  }
  printf("\n");

  // printf("%c ", GET_SIGN(x.bits[3]) == 1 ? '-' : '+');
  // printf("%d", GET_SCALE(x.bits[3]));
}

void print_flex(flex_int x) {
  if (x.data == NULL || x.data_size <= 0) {
    printf("Empty flex_int\n");
    return;
  }

  for (int i = x.data_size - 1; i >= 0; i--) {
    // for (int i = 95; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.data, i, x.data_size - 1));
    if (i % 32 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

int main() {
  s21_decimal x = {{10, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{1024, 0, 0, 0}};

  flex_int x1 = decimal_to_flex(x);
  flex_int y1 = decimal_to_flex(y);

  print_flex(x1);
  printf("*\n");
  print_flex(y1);
  printf("=\n");

  flex_int sum = flex_sub(&x1, &y1);

  print_flex(sum);
  printf("expected\n");
  print_decimal(z);

  free(x1.data);
  free(y1.data);
  free(sum.data);

  return 0;
}
