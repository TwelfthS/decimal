#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res_code = 0;
  int bit = s21_find_bit(value.bits[3], 31) != 1;
  s21_change_bit(&value.bits[3], 31, bit);
  for (int i = 0; i <= 3; i++) result->bits[i] = value.bits[i];
  if (!result) res_code = 1;
  return res_code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = !(result) ? 1 : 0;
  if (!status) {
    s21_decimal one = {{1, 0, 0, 0}};
    equalize(result, value);
    s21_truncate(value, result);
    if (s21_sign(value) == -1 && s21_get_exp(value))
      status = s21_sub(*result, one, result) ? 1 : 0;
  }
  return status;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = !(result) ? 1 : 0;
  if (!status) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal O_5 = {{5, 0, 0, set_scale(1, 1)}};
    s21_truncate(value, result);  // result now holds truncated value
    s21_decimal scale = {{0, 0, 0, 0}};
    s21_sub(value, *result, &scale);  // original_value - truncated_value (5.5 -
                                      // 5), results in scale
    if (s21_sign(scale) == -1) s21_negate(scale, &scale);
    if (s21_sign(value) == 1) {
      if (s21_is_greater(scale, O_5)) s21_add(*result, one, result);
      if (s21_is_equal(scale, O_5) && is_odd(*result))
        s21_add(*result, one, result);
    } else {
      if (s21_is_greater(scale, O_5)) s21_sub(*result, one, result);
      if (s21_is_equal(scale, O_5) && is_odd(*result))
        s21_sub(*result, one, result);
    }
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = !(result) ? 1 : 0;
  if (!status) {
    s21_big_decimal big_res;
    dec_to_big(value, &big_res);
    int scale = s21_get_exp(value);
    while (scale) {
      big_res.bits[7] = set_scale(--scale, s21_sign(value));
      div_by_ten(&big_res, 0);
    }
    big_to_dec(big_res, result);
  }
  return status;
}

int is_odd(s21_decimal value) { return s21_find_bit(value.bits[0], 0) == 1; }