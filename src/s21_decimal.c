// helpers

#include "s21_decimal.h"

void s21_change_bit(int *number, int position,  // set value at position
                    int value) {                // 0/1
  int mask = 1 << (position);
  *number = ((*number & ~mask) | (value << position));
}

int s21_find_bit(int number, int position) {  // get value at position
  return ((number & (1 << (position))) != 0);
}

int s21_sign(s21_decimal value) {  // positive / negative
  int sign = s21_find_bit(value.bits[3], 31) ? -1 : 1;
  return sign;
}

int s21_pow_two(int exp) {  // two raised to the power of exp (2^exp)
  int result = 1;
  for (int i = 0; i < exp; i++) result *= 2;
  return result;
}

int s21_get_exp(
    s21_decimal value) {  // get decimal's floating point exponent value
  int exp = 0;
  for (int bit = 16; bit <= 23; bit++) {
    exp += s21_find_bit(value.bits[3], bit) * s21_pow_two(bit - 16);
  }
  return exp;
}

void equalize(s21_decimal *pointer, s21_decimal dec) {
  for (int i = 0; i < 4; i++) pointer->bits[i] = dec.bits[i];
}

// void print_decimal(s21_decimal d) {
//   for (int i = 2; i >= 0; i--) {
//     int value = d.bits[i];
//     printf("%u ", value);
//   }
//   printf("[%u]", d.bits[3]);  // special bits part
//   printf("\n");
// }

// void print_big_decimal(s21_big_decimal d) {
//   for (int i = 6; i >= 0; i--) {
//     int value = d.bits[i];
//     printf("%u ", value);
//   }
//   printf("[%u]", d.bits[7]);  // special bits part
//   printf("\n");
// }

void rescale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal ten;
  obnul(&ten);
  ten.bits[0] = 10;
  int scale1 = s21_get_exp(*value_1);
  int scale2 = s21_get_exp(*value_2);
  int dif = scale1 - scale2;
  if (dif > 0) {
    for (int i = 0; i < dif; i++) {
      s21_mul(*value_2, ten, value_2);
    }
  } else if (dif < 0) {
    dif *= -1;
    for (int i = 0; i < dif; i++) {
      s21_mul(*value_1, ten, value_1);
    }
  }
}

void obnul(s21_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}

int set_scale(int pow, int sign) {
  sign = (sign == -1) ? 1 : 0;
  return (pow << 16) ^ (sign << 31);
}