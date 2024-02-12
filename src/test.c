#include <check.h>

#include "s21_decimal.h"

// // // negate
// {
START_TEST(s21_negate_1) {
  s21_decimal d = {{1, 0, 0, 0}};
  s21_decimal ans;
  s21_decimal true_ans = {{1, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_negate(d, &ans));          // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal ans;
  s21_decimal true_ans = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_negate(d, &ans));          // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal d = {{656636, 23124, 2342, MINUS}};
  s21_decimal ans;
  s21_decimal true_ans = {{656636, 23124, 2342, 0}};

  ck_assert_int_eq(0, s21_negate(d, &ans));          // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST
// }

// // // add
// {
START_TEST(s21_add_1) {  // + + overflow
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 1, 0, 0}};  // 4295623932M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1313272, 1, 0, 0}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_2) {  // + -
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_3) {  // + - overflow
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_4) {  // - -
  s21_decimal d1 = {
      {1449652028, 1336569152, 1, MINUS}};  // -24187264871841656636M
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1395663240, -1621828992, 2, 2147483648}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_5) {                      // .
  s21_decimal d1 = {{1101, 0, 0, 196608}};   // 1.101M
  s21_decimal d2 = {{10001, 0, 0, 262144}};  // 1.0001M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{21011, 0, 0, 262144}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_6) {                    // .
  s21_decimal d1 = {{122, 0, 0, 131072}};  // 1.22M
  s21_decimal d2 = {{29, 0, 0, 65536}};    // 2.9M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{412, 0, 0, 131072}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_7) {                  // . same scale
  s21_decimal d1 = {{12, 0, 0, 65536}};  // 1.2M
  s21_decimal d2 = {{29, 0, 0, 65536}};  // 2.9M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{41, 0, 0, 65536}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_8) {  // . dif_scale dif_bits
  s21_decimal d1 = {{-1297123461, 1256424873, 1269830,
                     -2146631680}};      // -2342423442342.2342342342523M
  s21_decimal d2 = {{29, 0, 0, 65536}};  // 2.9M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1677940869, 1256418121, 1269830, -2146631680}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_9) {  // . same_scale dif_bits
  s21_decimal d1 = {{-1297123461, 1256424873, 1269830,
                     -2146631680}};  // -2342423442342.2342342342523M
  s21_decimal d2 = {{-77531269, 5201, 0, 851968}};  // 2.2342342342523M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1219592192, 1256419671, 1269830, -2146631680}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_10) {                   // . dif_scale dif_bits
  s21_decimal d1 = {{8, 5, 0, 65536}};     // 2147483648.8M
  s21_decimal d2 = {{299, 0, 0, 131072}};  // 2.99M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{379, 50, 0, 131072}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_11) {  // . dif_scale dif_bits
  s21_decimal d1 = {
      {1449652028, 1336569152, 1, -2147221504}};  // -2418726487184165.6636M
  s21_decimal d2 = {{2048687041, 5, 0, -2147090432}};  // -23523.523521M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{985001777, 512929063, 131, -2147090432}};

  ck_assert_int_eq(0, s21_add(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal d1 = {{-1, -1, -1, 0}};  // 79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, 0}};  // 79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_add(d1, d2, &ans));  // error
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal d1 = {{-1, -1, -1, MINUS}};  // -79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, MINUS}};  // -79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(2, s21_add(d1, d2, &ans));  // error
}
END_TEST
// }

// // // sub
// {
START_TEST(s21_sub_1) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 1, 0, 0}};  // 4295623932M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 1, 0, MINUS}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1313272, 0, 0, 0}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {
      {1449652028, 1336569152, 1, MINUS}};  // -24187264871841656636M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1395663240, -1621828992, 2, 0}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal d1 = {{1, 0, 0, MINUS}};
  s21_decimal d2 = {{2, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{3, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal d1 = {{475, 0, 0, 196608}};  // 0.475
  s21_decimal d2 = {{2, 0, 0, 65536}};     // 0.2
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{275, 0, 0, 196608}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal d1 = {{122, 0, 0, 131072}};  // 1.22
  s21_decimal d2 = {{29, 0, 0, 65536}};    // 2.9
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{168, 0, 0, -2147352576}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal d1 = {{299, 0, 0, 65536}};   // 29.9
  s21_decimal d2 = {{114, 0, 0, 131072}};  // 1.14
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2876, 0, 0, 131072}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal d1 = {{471844685, -2076110342, 67287822,
                     -2146041856}};  // -124124.1241241241241241241421M
  s21_decimal d2 = {
      {1449652028, 1336569152, 1, -2147483648}};  // -24187264871841656636M;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-628505564, 114442738, 1311194256, 589824}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal d1 = {
      {1449652028, 1336569152, 1, -2147483648}};  // -24187264871841656636M;
  s21_decimal d2 = {{471844685, -2076110342, 67287822,
                     -2146041856}};  // -124124.1241241241241241241421M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-628505564, 114442738, 1311194256, -2146893824}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal d1 = {{122, 0, 0, -2147352576}};  // -1.22M
  s21_decimal d2 = {{29, 0, 0, 65536}};         // 2.9M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{412, 0, 0, -2147352576}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_12) {
  s21_decimal d1 = {{122, 0, 0, -2147352576}};  // -1.22M
  s21_decimal d2 = {{29, 0, 0, 65536}};         // 2.9M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{412, 0, 0, 131072}};

  ck_assert_int_eq(0, s21_sub(d2, d1, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_13) {
  s21_decimal d1 = {{122, 0, 0, 131072}};  // 1.22M
  s21_decimal d2 = {{299, 0, 0, 131072}};  // 2.99M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{177, 0, 0, -2147352576}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_sub_14) {                   // . dif_scale dif_bits
  s21_decimal d1 = {{8, 5, 0, 65536}};     // 2147483648.8M
  s21_decimal d2 = {{299, 0, 0, 131072}};  // 2.99M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-219, 49, 0, 131072}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_15) {
  s21_decimal d1 = {{-1, -1, -1, 1572864}};  // 79228.162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, 0}};        // 79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-79229, -1, -1, -2147483648}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_16) {
  s21_decimal d1 = {{268435456, 1042612833, 542101086,
                     1835008}};  // 1.0000000000000000000000000000M
  s21_decimal d2 = {
      {268435456, 1042612833, 542101086, 0}};  // 10000000000000000000000000000M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{268435455, 1042612833, 542101086, -2147483648}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_17) {
  s21_decimal d1 = {
      {268435456, 1042612833, 542101086, 0}};  // 10000000000000000000000000000M
  s21_decimal d2 = {{268435456, 1042612833, 542101086,
                     1835008}};  // 1.0000000000000000000000000000M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{268435455, 1042612833, 542101086, 0}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_18) {
  s21_decimal d1 = {{1000, 1, 0, 0}};       // 4294968296M
  s21_decimal d2 = {{1000, 0, 0, 196608}};  // 1.000M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{999000, 1000, 0, 196608}};

  ck_assert_int_eq(0, s21_sub(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_sub_19) {
  s21_decimal d1 = {{-1, -1, -1, 0}};      // 79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, MINUS}};  // -79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_sub(d1, d2, &ans));  // error
}
END_TEST

START_TEST(s21_sub_20) {
  s21_decimal d1 = {{-1, -1, -1, MINUS}};  // -79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, 0}};      // 79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(2, s21_sub(d1, d2, &ans));  // error
}
END_TEST
// }

// // // mul
// {
START_TEST(s21_mul_1) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 1, 0, 0}};  // 4295623932M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1674106896, 656736, 0, 0}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1674106896, 100, 0, MINUS}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};  // 24187264871841656636M
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(2, s21_mul(d1, d2, &ans));  // error!
}
END_TEST

START_TEST(s21_mul_4) {  // - -
  s21_decimal d1 = {{1, 0, 0, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1449652028, 1336569152, 1, 0}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_5) {  // . .
  s21_decimal d1 = {{65663665, 0, 0, 131072}};
  s21_decimal d2 = {{6566362, 10, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-372208710, 656737039, 0, 196608}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_6) {  // . .
  s21_decimal d1 = {{-493337520, 152, 0, -2147090432}};
  s21_decimal d2 = {{6566362, 10, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-906134496, 365491242, 1529, -2147024896}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_7) {  // - .
  s21_decimal d1 = {{-493337520, 152, 0, -2147090432}};
  s21_decimal d2 = {{2, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-986675040, 305, 0, 393216}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_8) {  // 0. 0.
  s21_decimal d1 = {{475, 0, 0, 196608}};
  s21_decimal d2 = {{23498273, 0, 0, 524288}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1723222213, 2, 0, 720896}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_9) {  // 0... 0...
  s21_decimal d1 = {
      {-1944707493, 1863956914, 451, 1441792}};  // 0.8327487211232141123163M
  s21_decimal d2 = {
      {-666756672, 385673562, 176, 1441792}};  // 0.3248283412312231123392M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{314972090, -251767578, 146638552, 1835008}};

  ck_assert_int_eq(0, s21_mul(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_mul_10) {
  s21_decimal d1 = {{-1, -1, -1, 0}};  // 79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, 0}};  // 79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_mul(d1, d2, &ans));  // error
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal d1 = {{-1, -1, -1, MINUS}};  // -79228162514264337593543950335M
  s21_decimal d2 = {{-1, -1, -1, 0}};      // 79228162514264337593543950335M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(2, s21_mul(d1, d2, &ans));  // error
}
END_TEST
// }

// // // div
// {
START_TEST(s21_div_1) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 1, 0, 0}};  // 4295623932M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{486594943, 1915824083, 82866, 1835008}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 1, 0, 0}};  // 4295623932M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1811825067, -811522578, -748615285, 1638400}};

  ck_assert_int_eq(0, s21_div(d2, d1, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, 0}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal d1 = {{656636, 0, 0, 0}};
  s21_decimal d2 = {{656636, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, MINUS}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};  // 24187264871841656636M
  s21_decimal d2 = {{659899536, 563, 0, MINUS}};      // -2418726487184
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1694541358, 1042772303, 542101086, -2146107392}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_6) {  // - -
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1449652028, 1336569152, 1, 0}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_7) {  // 0... 0...
  s21_decimal d1 = {{-1757806240, -619419189, 257625639,
                     1835008}};  // 0.4752354245245245252452352352M
  s21_decimal d2 = {{383865796, 1960380419, 127384394,
                     1835008}};  // 0.2349827323522352352323523524M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-716195034, 1498358377, 1096359878, 1835008}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_8) {  // 0... 0...
  s21_decimal d1 = {{-1757806240, -619419189, 257625639,
                     1835008}};  // 0.4752354245245245252452352352M
  s21_decimal d2 = {{383865796, 1960380419, 127384394,
                     1835008}};  // 0.2349827323522352352323523524M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-1201219085, 1418005801, 268044821, 1835008}};

  ck_assert_int_eq(0, s21_div(d2, d1, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_9) {  // 0.475 / 0.2
  s21_decimal d1 = {{475, 0, 0, 196608}};
  s21_decimal d2 = {{2, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2375, 0, 0, 196608}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_10) {  // 4.2 / 4.475
  s21_decimal d1 = {{4475, 0, 0, 196608}};
  s21_decimal d2 = {{42, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{-59985577, -1420881418, 508787611, 1835008}};

  ck_assert_int_eq(0, s21_div(d2, d1, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_11) {  // 4.475 / 4.2
  s21_decimal d1 = {{4475, 0, 0, 196608}};
  s21_decimal d2 = {{42, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1589840945, 957487460, 577595800, 1835008}};

  ck_assert_int_eq(0, s21_div(d1, d2, &ans));        // no error
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));  // check for same value
}
END_TEST

START_TEST(s21_div_12) {  // 4.475 / 0.0
  s21_decimal d1 = {{4475, 0, 0, 196608}};
  s21_decimal d2 = {{0, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(3, s21_div(d1, d2, &ans));  // error
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal d1 = {
      {1987968251, 1845239455, 73291188,
       1835008}};  // 0.135198379581937571938579173851738519837198537918379813759817359813475M
  s21_decimal d2 = {{-1774746752, 630139707, -1911024495,
                     0}};  // 43975982739115728375897359232M
  s21_decimal ans = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_div(d2, d1, &ans));  // error
}
END_TEST
//}

// // // // is_equal
// {
START_TEST(s21_eq_1) {  // +
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_2) {  // -
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_3) {  // -
  s21_decimal d1 = {{0, 1, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_4) {  // +
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_5) {  // -
  s21_decimal d1 = {{1449652029, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_6) {  // . +
  s21_decimal d1 = {{-244589049, 1, 0, 655360}};
  s21_decimal d2 = {{-244589049, 1, 0, 655360}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_7) {  // . -
  s21_decimal d1 = {{-244589049, 1, 0, 655360}};
  s21_decimal d2 = {{-12312, 23423424, 0, 655360}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_8) {  // . + same values (1 and 1.000000)
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1000000, 0, 0, 393216}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_eq_9) {  // . -
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1000010, 0, 0, 393216}};
  int ans = s21_is_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // // is_less
// {
START_TEST(s21_less_1) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_2) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, 0}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_3) {
  s21_decimal d1 = {{0, 1, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_4) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_5) {
  s21_decimal d1 = {{1449652029, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_6) {  // .
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1000000, 0, 0, 393216}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_7) {  // .
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1000100, 0, 0, 393216}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_8) {  // .
  s21_decimal d1 = {{114251, 0, 0, 327680}};
  s21_decimal d2 = {{1142512, 0, 0, 393216}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_less_9) {  // .
  s21_decimal d1 = {{114251, 0, 0, 327680}};
  s21_decimal d2 = {{1142512, 0, 0, 393216}};
  int ans = s21_is_less(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // // is_greater
// {
START_TEST(s21_greater_1) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_greater(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_greater_2) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, 0}};
  int ans = s21_is_greater(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_greater_3) {
  s21_decimal d1 = {{0, 1, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  int ans = s21_is_greater(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_greater_4) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_greater(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_greater_5) {
  s21_decimal d1 = {{1449652029, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_greater(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // // is_not_equal
// {
START_TEST(s21_neq_1) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_not_equal(d1, d2);
  int true_ans = !1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_neq_2) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_not_equal(d1, d2);
  int true_ans = !0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // // is_less_or_equal
// {
START_TEST(s21_leq_1) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_less_or_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_leq_2) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_less_or_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_leq_3) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652029, 1336569152, 1, 0}};
  int ans = s21_is_less_or_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // // is_greater_or_equal
// {
START_TEST(s21_geq_1) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, MINUS}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_greater_or_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_geq_2) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652028, 1336569152, 1, MINUS}};
  int ans = s21_is_greater_or_equal(d1, d2);
  int true_ans = 1;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_geq_3) {
  s21_decimal d1 = {{1449652028, 1336569152, 1, 0}};
  s21_decimal d2 = {{1449652029, 1336569152, 1, 0}};
  int ans = s21_is_greater_or_equal(d1, d2);
  int true_ans = 0;
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// }

// // // from_int_to_decimal
// {
START_TEST(s21_itd_1) {
  int i = 0;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, 0}};
  int code = s21_from_int_to_decimal(i, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_itd_2) {
  int i = 12;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{12, 0, 0, 0}};
  int code = s21_from_int_to_decimal(i, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_itd_3) {
  int i = -23523235;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{23523235, 0, 0, MINUS}};
  int code = s21_from_int_to_decimal(i, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_itd_4) {
  int i = -23523235;
  int code = s21_from_int_to_decimal(i, NULL);

  ck_assert_int_eq(1, code);
}
END_TEST
// }

// // // // // from_decimal_to_int
// {
START_TEST(s21_dti_1) {
  s21_decimal d = {{2345, 0, 0, 65536}};  // cut off the drobnaya chast
  int ans = -1;
  int true_ans = 234;

  ck_assert_int_eq(0, s21_from_decimal_to_int(d, &ans));
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dti_2) {  // error bc too large for int
  s21_decimal d = {{2342, 1351351, 124, 0}};
  int ans = -1;

  ck_assert_int_eq(1, s21_from_decimal_to_int(d, &ans));
}
END_TEST

START_TEST(s21_dti_3) {
  s21_decimal d = {{2345, 0, 0, MINUS}};
  int ans = -1;
  int true_ans = -2345;

  ck_assert_int_eq(0, s21_from_decimal_to_int(d, &ans));
  ck_assert_int_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dti_4) {
  s21_decimal d = {{MAX_INT, 0, 0, 0}};
  int ans = -1;
  int true_ans = MAX_INT;

  ck_assert_int_eq(0, s21_from_decimal_to_int(d, &ans));
  ck_assert_int_eq(ans, true_ans);
}
END_TEST
// // }

// // // // // from_decimal_to_float
// // {
START_TEST(s21_dtf_1) {
  s21_decimal d = {{2345, 0, 0, 65536}};
  float ans = -1.0;
  float true_ans = 234.5;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dtf_2) {
  s21_decimal d = {{2345324, 0, 0, 262144}};
  float ans = -1.0;
  float true_ans = 234.5324;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dtf_3) {
  s21_decimal d = {{2345324, 0, 0, MINUS + 262144}};
  float ans = -1.0;
  float true_ans = -234.5324;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dtf_4) {
  s21_decimal d = {{2345324, 0, 0, MINUS}};
  float ans = -1.0;
  float true_ans = -2345324;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dtf_5) {
  s21_decimal d = {{2345324, 0, 0, 0}};
  float ans = -1.0;
  float true_ans = 2345324;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

START_TEST(s21_dtf_6) {
  s21_decimal d = {{23, 0, 0, 65536}};
  float ans = -1.0;
  float true_ans = 2.3;
  int code = s21_from_decimal_to_float(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_float_eq(ans, true_ans);
}
END_TEST
// // }

// // // // // from_float_to_decimal
// // {
START_TEST(s21_ftd_1) {
  float f = 234.5;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2345, 0, 0, 65536}};
  int code = s21_from_float_to_decimal(f, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ftd_2) {
  float f = -234.65;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{23465, 0, 0, MINUS + 131072}};
  int code = s21_from_float_to_decimal(f, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ftd_3) {
  float f = 2324321.5;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2324322, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ftd_4) {
  float f = 2324321.5;
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2324322, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST
// // }

// // // // // floor
// {
START_TEST(s21_fl_1) {
  s21_decimal d = {{2345, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_2) {
  s21_decimal d = {{2345, 0, 0, -2147418112}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{235, 0, 0, MINUS}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_3) {
  s21_decimal d = {{2345, 0, 0, MINUS}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{2345, 0, 0, MINUS}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_4) {
  s21_decimal d = {{603813279, 54537, 0, -2146697216}};  // -234.235235235231M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{235, 0, 0, -2147483648}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_5) {
  s21_decimal d = {{-1949642954, 0, 0, 458752}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_6) {
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, 0}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_fl_7) {
  s21_decimal d = {{1, 0, 0, -2147418112}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, MINUS}};
  int code = s21_floor(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST
// }

// // // // // round
// {
START_TEST(s21_ro_1) {
  s21_decimal d = {{-1949642954, 0, 0, 458752}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{235, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_2) {
  s21_decimal d = {{2345, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_3) {
  s21_decimal d = {{2344, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_4) {
  s21_decimal d = {{2347, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{235, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_5) {
  s21_decimal d = {{2340, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_6) {
  s21_decimal d = {{234, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_7) {
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_8) {
  s21_decimal d = {{5, 0, 0, 65536}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_9) {
  s21_decimal d = {{51, 0, 0, 131072}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, 0}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_10) {
  s21_decimal d = {{50, 0, 0, -2147352576}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{0, 0, 0, MINUS}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_ro_11) {
  s21_decimal d = {{51, 0, 0, -2147352576}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, MINUS}};
  int code = s21_round(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST
// }

// // // // // truncate
// {
START_TEST(s21_tr_1) {
  s21_decimal d = {{234234242, 0, 0, 393216}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_truncate(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_tr_2) {
  s21_decimal d = {{234000000, 0, 0, 393216}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_truncate(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_tr_3) {
  s21_decimal d = {{234, 0, 0, 0}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, 0}};
  int code = s21_truncate(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_tr_4) {
  s21_decimal d = {{234346, 0, 0, -2147287040}};
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{234, 0, 0, -2147483648}};
  int code = s21_truncate(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_tr_5) {
  s21_decimal d = {{-1223331385, 258700, 0, 983040}};  // 1.111111111111111M
  s21_decimal ans = {{0, 0, 0, 0}};
  s21_decimal true_ans = {{1, 0, 0, 0}};
  int code = s21_truncate(d, &ans);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST
// }

Suite *suite() {
  Suite *s;
  s = suite_create("Decimal");

  TCase *tc_negate;
  tc_negate = tcase_create("s21_negate\n");
  tcase_add_test(tc_negate, s21_negate_1);
  tcase_add_test(tc_negate, s21_negate_2);
  tcase_add_test(tc_negate, s21_negate_3);
  suite_add_tcase(s, tc_negate);

  TCase *tc_add;
  tc_add = tcase_create("\n\ns21_add\n");
  tcase_add_test(tc_add, s21_add_1);
  tcase_add_test(tc_add, s21_add_2);
  tcase_add_test(tc_add, s21_add_3);
  tcase_add_test(tc_add, s21_add_4);
  tcase_add_test(tc_add, s21_add_5);
  tcase_add_test(tc_add, s21_add_6);
  tcase_add_test(tc_add, s21_add_7);
  tcase_add_test(tc_add, s21_add_8);
  tcase_add_test(tc_add, s21_add_9);
  tcase_add_test(tc_add, s21_add_10);
  tcase_add_test(tc_add, s21_add_11);
  tcase_add_test(tc_add, s21_add_12);
  tcase_add_test(tc_add, s21_add_13);
  suite_add_tcase(s, tc_add);

  TCase *tc_sub;
  tc_sub = tcase_create("\n\ns21_sub\n");
  tcase_add_test(tc_sub, s21_sub_1);
  tcase_add_test(tc_sub, s21_sub_2);
  tcase_add_test(tc_sub, s21_sub_3);
  tcase_add_test(tc_sub, s21_sub_4);
  tcase_add_test(tc_sub, s21_sub_5);
  tcase_add_test(tc_sub, s21_sub_6);
  tcase_add_test(tc_sub, s21_sub_7);
  tcase_add_test(tc_sub, s21_sub_8);
  tcase_add_test(tc_sub, s21_sub_9);
  tcase_add_test(tc_sub, s21_sub_10);
  tcase_add_test(tc_sub, s21_sub_11);
  tcase_add_test(tc_sub, s21_sub_12);
  tcase_add_test(tc_sub, s21_sub_13);
  tcase_add_test(tc_sub, s21_sub_14);
  tcase_add_test(tc_sub, s21_sub_15);
  tcase_add_test(tc_sub, s21_sub_16);
  tcase_add_test(tc_sub, s21_sub_17);
  tcase_add_test(tc_sub, s21_sub_18);
  tcase_add_test(tc_sub, s21_sub_19);
  tcase_add_test(tc_sub, s21_sub_20);
  suite_add_tcase(s, tc_sub);

  TCase *tc_mul;
  tc_mul = tcase_create("\n\ns21_mul\n");
  tcase_add_test(tc_mul, s21_mul_1);
  tcase_add_test(tc_mul, s21_mul_2);
  tcase_add_test(tc_mul, s21_mul_3);
  tcase_add_test(tc_mul, s21_mul_4);
  tcase_add_test(tc_mul, s21_mul_5);
  tcase_add_test(tc_mul, s21_mul_6);
  tcase_add_test(tc_mul, s21_mul_7);
  tcase_add_test(tc_mul, s21_mul_8);
  tcase_add_test(tc_mul, s21_mul_9);
  tcase_add_test(tc_mul, s21_mul_10);
  tcase_add_test(tc_mul, s21_mul_11);
  suite_add_tcase(s, tc_mul);

  TCase *tc_div;
  tc_div = tcase_create("\n\ns21_div\n");
  tcase_add_test(tc_div, s21_div_1);
  tcase_add_test(tc_div, s21_div_2);
  tcase_add_test(tc_div, s21_div_3);
  tcase_add_test(tc_div, s21_div_4);
  tcase_add_test(tc_div, s21_div_5);
  tcase_add_test(tc_div, s21_div_6);
  tcase_add_test(tc_div, s21_div_7);
  tcase_add_test(tc_div, s21_div_8);
  tcase_add_test(tc_div, s21_div_9);
  tcase_add_test(tc_div, s21_div_10);
  tcase_add_test(tc_div, s21_div_11);
  tcase_add_test(tc_div, s21_div_12);
  tcase_add_test(tc_div, s21_div_13);
  suite_add_tcase(s, tc_div);

  TCase *tc_eq;
  tc_eq = tcase_create("\n\nis equal\n");
  tcase_add_test(tc_eq, s21_eq_1);
  tcase_add_test(tc_eq, s21_eq_2);
  tcase_add_test(tc_eq, s21_eq_3);
  tcase_add_test(tc_eq, s21_eq_4);
  tcase_add_test(tc_eq, s21_eq_5);
  tcase_add_test(tc_eq, s21_eq_6);
  tcase_add_test(tc_eq, s21_eq_7);
  tcase_add_test(tc_eq, s21_eq_8);
  tcase_add_test(tc_eq, s21_eq_9);
  suite_add_tcase(s, tc_eq);

  TCase *tc_less;
  tc_less = tcase_create("\n\nis less\n");
  tcase_add_test(tc_less, s21_less_1);
  tcase_add_test(tc_less, s21_less_2);
  tcase_add_test(tc_less, s21_less_3);
  tcase_add_test(tc_less, s21_less_4);
  tcase_add_test(tc_less, s21_less_5);
  tcase_add_test(tc_less, s21_less_6);
  tcase_add_test(tc_less, s21_less_7);
  tcase_add_test(tc_less, s21_less_8);
  tcase_add_test(tc_less, s21_less_9);
  suite_add_tcase(s, tc_less);

  TCase *tc_greater;
  tc_greater = tcase_create("\n\nis greater\n");
  tcase_add_test(tc_greater, s21_greater_1);
  tcase_add_test(tc_greater, s21_greater_2);
  tcase_add_test(tc_greater, s21_greater_3);
  tcase_add_test(tc_greater, s21_greater_4);
  tcase_add_test(tc_greater, s21_greater_5);
  suite_add_tcase(s, tc_greater);

  TCase *tc_leq;
  tc_leq = tcase_create("\n\nis less or equal\n");
  tcase_add_test(tc_leq, s21_leq_1);
  tcase_add_test(tc_leq, s21_leq_2);
  tcase_add_test(tc_leq, s21_leq_3);
  suite_add_tcase(s, tc_leq);

  TCase *tc_geq;
  tc_geq = tcase_create("\n\nis greater or equal\n");
  tcase_add_test(tc_geq, s21_geq_1);
  tcase_add_test(tc_geq, s21_geq_2);
  tcase_add_test(tc_geq, s21_geq_3);
  suite_add_tcase(s, tc_geq);

  TCase *tc_neq;
  tc_neq = tcase_create("\n\nis not equal\n");
  tcase_add_test(tc_neq, s21_neq_1);
  tcase_add_test(tc_neq, s21_neq_2);
  suite_add_tcase(s, tc_neq);

  TCase *tc_itd;
  tc_itd = tcase_create("\n\nint to decimal\n");
  tcase_add_test(tc_itd, s21_itd_1);
  tcase_add_test(tc_itd, s21_itd_2);
  tcase_add_test(tc_itd, s21_itd_3);
  tcase_add_test(tc_itd, s21_itd_4);
  suite_add_tcase(s, tc_itd);

  TCase *tc_dti;
  tc_dti = tcase_create("\n\ndecimal to int\n");
  tcase_add_test(tc_dti, s21_dti_1);
  tcase_add_test(tc_dti, s21_dti_2);
  tcase_add_test(tc_dti, s21_dti_3);
  tcase_add_test(tc_dti, s21_dti_4);
  suite_add_tcase(s, tc_dti);

  TCase *tc_dtf;
  tc_dtf = tcase_create("\n\ndecimal to float\n");
  tcase_add_test(tc_dtf, s21_dtf_1);
  tcase_add_test(tc_dtf, s21_dtf_2);
  tcase_add_test(tc_dtf, s21_dtf_3);
  tcase_add_test(tc_dtf, s21_dtf_4);
  tcase_add_test(tc_dtf, s21_dtf_5);
  tcase_add_test(tc_dtf, s21_dtf_6);
  suite_add_tcase(s, tc_dtf);

  TCase *tc_ftd;
  tc_ftd = tcase_create("\n\nfloat to decimal\n");
  tcase_add_test(tc_ftd, s21_ftd_1);
  tcase_add_test(tc_ftd, s21_ftd_2);
  tcase_add_test(tc_ftd, s21_ftd_3);
  tcase_add_test(tc_ftd, s21_ftd_4);
  suite_add_tcase(s, tc_ftd);

  TCase *tc_fl;
  tc_fl = tcase_create("\n\nfloor\n");
  tcase_add_test(tc_fl, s21_fl_1);
  tcase_add_test(tc_fl, s21_fl_2);
  tcase_add_test(tc_fl, s21_fl_3);
  tcase_add_test(tc_fl, s21_fl_4);
  tcase_add_test(tc_fl, s21_fl_5);
  tcase_add_test(tc_fl, s21_fl_6);
  tcase_add_test(tc_fl, s21_fl_7);
  suite_add_tcase(s, tc_fl);

  TCase *tc_ro;
  tc_ro = tcase_create("\n\nround\n");
  tcase_add_test(tc_ro, s21_ro_1);
  tcase_add_test(tc_ro, s21_ro_2);
  tcase_add_test(tc_ro, s21_ro_3);
  tcase_add_test(tc_ro, s21_ro_4);
  tcase_add_test(tc_ro, s21_ro_5);
  tcase_add_test(tc_ro, s21_ro_6);
  tcase_add_test(tc_ro, s21_ro_7);
  tcase_add_test(tc_ro, s21_ro_8);
  tcase_add_test(tc_ro, s21_ro_9);
  tcase_add_test(tc_ro, s21_ro_10);
  tcase_add_test(tc_ro, s21_ro_11);
  suite_add_tcase(s, tc_ro);

  TCase *tc_tr;
  tc_tr = tcase_create("\n\ntruncate\n");
  tcase_add_test(tc_tr, s21_tr_1);
  tcase_add_test(tc_tr, s21_tr_2);
  tcase_add_test(tc_tr, s21_tr_3);
  tcase_add_test(tc_tr, s21_tr_4);
  tcase_add_test(tc_tr, s21_tr_5);
  suite_add_tcase(s, tc_tr);

  return s;
}

int main() {
  int success = 0;
  Suite *s;
  SRunner *runner;
  s = suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  success = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (success == 0);
}
