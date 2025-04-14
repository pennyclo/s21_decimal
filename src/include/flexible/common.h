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
#include <stdlib.h>

#include "../macros.h"
#include "../types.h"

int significants_count(s21_decimal decimal);
flex_int decimal_to_flex(s21_decimal decimal);
flex_int flex_sum(flex_int dec1, flex_int dec2);
flex_int flex_sub(flex_int dec1, flex_int dec2);
flex_int flex_mul(flex_int dec1, flex_int dec2);
int significants_count_flex(flex_int decimal, int size);

#endif  // SRC_INCLUDE_FLEXIBLE_COMMON_H_