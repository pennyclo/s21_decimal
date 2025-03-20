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
  for (int i = 95; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.bits, i));
  }
  printf("\n");

  // printf("%c ", GET_SIGN(x.bits[3]) == 1 ? '-' : '+');
  // printf("%d", GET_SCALE(x.bits[3]));
}

void print_flex(flex_int x) {
  for (int i = x.data_size * 8 - 1; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.data, i));
  }
  printf("\n");
}

int main() {
  s21_decimal x = {{5, 0, 0, 034223141234}};
  flex_int y = decimal_to_flex(x);

  print_decimal(x);
  print_flex(y);
  free(y.data);

  return 0;
}
