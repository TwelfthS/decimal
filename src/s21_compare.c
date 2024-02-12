#include "s21_decimal.h"

int s21_is_less(s21_decimal one, s21_decimal two) {
  int ret = 0;
  rescale(&one, &two);
  int sign1 = s21_sign(one);
  int sign2 = s21_sign(two);
  for (int b = 2; b >= 0; b--) {
    for (int i = 31; i >= 0; i--) {
      if (sign1 * s21_find_bit(one.bits[b], i) <
          sign2 * s21_find_bit(two.bits[b], i)) {
        ret = 1;
        break;
      } else if (sign1 * s21_find_bit(one.bits[b], i) ==
                 sign2 * s21_find_bit(two.bits[b], i)) {
        continue;
      } else {
        ret = 2;
        break;
      }
    }
    if (ret != 0) {
      if (ret == 2) ret = 0;
      break;
    }
  }
  return ret;
}

int s21_is_greater(s21_decimal one, s21_decimal two) {
  int ret = 0;
  rescale(&one, &two);
  int sign1 = s21_sign(one);
  int sign2 = s21_sign(two);
  for (int b = 2; b >= 0; b--) {
    for (int i = 31; i >= 0; i--) {
      if (sign1 * s21_find_bit(one.bits[b], i) >
          sign2 * s21_find_bit(two.bits[b], i)) {
        ret = 1;
        break;
      } else if (sign1 * s21_find_bit(one.bits[b], i) ==
                 sign2 * s21_find_bit(two.bits[b], i)) {
        continue;
      } else {
        ret = 2;
        break;
      }
    }
    if (ret != 0) {
      if (ret == 2) ret = 0;
      break;
    }
  }
  return ret;
}

int s21_is_less_or_equal(s21_decimal one, s21_decimal two) {
  return !s21_is_greater(one, two);
}

int s21_is_greater_or_equal(s21_decimal one, s21_decimal two) {
  return !s21_is_less(one, two);
}

int s21_is_equal(s21_decimal one, s21_decimal two) {
  int ret = 1;
  rescale(&one, &two);
  int sign1 = s21_sign(one);
  int sign2 = s21_sign(two);
  for (int b = 2; b >= 0; b--) {
    for (int i = 0; i <= 31; i++) {
      if (sign1 * s21_find_bit(one.bits[b], i) ==
          sign2 * s21_find_bit(two.bits[b], i)) {
        continue;
      } else {
        ret = 0;
        break;
      }
    }
    if (ret == 0) break;
  }
  return ret;
}

int s21_is_not_equal(s21_decimal one, s21_decimal two) {
  return !s21_is_equal(one, two);
}
