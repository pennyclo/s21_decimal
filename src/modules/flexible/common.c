/**
 * @file common.c
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../../include/flexible/common.h"

#include <stdio.h>

/**
 * @brief Determines the position of the oldest set bit in the number.
 *
 * The function traverses the bits of the number `s21_decimal` from the highest
 * to the lowest and finds the index of the most significant (highest) set bit.
 * If the number is zero, returns 0.
 *
 * @param decimal A number of type `s21_decimal`.
 * @return The index of the oldest bit set (0-95) or 0 if the number is zero.
 */
int significants_count(s21_decimal decimal) {
  int i = MAX_DEC_BIT * 8 - 1;

  for (int bit = 0; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal.bits, i, i);
  }

  return i + 1;
}

/**
 * @brief Converts 96-bit number `s21_decimal` to `flex_int` format.
 *
 * The function converts the number `s21_decimal` to `flex_int`,
 * allocating memory for significant bits and setting service data.
 * The data size (`data_size`) is defined as the number of significant
 * bits, rounded to bytes. The `service` field encodes the scale (scale) of
 * and the sign of the number. The bits are copied from `s21_decimal` to
 * `flex_int`.
 *
 * @param decimal A 96-bit number in `s21_decimal` format.
 * @return A `flex_int` structure containing an equivalent representation of the
 * number.
 */
flex_int decimal_to_flex(s21_decimal decimal) {
  flex_int data = {0};

  data.data_size = significants_count(decimal) + 1;
  data.service = (GET_SCALE(decimal.bits[3]) << 1) | GET_SIGN(decimal.bits[3]);
  data.data = (uint8_t *)calloc((size_t)ceil((double)data.data_size / 8),
                                sizeof(uint8_t));
  if (!data.data) {
    return data;
  }

  for (int i = data.data_size - 1; i >= 0; i--) {
    if (CHECK_DEC_BIT(decimal.bits, i, data.data_size)) {
      SET_DEC_BIT(data.data, i);
    }
  }

  return data;
}

flex_int flex_sum(flex_int dec1, flex_int dec2) {
  flex_int sum_dec = {0};
  int remainder = 0;
  int i = 0, check1 = 0, check2 = 0, check3 = 0;

  sum_dec.data = (uint8_t *)calloc(
      (size_t)ceil((double)(MAX(dec1.data_size, dec2.data_size) / 8)) + 1,
      sizeof(uint8_t));

  if (!sum_dec.data) {
    return sum_dec;
  }

  for (; i <= MAX(dec1.data_size, dec2.data_size) - 1; i++) {
    check1 = CHECK_DEC_BIT(dec1.data, i, dec1.data_size);
    check2 = CHECK_DEC_BIT(dec2.data, i, dec2.data_size);

    check3 = check1 + check2 + remainder;
    remainder = (check3 >= 2) ? 1 : 0;

    if (check3 % 2) {
      SET_DEC_BIT(sum_dec.data, i);
    }
  }

  sum_dec.data_size = i;

  if (remainder) {
    SET_DEC_BIT(sum_dec.data, i);
    sum_dec.data_size++;
  }

  return sum_dec;
}

flex_int flex_sub(flex_int dec1, flex_int dec2) {
  flex_int sub_dec = {0};
  int loan = 0;
  int i = 0, check1 = 0, check2 = 0, check3 = 0;

  sub_dec.data = (uint8_t *)calloc(
      (size_t)ceil((double)(MAX(dec1.data_size, dec2.data_size) / 8)) + 1,
      sizeof(uint8_t));

  if (!sub_dec.data) {
    return sub_dec;
  }

  sub_dec.data_size = MAX(dec1.data_size, dec2.data_size);

  for (; i <= sub_dec.data_size - 1; i++) {
    check1 = CHECK_DEC_BIT(dec1.data, i, dec1.data_size);
    check2 = CHECK_DEC_BIT(dec2.data, i, dec2.data_size);

    if (dec1.data > dec2.data) {
      check3 = check1 - check2 - loan;
    } else {
      check3 = check2 - check1 - loan;
    }

    loan = (check3 <= -1) ? 1 : 0;

    if (check3 == -1 || check3 == 1) {
      SET_DEC_BIT(sub_dec.data, i);
    }
  }

  sub_dec.data_size = i;

  if (loan) {
    SET_DEC_BIT(sub_dec.data, i);
  }

  return sub_dec;
}

int significants_count_flex(flex_int decimal) {
  int i = MAX_DEC_BIT * 8 - 1;

  for (int bit = 0; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal.data, i, i);
  }

  return i + 1;
}

flex_int flex_mul(flex_int dec1, flex_int dec2) {
  flex_int mul_dec = {0};
  int loan = 0;
  int check1 = 0, check2 = 0, check3 = 0;

  int size = (size_t)ceil((double)(dec1.data_size + dec2.data_size) / 8) + 1;

  mul_dec.data = (uint8_t *)calloc(size, sizeof(uint8_t));

  if (!mul_dec.data || size > 96) {
    return mul_dec;
  }

  int i = dec2.data_size - 1;

  for (int bit = 0; i >= 0; i--) {
    bit = CHECK_DEC_BIT(dec2.data, i, dec2.data_size);
    if (bit) {
      for (int j = 0; j <= dec1.data_size - 1 || loan; j++) {
        check1 = CHECK_DEC_BIT(dec1.data, j, dec1.data_size);
        if (check1 || loan) {
          check2 = CHECK_DEC_BIT(mul_dec.data, j + i, j + i);

          check3 = check1 + check2 + loan;
          loan = (check3 >= 2) ? 1 : 0;

          if (check3 % 2) {
            SET_DEC_BIT(mul_dec.data, j + i);
          } else {
            SET_DEC_BIT_ZERO(mul_dec.data, j + i);
          }
        }
      }
    }
  }

  mul_dec.data_size = significants_count_flex(mul_dec);

  return mul_dec;
}