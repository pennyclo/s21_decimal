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

#define OK 0
#define ERROR_MEMORY 1

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
int realloc_to_flex(uint8_t **decimal, int *rllc_size);
int normal_bit_sub(flex_int *decimal, int normal_size_bit);
void cycle_sub(uint8_t *differ, uint8_t *min, uint8_t *subtrh, int min_size,
               int subtrh_size);

int normalization(flex_int *dec1, flex_int *dec2);
bool check_alloc(uint8_t *data_size_bit, int *norm_bits);
bool cycle_normal(uint8_t *big_exp, uint8_t *small_exp, flex_int *small_dec);
bool mul_ten(flex_int *decimal);
int eq_sign(uint8_t *ser_dec1, uint8_t *ser_dec2);
int binary_remainder(uint8_t *remainder, int rem_size_bin, flex_int divisor);
int check_big_dec(uint8_t *decimal_1, int size_dec_1, uint8_t *decimal_2,
                  int size_dec_2);
void rounded(flex_int *decimal, int round);
void print_flex(uint8_t *x, int bit_size);

void bin_copy(uint8_t *copy_value, int copy_size_bin, uint8_t *res_value,
              int res_size_bin);
#endif  // SRC_INCLUDE_FLEXIBLE_COMMON_H_
