#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  obnul(result);
  s21_big_decimal result_big, value_1b, value_2b;
  dec_to_big(*result, &result_big);
  dec_to_big(value_1, &value_1b);
  dec_to_big(value_2, &value_2b);
  s21_decimal temp_result;
  obnul(&temp_result);
  int ret = 0;
  ret = big_mul(value_1b, value_2b, &result_big);
  big_to_dec(result_big, &temp_result);
  equalize(result, temp_result);
  return ret;
}
