/**
 * @file macros.h
 * @author Alexandr Afanasev (https://github.com/pennyclo)
 * @brief
 * @version 1.0
 * @date 2025-03-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef SRC_INCLUDE_MACROS_H_
#define SRC_INCLUDE_MACROS_H_

#define SIZE(value) sizeof(value) * 8

#define SCALE_MASK 0xFF0000

#define MAX(value1, value2) (((value1) >= (value2)) ? (value1) : (value2))

#define CHECK_BIT(value, bit) (((value) >> (bit)) & 1u)

#define GET_SCALE(service) (((service) & (SCALE_MASK)) >> 16)

#define GET_SIGN(service) ((service) >> ((SIZE(service)) - 1))

#define CHECK_DEC_BIT(mass, bit, size)                                    \
  ((size) >= (bit))                                                       \
      ? CHECK_BIT((mass[(bit) / (SIZE(*mass))]), ((bit) % (SIZE(*mass)))) \
      : 0

#define IS_BIT(mass, bit)

#define SET_BIT(value, bit) ((value) |= (1u << (bit)))

#define SET_DEC_BIT(mass, bit) \
  SET_BIT((mass[(bit) / (SIZE(*mass))]), ((bit) % (SIZE(*mass))))

#endif  // SRC_INCLUDE_MACROS_H_
