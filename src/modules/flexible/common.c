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

  return i + 2;
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

  data.data_size = significants_count(decimal);
  data.service = (GET_SCALE(decimal.bits[3]) << 1) | GET_SIGN(decimal.bits[3]);
  data.data = (uint8_t *)calloc((size_t)ceil((double)data.data_size / 8),
                                sizeof(uint8_t));
  if (!data.data) {
    return data;
  }

  for (int i = data.data_size - 1; i >= 0; i--) {
    if (CHECK_DEC_BIT(decimal.bits, i, data.data_size)) {
      SET_DEC_BIT(data.data, i, 1);
    }
  }

  return data;
}

flex_int realloc_to_flex(flex_int decimal, int rllc_size) {
  flex_int data = {0};

  data.data_size = rllc_size;
  data.service = decimal.service;
  data.data = (uint8_t *)calloc((size_t)ceil((double)data.data_size / 8),
                                sizeof(uint8_t));
  if (!data.data) {
    return data;
  }

  for (int i = data.data_size - 1; i >= 0; i--) {
    SET_DEC_BIT(data.data, i,
                CHECK_DEC_BIT(decimal.data, i, decimal.data_size - 1));
  }

  return data;
}

flex_int flex_sum(flex_int dec1, flex_int dec2) {
  flex_int sum_dec = {0};
  int i = 0, check1 = 0, check2 = 0, check3 = 0, remainder = 0;

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
      SET_DEC_BIT(sum_dec.data, i, 1);
    }
  }

  sum_dec.data_size = i;

  if (remainder) {
    SET_DEC_BIT(sum_dec.data, i, remainder);
    sum_dec.data_size++;
  }

  return sum_dec;
}

flex_int flex_sub(flex_int *dec1, flex_int *dec2) {
  flex_int sub_dec = {0};
  flex_int one_bit = {0};
  uint8_t res[] = {1, 0};
  one_bit.data = res;
  one_bit.data_size = 1;
  int big_dec = 0;

  if (dec1->data_size > dec2->data_size) {
    if (!(normal_bit_sub(dec2, dec1->data_size))) {
      return sub_dec;
    }
  } else if (dec2->data_size > dec1->data_size) {
    if (!(normal_bit_sub(dec1, dec2->data_size))) {
      return sub_dec;
    }
  }

  // sub_dec.data = (uint8_t *)calloc(
  // (size_t)ceil((double)(MAX(dec1->data_size, dec2->data_size) / 8)) + 1,
  // sizeof(uint8_t));

  // if (!sub_dec.data) {
  // return sub_dec;
  // }

  sub_dec.data_size = MAX(dec1->data_size, dec2->data_size);

  big_dec = compare_decimal(*dec1, *dec2, sub_dec.data_size / 8 - 1);

  if (big_dec == 1 || !big_dec) {
    for (int i = 0; i <= sub_dec.data_size / 8 - 1; i++) {
      dec2->data[i] = ~dec2->data[i];
    }

    flex_int tmp = flex_sum(*dec2, one_bit);
    free(dec2->data);
    *dec2 = tmp;
    sub_dec = flex_sum(*dec1, *dec2);
    shift_left(sub_dec, sub_dec.data_size / 8);
    shift_right(sub_dec, sub_dec.data_size / 8);
  } else if (big_dec == -1) {
    for (int i = 0; i <= sub_dec.data_size / 8 - 1; i++) {
      dec1->data[i] = ~dec1->data[i];
    }

    flex_int tmp = flex_sum(*dec1, one_bit);
    free(dec1->data);
    *dec1 = tmp;
    sub_dec = flex_sum(*dec1, *dec2);
  }

  return sub_dec;
}

int normal_bit_sub(flex_int *decimal, int normal_size_bit) {
  int valid = 1;
  flex_int tmp = realloc_to_flex(*decimal, normal_size_bit);
  if (tmp.data) {
    free(decimal->data);
    *decimal = tmp;
  } else {
    valid = 0;
  }

  return valid;
}

// flex_int flex_sub(flex_int *dec1, flex_int *dec2) {
// flex_int sub_dec = {0};
// int i = 0, check1 = 0, check2 = 0, check3 = 0, loan = 0;
//
// sub_dec.data = (uint8_t *)calloc(
// (size_t)ceil((double)(MAX(dec1->data_size, dec2->data_size) / 8)) + 1,
// sizeof(uint8_t));
//
// if (!sub_dec.data) {
// return sub_dec;
// }
//
// sub_dec.data_size = MAX(dec1->data_size, dec2->data_size);
//
// int big_dec = 0;
//
// if (dec1->data_size >= dec2->data_size) {
// flex_int tmp = realloc_to_flex(*dec2, dec1->data_size);
// if (tmp.data) {
// free(dec2->data);
// *dec2 = tmp;
// big_dec = compare_decimal(*dec1, *dec2, sub_dec.data_size / 8 - 1);
// } else {
// return sub_dec;
// }
// }
//
// for (; i <= sub_dec.data_size - 1; i++) {
// check1 = CHECK_DEC_BIT(dec1->data, i, dec1->data_size);
// check2 = CHECK_DEC_BIT(dec2->data, i, dec2->data_size);
//
// if (big_dec == -1) {
// check3 = check2 - check1 - loan;
// } else {
// check3 = check1 - check2 - loan;
// }
//
// loan = (check3 <= -1) ? 1 : 0;
//
// if (check3 == -1 || check3 == 1) {
// SET_DEC_BIT(sub_dec.data, i, 1);
// }
// }
//
// sub_dec.data_size = i;
//
// if (loan) {
// SET_DEC_BIT(sub_dec.data, i, loan);
// }
//
// return sub_dec;
// }

int significants_count_flex(flex_int decimal, int size) {
  int i = size * SIZE(uint8_t) - 1;

  for (int bit = 0; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal.data, i, i);
  }

  return i + 2;
}

flex_int flex_mul(flex_int dec1, flex_int dec2) {
  flex_int mul_dec = {0};
  int loan = 0;
  int check1 = 0, check2 = 0, check3 = 0;

  int size = (size_t)ceil((double)(dec1.data_size + dec2.data_size) / 8) + 1;

  mul_dec.data = (uint8_t *)calloc(size, sizeof(uint8_t));

  if (!mul_dec.data) {
    return mul_dec;
  }

  for (int i = dec2.data_size - 1; i >= 0; i--) {
    if (CHECK_DEC_BIT(dec2.data, i, dec2.data_size - 1)) {
      for (int j = 0; j <= dec1.data_size - 1 || loan; j++) {
        check1 = CHECK_DEC_BIT(dec1.data, j, dec1.data_size - 1);
        if (check1 || loan) {
          check2 = CHECK_DEC_BIT(mul_dec.data, j + i, j + i);

          check3 = check1 + check2 + loan;
          loan = (check3 >= 2) ? 1 : 0;

          SET_DEC_BIT(mul_dec.data, j + i, check3 % 2);
        }
      }
    }
  }

  mul_dec.data_size = significants_count_flex(mul_dec, size);

  return mul_dec;
}

flex_int flex_div(flex_int dividend, flex_int divisor) {
  flex_int remainder = {0};
  flex_int quotient = {0};

  int size = (size_t)ceil((double)(divisor.data_size) / 8);

  remainder.data = (uint8_t *)calloc(size, sizeof(uint8_t));

  for (int i = dividend.data_size - 1; i >= 0; i--) {
    shift_left(remainder, size);
    remainder.data[0] |=
        CHECK_DEC_BIT(dividend.data, i, dividend.data_size - 1);

    if (compare_decimal(remainder, divisor, size) == 1) {
      flex_sub(&remainder, &divisor);
    }
  }
}

void shift_left(flex_int decimal, int size) {
  uint8_t carry = 0;

  for (int i = 0; i < size; i++) {
    uint8_t next_carry = CHECK_BIT(decimal.data[i], 7);
    decimal.data[i] = (decimal.data[i] << 1) | carry;
    carry = next_carry;
  }
}

void shift_right(flex_int decimal, int size) {
  uint8_t carry = 0;

  for (int i = size; i >= 0; i--) {
    uint8_t next_carry = (CHECK_BIT(decimal.data[i], 0)) == 1 ? 128 : 0;
    decimal.data[i] = (decimal.data[i] >> 1) | carry;
    carry = next_carry;
  }
}

int compare_decimal(flex_int dec1, flex_int dec2, int size) {
  int valid = 0;
  for (int i = size; i >= 0 && !valid; i--) {
    if (dec1.data[i] >= dec2.data[i]) {
      valid = 1;
    } else if (dec2.data[i] > dec1.data[i]) {
      valid = -1;
    }
  }

  return valid;
}