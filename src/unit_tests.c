#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "stack.h"

START_TEST(calc_1) {
  char str[50] = "(1+1-2/2.3*(3%1)-4^2)*0";
  double in = 0, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_2) {
  char str[50] = "sin(cos(5-3))*2-sqrt(5)-tan(2)";
  double in = -0.859506, out = 0;
  int err = 0;
  solv(str, &err, &out);

  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_3) {
  char str[50] = "asin(-1)/2-atan(3)+3(2-4(2-ln(3)))";
  double in = -6.8510964, out = 0;
  int err = 0;
  solv(str, &err, &out);

  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_4) {
  char str[50] = "-3";
  double in = -3, out = 0;
  int err = 0;
  solv(str, &err, &out);

  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_5) {
  char str[50] = "1/0";
  double out = 0;
  int err = 0;
  solv(str, &err, &out);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(calc_6) {
  char str[50] = "(0.00001+2.3333-((23-3.1-1/2)-(34+2)))";
  double in = 18.93331, out = 0;
  int err = 0;
  solv(str, &err, &out);

  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST
START_TEST(calc_7) {
  char str[200] = "(1.23456789+0.00000001-((23-3.14-0.5)-(34.56789+2.01)))*2";
  double expected_output = 36.9049158;
  double output = 0;
  int error = 0;
  solv(str, &error, &output);
  ck_assert_msg(fabs(output - expected_output) < 0.00001,
                "Expected output %lf, but got %lf", expected_output, output);
}
END_TEST

START_TEST(calc_8) {
  char str[50] = "1+2*3/4-5^2";
  double in = -22.5, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_9) {
  char str[50] = "sin(0.5*3.1415)-cos(0.5*3.1415)";
  double in = 0.999953672132, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_10) {
  char str[50] = "log(2.7)";
  double in = 0.4313637641589874, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_11) {
  char str[50] = "log(100)";
  double in = 2, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_12) {
  char str[50] = "sqrt(25)";
  double in = 5, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
END_TEST

START_TEST(calc_13) {
  char str[50] = "ln(10)";
  double in = 2.3025850929940457, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_14) {
  char str[50] = "0.0+0.0-0.0-0";
  double in = 0, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_15) {
  char str[50] = "1^2-1";
  double in = 0, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_16) {
  char str[50] = "25^2";
  double in = 625, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 1e-6);
}
START_TEST(calc_17) {
  char str[50] = "-(-1^3)";
  double in = 1, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}

START_TEST(calc_19) {
  char str[50] = "sqrt(2)";
  double in = 1.414213562373095, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_20) {
  char str[50] = "sqrt(1)";
  double in = 1, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_21) {
  char str[50] = "((2+2)-(2+2)-(2+2)-(2+2)-(2+2))";
  double in = -12, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_22) {
  char str[50] = "sin(2)-1/2";
  double in = 0.409297426826, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_23) {
  char str[50] = "(0.1)^10";
  double in = 0, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_24) {
  char str[50] = "1/(-1)";
  double in = -1, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_25) {
  char str[50] = "acos(0.2)";
  double in = 1.369438406005, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_26) {
  char str[50] = "2^2^3";
  double in = 64, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_27) {
  char str[50] = "10^0";
  double in = 1, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_28) {
  char str[50] = "sqrt(-1)";
  double out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_nan(out);
}
START_TEST(calc_29) {
  char str[50] = "-(-1)^2";
  double in = -1, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}
START_TEST(calc_30) {
  char str[50] = "2^20";
  double in = 1048576, out = 0;
  int err = 0;
  solv(str, &err, &out);
  ck_assert_double_eq_tol(in, out, 0.00001);
}

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, calc_1);
  tcase_add_test(tc, calc_2);
  tcase_add_test(tc, calc_3);
  tcase_add_test(tc, calc_4);
  tcase_add_test(tc, calc_5);
  tcase_add_test(tc, calc_6);
  tcase_add_test(tc, calc_7);
  tcase_add_test(tc, calc_8);
  tcase_add_test(tc, calc_9);
  tcase_add_test(tc, calc_10);
  tcase_add_test(tc, calc_11);
  tcase_add_test(tc, calc_12);
  tcase_add_test(tc, calc_13);
  tcase_add_test(tc, calc_14);
  tcase_add_test(tc, calc_15);
  tcase_add_test(tc, calc_16);
  tcase_add_test(tc, calc_17);

  tcase_add_test(tc, calc_19);
  tcase_add_test(tc, calc_20);
  tcase_add_test(tc, calc_21);
  tcase_add_test(tc, calc_22);
  tcase_add_test(tc, calc_23);
  tcase_add_test(tc, calc_24);
  tcase_add_test(tc, calc_25);
  tcase_add_test(tc, calc_26);
  tcase_add_test(tc, calc_26);
  tcase_add_test(tc, calc_27);
  tcase_add_test(tc, calc_28);
  tcase_add_test(tc, calc_29);
  tcase_add_test(tc, calc_30);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  setlocale(LC_ALL, "");
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = suite_insert();
  sr = srunner_create(s1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  nf = 0;
  srunner_free(sr);
  return nf;
}