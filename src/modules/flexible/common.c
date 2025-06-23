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

int significants_count(s21_decimal *decimal) {
  int i = MAX_DEC_BIT * 8 - 1;

  for (int bit = 0; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal->bits, i, i);
  }

  return i + 2;
}

flex_int decimal_to_flex(s21_decimal *decimal) {
  flex_int data = {0};

  data.data_size = significants_count(decimal);
  data.service =
      (GET_SCALE(decimal->bits[3]) << 1) | GET_SIGN(decimal->bits[3]);
  data.data = (uint8_t *)calloc((size_t)ceil((double)data.data_size / 8),
                                sizeof(uint8_t));
  if (!data.data) {
    return data;
  }

  for (int i = data.data_size - 1; i >= 0; i--) {
    if (CHECK_DEC_BIT(decimal->bits, i, data.data_size)) {
      SET_DEC_BIT(data.data, i, 1);
    }
  }

  return data;
}

flex_int realloc_to_flex(flex_int decimal, int rllc_size) {  // delete
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

  decimal.data = realloc;
  return data;
}

flex_int flex_sum(flex_int *dec1, flex_int *dec2) {
  flex_int sum_dec = {0};
  int i = 0, check1 = 0, check2 = 0, check3 = 0, remainder = 0;

  sum_dec.data = (uint8_t *)calloc(
      (size_t)ceil((double)(MAX(dec1->data_size, dec2->data_size) / 8)) + 1,
      sizeof(uint8_t));

  if (!sum_dec.data) {
    return sum_dec;
  }

  for (; i <= MAX(dec1->data_size, dec2->data_size) - 1; i++) {
    check1 = CHECK_DEC_BIT(dec1->data, i, dec1->data_size);
    check2 = CHECK_DEC_BIT(dec2->data, i, dec2->data_size);

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
  int big_dec = 0;

  int bits1 = dec1->data_size;
  int bits2 = dec2->data_size;

  int bytes1 = (bits1 + 7) / 8;
  int bytes2 = (bits2 + 7) / 8;

  int size = bytes1 > bytes2 ? bytes1 : bytes2;
  int size_min = bytes1 > bytes2 ? bytes2 : bytes1;

  sub_dec.data = (uint8_t *)calloc(size, sizeof(uint8_t));

  big_dec = compare_decimal(dec1->data, dec2->data, size_min - 1);

  if (big_dec >= 0) {
    cycle_sub(sub_dec.data, dec1->data, dec2->data, size, bytes2);
  } else {
    cycle_sub(sub_dec.data, dec2->data, dec1->data, size, bytes1);
  }

  sub_dec.data_size = significants_count_flex(sub_dec.data, size);

  return sub_dec;
}

void cycle_sub(uint8_t *differ, uint8_t *min, uint8_t *subtrh, int min_size,
               int subtrh_size) {
  uint16_t borrow = 0;
  for (int i = 0; i < min_size; i++) {
    uint16_t min_i = min[i];
    uint16_t sub_i = (i < subtrh_size ? subtrh[i] : 0);
    uint16_t diff = min_i - sub_i - borrow;
    differ[i] = diff & 0xFF;
    borrow = (min_i < sub_i + borrow) ? 1 : 0;
  }
}

int normal_bit_sub(flex_int *decimal, int normal_size_bit) {  // delete
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

int significants_count_flex(uint8_t *decimal, int size) {
  int i = size * SIZE(uint8_t) - 1;
  int bit = 0;

  for (; i >= 0 && !bit; i--) {
    bit = CHECK_DEC_BIT(decimal, i, i);
  }

  if (!bit) {
    i -= 1;
  }

  return i + 2;
}

flex_int flex_mul(flex_int *dec1, flex_int *dec2) {
  flex_int mul_dec = {0};
  int loan = 0;
  int check1 = 0, check2 = 0, check3 = 0;

  int size = (size_t)ceil((double)(dec1->data_size + dec2->data_size) / 8) + 1;

  mul_dec.data = (uint8_t *)calloc(size, sizeof(uint8_t));

  if (!mul_dec.data) {
    return mul_dec;
  }

  for (int i = dec2->data_size - 1; i >= 0; i--) {
    if (CHECK_DEC_BIT(dec2->data, i, dec2->data_size - 1)) {
      for (int j = 0; j <= dec1->data_size - 1 || loan; j++) {
        check1 = CHECK_DEC_BIT(dec1->data, j, dec1->data_size - 1);
        if (check1 || loan) {
          check2 = CHECK_DEC_BIT(mul_dec.data, j + i, j + i);

          check3 = check1 + check2 + loan;
          loan = (check3 >= 2) ? 1 : 0;

          SET_DEC_BIT(mul_dec.data, j + i, check3 % 2);
        }
      }
    }
  }

  mul_dec.data_size = significants_count_flex(mul_dec.data, size);

  return mul_dec;
}

flex_int flex_div(flex_int *dividend, flex_int *divisor) {
  flex_int quotient = {0};
  int size = (divisor->data_size + 7) / 8;
  quotient.data_size = dividend->data_size - divisor->data_size + 1;
  int size_quotient = (quotient.data_size + 7) / 8;

  quotient.remainder = (uint8_t *)calloc(size, sizeof(uint8_t));
  quotient.data = (uint8_t *)calloc(size_quotient, sizeof(uint8_t));

  for (int i = dividend->data_size - 1; i >= 0; i--) {
    shift_left(quotient.remainder, size);
    quotient.remainder[0] |=
        CHECK_DEC_BIT(dividend->data, i, dividend->data_size - 1);

    if (compare_decimal(quotient.remainder, divisor->data, size - 1) >= 0) {
      cycle_sub(quotient.remainder, quotient.remainder, divisor->data, size,
                size);
      SET_DEC_BIT(quotient.data, i, 1);
    }
  }

  quotient.data_size = significants_count_flex(quotient.data, size_quotient);
  quotient.remainder_size = significants_count_flex(quotient.remainder, size);

  return quotient;
}

void shift_left(uint8_t *decimal, int size) {
  uint8_t carry = 0;

  for (int i = 0; i <= size - 1; i++) {
    uint8_t next_carry = CHECK_BIT(decimal[i], 7);
    decimal[i] = (decimal[i] << 1) | carry;
    carry = next_carry;
  }
}

void shift_right(flex_int *decimal, int size) {
  uint8_t carry = 0;

  for (int i = size - 1; i >= 0; i--) {
    uint8_t next_carry = (CHECK_BIT(decimal->data[i], 0)) == 1 ? 128 : 0;
    decimal->data[i] = (decimal->data[i] >> 1) | carry;
    carry = next_carry;
  }
}

int compare_decimal(uint8_t *dec1, uint8_t *dec2, int size) {
  int valid = 0;
  for (int i = size; i >= 0 && !valid; i--) {
    if (dec1[i] >= dec2[i]) {
      valid = 1;
    } else if (dec2[i] > dec1[i]) {
      valid = -1;
    }
  }

  return valid;
}

/* */
void normalization(flex_int *dec1, flex_int *dec2) {
  uint8_t dec_exp_1 = GET_SCALE_FLEX(dec1->service);
  uint8_t dec_exp_2 = GET_SCALE_FLEX(dec2->service);

  if (dec_exp_1 != dec_exp_2) {
    bool big_exp = dec_exp_1 > dec_exp_2 ? 1 : 0;

    printf("<%d>", big_exp);    // debug
    printf("<%d>", dec_exp_1);  // debug
    printf("<%d>", dec_exp_2);  // debug

    if (big_exp) {
      int sub_exp = dec_exp_1 - dec_exp_2;
      int crt = 1;

      for (int i = 0; i < sub_exp && crt; i++) {
        crt = mul_ten(dec2);
      }

      if (!crt) {
        return;
      }
      // flex_int tmp2 = flex_mul(dec2, &tmp);
      // free(dec2->data);
      // dec2->data = tmp2.data;
      // dec2->data_size = tmp2.data_size;

      // printf("<%d>", sub_exp);  // debug

      // int norm_bits = ceil(sub_exp * 3.32193);
      // printf("<%d>", norm_bits);  // debug
      // int debug_bits = check_alloc(&dec2->data_size, &norm_bits);
      // printf("<%d>", debug_bits);  // debug
    }
  }
}

bool mul_ten(flex_int *decimal) {
  bool crt = false;
  flex_int tmp;
  uint8_t ten = 10u;
  tmp.data = &ten;
  tmp.data_size = 4u;

  flex_int tmp2 = flex_mul(decimal, &tmp);
  free(decimal->data);
  decimal->data = tmp2.data;
  decimal->data_size = tmp2.data_size;

  if (decimal->data) {
    crt = true;
  }

  return crt;
}

bool check_alloc(uint8_t *data_size_bit, int *norm_bits) {
  bool check_alloc = false;

  if (*norm_bits <= *data_size_bit) {
    check_alloc = true;
  }

  return check_alloc;
}