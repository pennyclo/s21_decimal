/**
 * @file comparisons.c
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-07-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../../include/comparisons/comparisons.h"

int s21_is_less(s21_decimal *dec1, s21_decimal *dec2) {
  int is_less = 0;

  flex_int decimal_1 = decimal_to_flex(dec1);
  flex_int decimal_2 = decimal_to_flex(dec2);

  int eq_signs = eq_sign(&decimal_1.service, &decimal_2.service);

  normalization(&decimal_1, &decimal_2);

  if (decimal_1.data_size < decimal_2.data_size || eq_signs == 2) {
    is_less = 1;
  } else if (decimal_1.data_size == decimal_2.data_size && eq_signs == 0) {
    for (int i = decimal_1.data_size - 1; i >= 0 && !is_less; i--) {
      uint8_t check1 = CHECK_DEC_BIT(decimal_1.data, i, decimal_1.data_size);
      uint8_t check2 = CHECK_DEC_BIT(decimal_2.data, i, decimal_2.data_size);

      is_less = (check1 < check2) ? 1 : 0;
    }
  }

  if (decimal_1.data) {
    free(decimal_1.data);
  }

  if (decimal_2.data) {
    free(decimal_2.data);
  }

  return is_less;
}

int s21_is_less_or_equal(s21_decimal *dec1, s21_decimal *dec2) {
  int is_less = 0;

  flex_int decimal_1 = decimal_to_flex(dec1);
  flex_int decimal_2 = decimal_to_flex(dec2);

  int eq_signs = eq_sign(&decimal_1.service, &decimal_2.service);

  normalization(&decimal_1, &decimal_2);

  if (decimal_1.data_size < decimal_2.data_size || eq_signs == 2) {
    is_less = 1;
  } else if (decimal_1.data_size == decimal_2.data_size && eq_signs == 0) {
    is_less = 1;
    for (int i = decimal_1.data_size - 1; i >= 0 && is_less; i--) {
      uint8_t check1 = CHECK_DEC_BIT(decimal_1.data, i, decimal_1.data_size);
      uint8_t check2 = CHECK_DEC_BIT(decimal_2.data, i, decimal_2.data_size);

      is_less = (check1 <= check2) ? 1 : 0;
    }
  }

  if (decimal_1.data) {
    free(decimal_1.data);
  }

  if (decimal_2.data) {
    free(decimal_2.data);
  }

  return is_less;
}

int s21_is_greater(s21_decimal *dec1, s21_decimal *dec2) {
  int is_greater = 0;

  flex_int decimal_1 = decimal_to_flex(dec1);
  flex_int decimal_2 = decimal_to_flex(dec2);

  int eq_signs = eq_sign(&decimal_1.service, &decimal_2.service);

  normalization(&decimal_1, &decimal_2);

  if (decimal_1.data_size > decimal_2.data_size || eq_signs == 1) {
    is_greater = 1;
  } else if (decimal_1.data_size == decimal_2.data_size && eq_signs == 0) {
    for (int i = decimal_1.data_size - 1; i >= 0 && !is_greater; i--) {
      uint8_t check1 = CHECK_DEC_BIT(decimal_1.data, i, decimal_1.data_size);
      uint8_t check2 = CHECK_DEC_BIT(decimal_2.data, i, decimal_2.data_size);

      is_greater = (check1 > check2) ? 1 : 0;
    }
  }

  if (decimal_1.data) {
    free(decimal_1.data);
  }

  if (decimal_2.data) {
    free(decimal_2.data);
  }

  return is_greater;
}

int s21_is_greater_or_equal(s21_decimal *dec1, s21_decimal *dec2) {
  int is_greater = 0;

  flex_int decimal_1 = decimal_to_flex(dec1);
  flex_int decimal_2 = decimal_to_flex(dec2);

  int eq_signs = eq_sign(&decimal_1.service, &decimal_2.service);

  normalization(&decimal_1, &decimal_2);

  if (decimal_1.data_size > decimal_2.data_size || eq_signs == 1) {
    is_greater = 1;
  } else if (decimal_1.data_size == decimal_2.data_size && eq_signs == 0) {
    for (int i = decimal_1.data_size - 1; i >= 0 && !is_greater; i--) {
      uint8_t check1 = CHECK_DEC_BIT(decimal_1.data, i, decimal_1.data_size);
      uint8_t check2 = CHECK_DEC_BIT(decimal_2.data, i, decimal_2.data_size);

      is_greater = (check1 >= check2) ? 1 : 0;
    }
  }

  if (decimal_1.data) {
    free(decimal_1.data);
  }

  if (decimal_2.data) {
    free(decimal_2.data);
  }

  return is_greater;
}