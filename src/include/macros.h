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

#define SIZE_IN_BYTE(size_in_bit) (((size_in_bit) + 7) / 8)

#define SCALE_MASK 0xFF0000

#define UINT8_T_MASK 0xFF

#define CHECK_DEC_BYTE(value, byte, size_in_bit)            \
  ((SIZE_IN_BYTE(size_in_bit)) >= (byte)) ? (value[(byte)]) \
                                          : 0u  // unwork correct

#define MAX(value1, value2) (((value1) >= (value2)) ? (value1) : (value2))

#define MIN(value1, value2) (((value1) >= (value2)) ? (value2) : (value1))

#define CHECK_BIT(value, bit) (((value) >> (bit)) & 1u)

#define GET_SCALE(service) (((service) & (SCALE_MASK)) >> 16)

#define GET_SIGN(service) ((service) >> ((SIZE(service)) - 1))

#define GET_SIGN_FLEX(service) ((service) & 1u)

#define GET_SCALE_FLEX(service) ((service) >> 1)

#define CHECK_DEC_BIT_UNSAFE(mass, bit) \
  CHECK_BIT((mass[(bit) / (SIZE(*mass))]), ((bit) % (SIZE(*mass))))

#define CHECK_DEC_BIT(mass, bit, bit_size) \
  ((bit_size) >= (bit)) ? CHECK_DEC_BIT_UNSAFE((mass), (bit)) : 0

#define SET_BIT(value, bit) ((value) |= (1u << (bit)))

#define SET_BIT_ZERO(value, bit) ((value) &= ~(1u << (bit)))

#define SET_DEC_BIT(mass, bit, bit_state)                               \
  ((bit_state) == 1)                                                    \
      ? SET_BIT((mass[(bit) / (SIZE(*mass))]), ((bit) % (SIZE(*mass)))) \
      : SET_BIT_ZERO((mass[(bit) / (SIZE(*mass))]), ((bit) % (SIZE(*mass))))

#endif  // SRC_INCLUDE_MACROS_H_
