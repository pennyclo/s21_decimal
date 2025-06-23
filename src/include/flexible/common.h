/**
 * @file common.h
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef SRC_INCLUDE_FLEXIBLE_COMMON_H_
#define SRC_INCLUDE_FLEXIBLE_COMMON_H_

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../macros.h"
#include "../types.h"

int significants_count(s21_decimal *decimal);
flex_int decimal_to_flex(s21_decimal *decimal);
flex_int flex_sum(flex_int *dec1, flex_int *dec2);
flex_int flex_sub(flex_int *dec1, flex_int *dec2);
flex_int flex_mul(flex_int *dec1, flex_int *dec2);
int significants_count_flex(uint8_t *decimal, int size);
flex_int flex_div(flex_int *dividend, flex_int *divisor);
void shift_left(uint8_t *decimal, int size);
void shift_right(flex_int *decimal, int size);
int compare_decimal(uint8_t *dec1, uint8_t *dec2, int size);
flex_int realloc_to_flex(flex_int decimal, int rllc_size);
int normal_bit_sub(flex_int *decimal, int normal_size_bit);
void cycle_sub(uint8_t *differ, uint8_t *min, uint8_t *subtrh, int min_size,
               int subtrh_size);

void normalization(flex_int *dec1, flex_int *dec2);
bool check_alloc(uint8_t *data_size_bit, int *norm_bits);
bool mul_ten(flex_int *decimal);

#endif  // SRC_INCLUDE_FLEXIBLE_COMMON_H_
