#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  s21_big_decimal result_big;
  s21_big_decimal value_1b;
  s21_big_decimal value_2b;
  dec_to_big(*result, &result_big);
  dec_to_big(value_1, &value_1b);
  dec_to_big(value_2, &value_2b);
  ret = big_add(value_1b, value_2b, &result_big);
  big_to_dec(result_big, result);
  return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  s21_big_decimal result_big;
  s21_big_decimal value_1b;
  s21_big_decimal value_2b;
  dec_to_big(*result, &result_big);
  dec_to_big(value_1, &value_1b);
  dec_to_big(value_2, &value_2b);
  ret = big_sub(value_1b, value_2b, &result_big);
  big_to_dec(result_big, result);
  return ret;
}