#ifndef SRC_S21_MATH_H_  //  SRC_S21_MATH_H_
#define SRC_S21_MATH_H_  //  SRC_S21_MATH_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define s21_INF 1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define s21_E 2.71828182845904523536028747135266250
#define s21_PI 3.14159265358979323846264338327950288
#define s21_PI_2 \
  1.5707963267948966192313216916397514420985846996875529104874722961
#define FLOAT_NULL 0.000000000000001L
#define s21_EPS 1e-30
#define MIN_E -14.50865773852421991
#define ln_10 2.30258509299404568401799145468436421
#define ln_2 0.693147180559945309417232121458176568

int s21_abs(int x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_fabs(double x);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_log_form(double x);
unsigned s21_log_decompos(double *x, long double *sum);
long double s21_sqrt(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);

#endif  // SRC_S21_MATH_H_
