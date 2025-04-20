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

#define DEC_SIZE 4
#define MAX_DEC_BIT (DEC_SIZE - 1) * sizeof(unsigned int)

typedef struct {
  unsigned int bits[DEC_SIZE];
} s21_decimal;

typedef struct {
  uint8_t *data;
  uint8_t data_size;
  uint8_t service;
} flex_int;

#endif  // SRC_INCLUDE_TYPES_H_
