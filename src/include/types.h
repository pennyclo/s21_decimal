/**
 * @file types.h
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef SRC_INCLUDE_TYPES_H_
#define SRC_INCLUDE_TYPES_H_

#include <stdint.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint8_t data_size;
  uint8_t service;
  uint8_t *data;
} flex_int;

#endif  // SRC_INCLUDE_TYPES_H_
