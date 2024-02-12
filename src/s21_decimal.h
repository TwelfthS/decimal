#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define MAX_INT 2147483647
#define MINUS 2147483648

#include <stdio.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// helpers
void s21_change_bit(int *number, int position, int value);
int s21_find_bit(int number, int position);
int s21_sign(s21_decimal value);
int s21_pow_two(int exp);
int s21_get_exp(s21_decimal value);
void equalize(s21_decimal *pointer, s21_decimal dec);
void rescale(s21_decimal *value_1, s21_decimal *value_2);
void obnul(s21_decimal *dec);
int set_scale(int pow, int sign);
int is_odd(s21_decimal value);
// void print_decimal(s21_decimal d);
// void print_big_decimal(s21_big_decimal d);

// big decimal
void dec_to_big(s21_decimal dec, s21_big_decimal *big);
void big_to_dec(s21_big_decimal big, s21_decimal *dec);
int big_add(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result);
int plus_one(s21_big_decimal value_1, s21_big_decimal *result);
int big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result);
int minus_one(s21_big_decimal value_1, s21_big_decimal *result);
int big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result_big);
int big_div(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *temp1);
void div_process(s21_big_decimal *temp1, int *c, s21_big_decimal value_1,
                 s21_big_decimal value_2);
int big_is_greater(s21_big_decimal one, s21_big_decimal two);
int big_is_equal(s21_big_decimal one, s21_big_decimal two);
int absolute_is_less_big(s21_big_decimal one, s21_big_decimal two);
int s21_get_exp_big(s21_big_decimal value);
void equalize_big(s21_big_decimal *pointer, s21_big_decimal dec);
int s21_sign_big(s21_big_decimal value);
void rescale_big(s21_big_decimal *value_1, s21_big_decimal *value_2);
int big_negate(s21_big_decimal value, s21_big_decimal *result);
void big_obnul(s21_big_decimal *dec);
void div_by_ten(s21_big_decimal *dec, int flag_for_rounding);
void mul_by_ten(s21_big_decimal value_1, s21_big_decimal *result_big);

#endif
