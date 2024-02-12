#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero;
  obnul(&zero);
  if (s21_is_equal(value_2, zero)) {  // division by zero
    return 3;
  }
  int ret = 0;
  s21_decimal temp;  // helper decimals
  obnul(&temp);
  s21_decimal ten;
  obnul(&ten);
  ten.bits[0] = 10;
  int neg = 0;
  if (s21_sign(value_1) + s21_sign(value_2) == 0) {  // sign
    neg = 1;
  }

  if (s21_sign(value_1) == -1)
    s21_negate(value_1, &value_1);  // we work with signs separately
  if (s21_sign(value_2) == -1) s21_negate(value_2, &value_2);

  s21_big_decimal result_big, value_1b, value_2b;
  dec_to_big(*result, &result_big);  // convert to big decimal
  dec_to_big(value_1, &value_1b);
  dec_to_big(value_2, &value_2b);
  ret = big_div(value_1b, value_2b, &result_big);
  big_to_dec(result_big, result);
  if (neg == 1) s21_negate(*result, result);
  if (neg == 1 && ret == 1) ret = 2;

  return ret;
}
