#include <math.h>

#include "s21_decimal.h"

typedef union {
  int un_int;
  float fl;
} float_in_bits;

void set_sign(s21_decimal *num, int sign) {
  unsigned int mask = 1u << 31;
  if (sign != 0) {
    num->bits[3] |= mask;
  } else {
    num->bits[3] &= ~mask;
  }
}

void set_scale_with_mask(s21_decimal *num, int scale) {
  int clearMask = ~(0xFF << 16);
  num->bits[3] &= clearMask;
  int mask = scale << 16;
  num->bits[3] |= mask;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error_code = 0;
  if (dst == NULL || isinf(src) || isnan(src)) {
    error_code = 1;
  } else {
    obnul(dst);
    if (src < 0) {
      src *= -1;
      s21_negate(*dst, dst);
    }
    dst->bits[0] = src;
  }
  return error_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int sign = s21_sign(src);
  int error_code = 0;
  if (!dst) error_code = 1;

  int exponent = s21_get_exp(src);
  long double tmp = 0.0;

  for (int i = 0; i < 96; i++)
    tmp += s21_pow_two(i) * s21_find_bit(src.bits[i / 32], i % 32);

  if (exponent != 0)
    while (exponent--) tmp /= 10.0;

  tmp *= sign;
  *dst = tmp;

  return error_code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int sign = s21_sign(src);
  int error_code = 0;
  int exponent = s21_get_exp(src);
  int tmp = 0;

  if (src.bits[1] || src.bits[2] || dst == NULL) {
    error_code = 1;
  } else {
    tmp = src.bits[0];
    while (exponent--) tmp /= 10.0;

    tmp *= sign;
    *dst = tmp;
  }
  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  obnul(dst);
  int error_code = 0;
  if (isinf(src) || isnan(src) || dst == NULL) {
    error_code = 1;
  } else {
    if (src != 0) {
      int sign = *(int *)&src >> 31;
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double tmp = (double)fabs(src);
      int scale = 0;
      while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
        tmp *= 10;
        scale++;
      }
      tmp = round(tmp);
      if (scale <= 28 && (exp > -94 && exp < 96)) {
        float_in_bits mantissa = {0};
        tmp = (float)tmp;
        while (fmod(tmp, 10) == 0 && scale > 0) {
          scale--;
          tmp /= 10;
        }
        mantissa.fl = tmp;
        exp = ((*(int *)&mantissa.fl & ~0x80000000) >> 23) - 127;
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
          if ((mantissa.un_int & (1 << j)) != 0) {
            dst->bits[i / 32] |= 1 << i % 32;
          }
        }
        set_sign(dst, sign);
        set_scale_with_mask(dst, scale);
      }
    }
  }
  return error_code;
}
