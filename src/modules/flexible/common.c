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
  int i = 95;

  for (int bit = 0; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal.bits, i);
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

  data.data_size = ceil((double)significants_count(decimal) / 8);
  data.service = (GET_SCALE(decimal.bits[3]) << 1) | GET_SIGN(decimal.bits[3]);
  data.data = (uint8_t *)calloc(data.data_size, sizeof(uint8_t));
  if (!data.data) {
    return data;
  }

  for (int i = 95; i >= 0; i--) {
    if (CHECK_DEC_BIT(decimal.bits, i)) {
      SET_DEC_BIT(data.data, i);
    }
  }

  return data;
}