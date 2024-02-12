#include "s21_decimal.h"

// converters
void dec_to_big(s21_decimal dec, s21_big_decimal *big) {
  for (int i = 0; i <= 2; i++) {
    big->bits[i] = dec.bits[i];
  }
  big->bits[7] = dec.bits[3];
  for (int i = 3; i <= 6; i++) {
    big->bits[i] = 0;
  }
}

void big_to_dec(s21_big_decimal big, s21_decimal *dec) {
  for (int i = 0; i <= 2; i++) {
    dec->bits[i] = big.bits[i];
  }
  dec->bits[3] = big.bits[7];
}
// arithmetics

int big_add(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result) {
  int ret = 0;
  int temp = 0;
  int res = 0;
  s21_big_decimal temp_result;
  big_obnul(&temp_result);
  if (s21_sign_big(value_1) == -1 && s21_sign_big(value_2) == 1) {
    s21_big_decimal tmp;
    big_negate(value_1, &tmp);
    ret = big_sub(value_2, tmp, result);
  } else if (s21_sign_big(value_1) == 1 && s21_sign_big(value_2) == -1) {
    s21_big_decimal tmp;
    big_negate(value_2, &tmp);
    ret = big_sub(value_1, tmp, result);
  } else {
    int scale1 = s21_get_exp_big(value_1);
    int scale2 = s21_get_exp_big(value_2);
    int dif = scale1 - scale2;
    rescale_big(&value_1, &value_2);
    if (dif >= 0) {
      temp_result.bits[7] = value_1.bits[7];
    } else {
      temp_result.bits[7] = value_2.bits[7];
    }
    for (int i = 0; i <= 223; i++) {
      res = s21_find_bit(value_1.bits[i / 32], i % 32) +
            s21_find_bit(value_2.bits[i / 32], i % 32) + temp;
      if (temp != 0) temp--;
      s21_change_bit(&temp_result.bits[i / 32], i % 32, res % 2);
      if (res - 2 >= 0) temp = 1;
    }
    int scale = s21_get_exp_big(temp_result);
    while (scale > 0 &&
           (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
            temp_result.bits[5] != 0 || temp_result.bits[6] != 0)) {
      div_by_ten(&temp_result, 1);
      scale--;
    }
    temp_result.bits[7] = set_scale(scale, s21_sign_big(temp_result));
    if (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
        temp_result.bits[5] != 0 || temp_result.bits[6] != 0) {
      if (s21_sign_big(temp_result) == 1) {
        ret = 1;
      } else {
        ret = 2;
      }
    }
    equalize_big(result, temp_result);
  }
  return ret;
}

int big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result) {
  int ret = 0;
  int temp = 0;
  int res = 0;
  s21_big_decimal temp_result;
  big_obnul(&temp_result);
  if (absolute_is_less_big(value_1, value_2)) {
    ret = big_sub(value_2, value_1, result);
    big_negate(*result, result);
  } else {
    if (s21_sign_big(value_1) + s21_sign_big(value_2) == 0) {
      s21_big_decimal tmp;
      big_negate(value_2, &tmp);
      ret = big_add(value_1, tmp, result);
    } else {
      if (s21_sign_big(value_1) == -1) {
        big_negate(temp_result, &temp_result);
      }
      int scale1 = s21_get_exp_big(value_1);
      int scale2 = s21_get_exp_big(value_2);
      int dif = scale1 - scale2;
      rescale_big(&value_1, &value_2);
      if (dif >= 0) {
        temp_result.bits[7] =
            set_scale(s21_get_exp_big(value_1), s21_sign_big(value_1));
      } else {
        temp_result.bits[7] =
            set_scale(s21_get_exp_big(value_2), s21_sign_big(value_2));
      }
      for (int i = 0; i <= 223; i++) {
        res = s21_find_bit(value_1.bits[i / 32], i % 32) -
              s21_find_bit(value_2.bits[i / 32], i % 32) - temp;
        if (temp != 0) temp--;
        if (res < 0) {
          temp = 1;
        }
        s21_change_bit(&temp_result.bits[i / 32], i % 32, res % 2);
      }
      int scale = s21_get_exp_big(temp_result);
      while (scale > 0 &&
             (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
              temp_result.bits[5] != 0 || temp_result.bits[6] != 0)) {
        div_by_ten(&temp_result, 1);
        scale--;
      }
      temp_result.bits[7] = set_scale(scale, s21_sign_big(temp_result));
      if (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
          temp_result.bits[5] != 0 || temp_result.bits[6] != 0) {
        if (s21_sign_big(temp_result) == 1) {
          ret = 1;
        } else {
          ret = 2;
        }
      }
      equalize_big(result, temp_result);
    }
  }
  return ret;
}

int big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result_big) {
  int ret = 0;
  int temp = 0;
  int k = 1;
  int res;
  s21_big_decimal temp_result;
  big_obnul(&temp_result);
  for (int i = 0; i < 96; i++) {
    if (s21_find_bit(value_2.bits[i / 32], i % 32)) {
      int n = 0;

      for (int j = 0; n < 223; j++) {
        if (j < i) {
          k = 0;
        } else {
          k = 1;
        }
        res = s21_find_bit(temp_result.bits[j / 32], j % 32) +
              s21_find_bit(value_1.bits[n / 32], n % 32) * k + temp;
        if (temp != 0) temp--;
        s21_change_bit(&temp_result.bits[j / 32], j % 32, res % 2);
        if (res - 2 >= 0) temp = 1;
        if (k != 0) n++;
      }
    }
  }
  int scale = (s21_get_exp_big(value_1) + s21_get_exp_big(value_2));
  while (scale > 28) {
    if (s21_get_exp_big(value_1) == 28 || s21_get_exp_big(value_2) == 28) {
      div_by_ten(&temp_result, 1);
    } else {
      div_by_ten(&temp_result, 1);
    }
    scale--;
  }
  while (scale > 0 && (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
                       temp_result.bits[5] != 0 || temp_result.bits[6] != 0)) {
    div_by_ten(&temp_result, 1);
    scale--;
  }
  temp_result.bits[7] = scale << 16;
  if (s21_sign_big(value_1) + s21_sign_big(value_2) == 0) {
    big_negate(temp_result, &temp_result);
  }
  if (temp_result.bits[3] != 0 || temp_result.bits[4] != 0 ||
      temp_result.bits[5] != 0 || temp_result.bits[6] != 0) {
    if (s21_sign_big(temp_result) == 1) {
      ret = 1;
    } else {
      ret = 2;
    }
  }
  equalize_big(result_big, temp_result);
  return ret;
}

int big_div(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result_big) {
  int ret = 0;
  s21_big_decimal temp1, ten;
  big_obnul(&temp1);
  big_obnul(&ten);
  ten.bits[0] = 10;
  int c = 0;  // scale counter
  while (absolute_is_less_big(value_1, value_2)) {
    mul_by_ten(value_1, &value_1);
    c++;
  }
  div_process(&temp1, &c, value_1, value_2);
  while (c < 0) {
    big_mul(temp1, ten, &temp1);
    c++;
  }
  while (c > 28) {
    div_by_ten(&temp1, 1);
    c--;
  }
  while (c > 0 && (temp1.bits[3] != 0 || temp1.bits[4] != 0 ||
                   temp1.bits[5] != 0 || temp1.bits[6] != 0)) {
    div_by_ten(&temp1, 1);
    c--;
  }
  temp1.bits[7] = c << 16;
  if (temp1.bits[3] != 0 || temp1.bits[4] != 0 || temp1.bits[5] != 0 ||
      temp1.bits[6] != 0) {
    ret = 1;
  }
  equalize_big(result_big, temp1);
  return ret;
}

void div_process(s21_big_decimal *temp1, int *c, s21_big_decimal value_1,
                 s21_big_decimal value_2) {
  s21_big_decimal temp, temp2, zero, ten, one;
  big_obnul(&temp);
  big_obnul(&zero);
  big_obnul(&ten);
  big_obnul(&one);
  ten.bits[0] = 10;
  one.bits[0] = 1;
  int temp_scale1 = s21_get_exp_big(value_1);
  int temp_scale2 = s21_get_exp_big(value_2);
  value_1.bits[7] = 0;
  value_2.bits[7] = 0;
  int n = 0;
  equalize_big(&temp2, value_2);
  while (absolute_is_less_big(temp2, value_1)) {
    mul_by_ten(temp2, &temp2);
    n++;
  }
  for (int i = 0; i < n - 1; i++) {
    big_mul(value_2, ten, &value_2);
    *c = *c - 1;
  }
  big_sub(value_1, value_2, &temp);
  big_add(*temp1, one, temp1);
  while (big_is_greater(temp, zero)) {
    big_sub(temp, value_2, &temp);
    big_add(*temp1, one, temp1);
  }
  *c = *c - temp_scale2;
  *c = *c + temp_scale1;
  while (n > 1 || (!big_is_equal(temp, zero) && *c < 28)) {
    *c = *c + 1;
    big_add(temp, value_2, &temp);
    big_sub(*temp1, one, temp1);
    mul_by_ten(*temp1, temp1);
    mul_by_ten(temp, &temp);
    while (big_is_greater(temp, zero)) {
      big_sub(temp, value_2, &temp);
      big_add(*temp1, one, temp1);
    }
    n--;
  }
  if (!big_is_equal(temp, zero)) big_sub(*temp1, one, temp1);

  int round = 0;  // rounding
  if (!big_is_equal(temp, zero)) big_add(temp, value_2, &temp);
  big_mul(temp, ten, &temp);
  while (big_is_greater(temp, zero)) {
    big_sub(temp, value_2, &temp);
    round++;
  }
  if (!big_is_equal(temp, zero)) round--;
  if (round > 4) big_add(*temp1, one, temp1);
}

// compare
int big_is_greater(s21_big_decimal one, s21_big_decimal two) {
  int ret = 0;
  rescale_big(&one, &two);
  int sign1 = s21_sign_big(one);
  int sign2 = s21_sign_big(two);
  for (int b = 6; b >= 0; b--) {
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

int big_is_equal(s21_big_decimal one, s21_big_decimal two) {
  int ret = 1;
  rescale_big(&one, &two);
  int sign1 = s21_sign_big(one);
  int sign2 = s21_sign_big(two);
  for (int b = 6; b >= 0; b--) {
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

int absolute_is_less_big(s21_big_decimal one,
                         s21_big_decimal two) {  // helper function
  int ret = 0;
  rescale_big(&one, &two);
  for (int b = 6; b >= 0; b--) {
    for (int i = 31; i >= 0; i--) {
      if (s21_find_bit(one.bits[b], i) < s21_find_bit(two.bits[b], i)) {
        ret = 1;
        break;
      } else if (s21_find_bit(one.bits[b], i) == s21_find_bit(two.bits[b], i)) {
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

// helpers

int s21_get_exp_big(
    s21_big_decimal value) {  // get decimal's floating point exponent value
  int exp = 0;
  for (int bit = 16; bit <= 23; bit++) {
    exp += s21_find_bit(value.bits[7], bit) * s21_pow_two(bit - 16);
  }
  return exp;
}

void equalize_big(s21_big_decimal *pointer, s21_big_decimal dec) {
  for (int i = 0; i < 8; i++) {
    pointer->bits[i] = dec.bits[i];
  }
}

int s21_sign_big(s21_big_decimal value) {  // positive / negative
  int sign = s21_find_bit(value.bits[7], 31) ? -1 : 1;
  return sign;
}

void rescale_big(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  s21_big_decimal ten;
  big_obnul(&ten);
  ten.bits[0] = 10;
  int scale1 = s21_get_exp_big(*value_1);
  int scale2 = s21_get_exp_big(*value_2);
  int dif = scale1 - scale2;
  if (dif > 0) {
    for (int i = 0; i < dif; i++) {
      mul_by_ten(*value_2, value_2);
    }
  } else if (dif < 0) {
    dif *= -1;
    for (int i = 0; i < dif; i++) {
      mul_by_ten(*value_1, value_1);
    }
  }
}

int big_negate(s21_big_decimal value, s21_big_decimal *result) {
  int res_code = 0;
  int bit = s21_find_bit(value.bits[7], 31) != 1;
  s21_change_bit(&value.bits[7], 31, bit);
  for (int i = 0; i <= 7; i++) result->bits[i] = value.bits[i];
  if (!result) res_code = 1;
  return res_code;
}

void big_obnul(s21_big_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
  dec->bits[4] = 0;
  dec->bits[5] = 0;
  dec->bits[6] = 0;
  dec->bits[7] = 0;
}

void div_by_ten(s21_big_decimal *dec, int flag_for_rounding) {
  s21_big_decimal temp, temp1, zero, ten, one, value_2, value_x;
  big_obnul(&temp);
  big_obnul(&temp1);
  big_obnul(&zero);
  big_obnul(&ten);
  big_obnul(&one);
  big_obnul(&value_2);
  big_obnul(&value_x);
  ten.bits[0] = 10;
  one.bits[0] = 1;
  value_2.bits[0] = 10;
  value_x.bits[0] = 10;
  int temp_scale = dec->bits[7];
  dec->bits[7] = 0;
  int n = 0;
  while (big_is_greater(*dec, value_x)) {
    equalize_big(&value_2, value_x);
    mul_by_ten(value_2, &value_x);
    n++;
  }
  big_sub(*dec, value_2, &temp);
  big_add(temp1, one, &temp1);
  while (big_is_greater(temp, zero)) {
    big_sub(temp, value_2, &temp);
    big_add(temp1, one, &temp1);
  }
  while (n > 1) {
    big_add(temp, value_2, &temp);
    big_sub(temp1, one, &temp1);
    big_mul(temp1, ten, &temp1);
    big_mul(temp, ten, &temp);
    while (big_is_greater(temp, zero)) {
      big_sub(temp, value_2, &temp);
      big_add(temp1, one, &temp1);
    }
    n--;
  }
  if (!big_is_equal(temp, zero)) big_sub(temp1, one, &temp1);
  int round = 0;  // rounding
  if (!big_is_equal(temp, zero)) big_add(temp, value_2, &temp);
  big_mul(temp, ten, &temp);
  while (big_is_greater(temp, zero)) {
    big_sub(temp, value_2, &temp);
    round++;
  }
  if (flag_for_rounding) {
    if (!big_is_equal(temp, zero)) round--;
    if (round > 4) big_add(temp1, one, &temp1);
    if (round == 5 && s21_find_bit(temp1.bits[0], 0)) {
      big_sub(temp1, one, &temp1);
    }
  }
  equalize_big(dec, temp1);
  dec->bits[7] = temp_scale;
}

void mul_by_ten(s21_big_decimal value_1, s21_big_decimal *result_big) {
  int temp = 0;
  int k = 1;
  int res;
  s21_big_decimal temp_result, ten;
  big_obnul(&temp_result);
  big_obnul(&ten);
  ten.bits[0] = 10;
  for (int i = 0; i < 96; i++) {
    if (s21_find_bit(ten.bits[i / 32], i % 32)) {
      int n = 0;

      for (int j = 0; n < 223; j++) {
        if (j < i) {
          k = 0;
        } else {
          k = 1;
        }
        res = s21_find_bit(temp_result.bits[j / 32], j % 32) +
              s21_find_bit(value_1.bits[n / 32], n % 32) * k + temp;
        if (temp != 0) temp--;
        s21_change_bit(&temp_result.bits[j / 32], j % 32, res % 2);
        if (res - 2 >= 0) temp = 1;
        if (k != 0) n++;
      }
    }
  }
  temp_result.bits[7] = value_1.bits[7];
  equalize_big(result_big, temp_result);
}