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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void print_int_bits(int x) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", CHECK_BIT(x, i));
  }
}

void print_decimal(s21_decimal x) {
  // printf("%c ", GET_SIGN(x.bits[3]) == 1 ? '-' : '+');

  for (int i = 2; i >= 0; i--) {
    print_int_bits(x.bits[i]);
    // printf(" ");
  }

  // printf("%d", GET_SCALE(x.bits[3]));

  printf("\n");
}

/**
 * @brief
 *
 * @param x
 * @return index high bit.
 */
int significants_count(s21_decimal x) {
  int i = 95;
  for (int b = 0; i >= 0 && !b; i--) {
    b = CHECK_DEC_BIT(x.bits, i);
  }

  return i + 1;
}

void parser_decimal(s21_decimal x) {
  for (int i = 95; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.bits, i));
  }
  printf("\n");
}

flex_int decimal_to_flex(s21_decimal x) {
  flex_int data = {0};

  data.data_size = ceil((double)significants_count(x) / 8);
  data.service = (GET_SCALE(x.bits[3]) << 1) | GET_SIGN(x.bits[3]);
  data.data = (uint8_t *)calloc(data.data_size, sizeof(uint8_t));
  // if(!data.data) {
  //   return NULL;
  // }

  for (int i = 95; i >= 0; i--) {
    if (CHECK_DEC_BIT(x.bits, i)) {
      SET_DEC_BIT(data.data, i);
    }
  }

  return data;
}

void parser_flex(flex_int x) {
  for (int i = x.data_size * 8 - 1; i >= 0; i--) {
    printf("%d", CHECK_DEC_BIT(x.data, i));
  }
  printf("\n");
}

int main() {
  s21_decimal x = {{5, 0, 64312321, 0}};
  flex_int y = decimal_to_flex(x);
  // printf("%d\n", significants_count(x));
  // print_decimal(x);
  parser_decimal(x);
  parser_flex(y);
  free(y.data);
  // uint8_t x = 0;

  // SET_BIT(x, 6);

  // for (int i = 7; i >= 0; i--) {
  //   printf("%d", CHECK_BIT(x, i));
  // }

  return 0;
}
