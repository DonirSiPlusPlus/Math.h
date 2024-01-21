#include "s21_math.h"

int s21_abs(int x) { return x < 0 ? -x : x; }

long double s21_fabs(double x) {
  return x < FLOAT_NULL ? (long double)-x : (long double)x;
}

long double s21_ceil(double x) {
  if (x == s21_INF || x == -s21_INF) {
    x = (x == s21_INF ? s21_INF : -s21_INF);
  } else if (x != x) {
    x = s21_NAN;
  } else {
    long long int_x = (long long)x;
    if (x > 0.0 && x != int_x) int_x++;
    if (x >= LLONG_MIN && x <= LLONG_MAX) x = int_x;
  }
  return x;
}

long double s21_floor(double x) {
  if (x == s21_INF || x == -s21_INF) {
    x = (x == s21_INF ? s21_INF : -s21_INF);
  } else if (x != x) {
    x = s21_NAN;
  } else {
    long long int_x = (long long)x;
    if (x < 0.0 && x != int_x) int_x--;
    if (x >= LLONG_MIN && x <= LLONG_MAX) x = int_x;
  }
  return x;
}

long double s21_fmod(double x, double y) {
  if (x != x || y != y || y == 0 || x == s21_INF || x == -s21_INF) {
    x = s21_NAN;
  } else if (y != s21_INF && y != -s21_INF) {
    y = s21_fabs(y);
    double tmp = y;
    for (int i = 2; tmp <= s21_fabs(x); i++) {
      tmp = s21_fabs(y);
      tmp *= i;
    }
    x = (x > 0.0 ? x - (tmp - y) : x + tmp - y);
  }
  return x;
}

long double s21_exp(double x) {
  double sum = 1;
  if (x != x) {
    sum = s21_NAN;
  } else if (x == -s21_INF) {
    sum = 0.000000;
  } else if (x == s21_INF) {
    sum = s21_INF;
  } else {
    double chlen = 1;
    if (x < MIN_E) {
      sum = 0.0000000;
    } else {
      for (unsigned n = 1;; n++) {
        if (chlen > -s21_EPS && chlen < s21_EPS) break;
        chlen *= x / n;
        sum += chlen;
        if (sum >= __DBL_MAX__) {
          sum = s21_INF;
          break;
        }
      }
    }
  }
  return sum;
}

long double s21_log(double x) {
  long double sum = 0;
  if (x < 0.0 || x != x || x == -s21_INF) {
    sum = s21_NAN;
  } else if (x == 0) {
    sum = -s21_INF;
  } else if (x == s21_INF) {
    sum = s21_INF;
  } else {
    unsigned mantis = 0;
    if (x < 1) {
      while (x <= 1) {
        x *= 10;
        mantis++;
      }
    }
    if (!mantis) {
      sum += s21_log_decompos(&x, &sum);
      sum += s21_log_form(x);
    } else {
      sum += s21_log_decompos(&x, &sum) + s21_log_form(x) - (mantis * ln_10);
    }
  }
  return sum;
}

unsigned s21_log_decompos(double *x, long double *sum) {
  unsigned step_e = 0;
  for (; *x >= s21_E; *x /= s21_E) {
    if (*x == (long long)*x && *x > 5 && step_e != 0) {
      while (*x > 2) {
        *sum += ln_2;
        *x /= 2;
      }
      break;
    }
    step_e++;
  }
  if (*x > 2) {
    *x /= 2;
    *sum += ln_2;
  }
  return step_e;
}

long double s21_log_form(double x) {
  long double sum = 0;
  x--;
  if (x == 1.0) {
    sum += ln_2;
  } else {
    long double chlen = 1, chisl = -1;
    for (unsigned n = 1;; n++) {
      if (chlen > -s21_EPS && chlen < s21_EPS) break;
      chisl *= (-1) * x;
      chlen = chisl / n;
      sum += chlen;
    }
  }
  return sum;
}

long double s21_sqrt(double x) {
  long double root = x;
  if (x != x || x == -s21_INF || x < 0) {
    root = s21_NAN;
  } else if (x == s21_INF) {
    root = s21_INF;
  } else if (!x) {
    root = 0;
  } else {
    for (unsigned n = 0; n < 50; n++) {
      if (root < 1e-8) break;
      root = (root + x / root) / 2;
    }
  }
  return root;
}

long double s21_sin(double x) {
  long double result;
  if (x != x || x == s21_INF || x == -s21_INF) {
    result = s21_NAN;
  } else {
    short sign = 1;
    if (x < 0) {
      sign = -1;
      x = -x;
    }
    x = s21_fmod(x, s21_PI * 2);  // берём значение на кругу
    long double chlen = x;
    result = x;
    for (int n = 1; n < 100; n++) {
      chlen *= (-1 * x * x) / ((2 * n) * (2 * n + 1));
      result += chlen;
    }
    result *= sign;
  }
  return result;
}

long double s21_tan(double x) {
  long double tan = x;
  if (x == s21_PI / 2) {
    tan = 16331239353195370L;
  } else if (x == -s21_PI / 2) {
    tan = -16331239353195370L;
  } else if (!x) {
    tan = 0.000000;
  } else {
    tan = s21_sin(x) / s21_cos(x);
  }
  return tan;
}

long double s21_atan(double x) {
  long double y;
  if (x != x) {
    y = -s21_NAN;
  } else if (x == s21_INF) {
    y = s21_PI_2;
  } else if (x == -s21_INF) {
    y = -s21_PI_2;
  } else {
    long double dx;
    long double s21_abs;
    int n = 1;
    int flag = 0;
    int flag_neg = 0;
    if (x < 0) {
      flag_neg++;
      x = -x;
    }
    if (x > 1) {
      x = 1 / x;
      flag++;
    }
    dx = x;
    y = x;
    s21_abs = x;
    if (x != 1) {
      while (s21_abs > 0.000000000000001) {
        ++n;
        dx *= -x * x * (2 * n - 3) / (2 * n - 1);
        y += dx;
        if (dx < 0) {
          s21_abs *= -dx;
        } else {
          s21_abs = dx;
        }
      }
    } else {
      y = s21_PI_2 / 2;
    }
    if (flag) {
      y = s21_PI_2 - y;
    }
    if (flag_neg) {
      y = -y;
    }
  }
  return y;
}

long double s21_acos(double x) {
  long double acos = 0.0;
  acos = s21_PI / 2 - s21_asin(x);
  return acos;
}

long double s21_cos(double x) {
  long double cost = 0;
  if (x != x || x == s21_INF || x == -s21_INF) {
    cost = s21_NAN;
  } else {
    x = s21_fmod(x, 2 * s21_PI);
    if (x < 0) {
      x = 2 * s21_PI + x;
    }
    long double chlen = 1;
    for (int n = 1; n < 100; n++) {
      cost += chlen;
      chlen *= (-1 * x * x) / (2 * n * (2 * n - 1));
    }
  }
  return cost;
}

long double s21_asin(double x) {
  long double y = 0.0;
  if (x != x || x > 1.0 || x < -1.0) {
    y = s21_NAN;
  } else if (x == 1) {
    y = s21_PI_2;
  } else if (x == -1) {
    y = -s21_PI_2;
  } else {
    y = s21_atan(x / s21_sqrt(1 - x * x));
  }
  return y;
}

long double s21_pow(double base, double exp) {
  double ret = base;
  if (exp == 0 || base == 1) {
    ret = 1;
  } else if (base != base || exp != exp) {
    ret = s21_NAN;
  } else if (exp == -s21_INF) {
    if (base > -1 && base < 1) {
      ret = s21_INF;
    } else if (base == -1) {
      ret = 1;
    } else {
      ret = 0.0000000;
    }
  } else if (exp == s21_INF) {
    if (base > -1 && base < 1) {
      ret = 0.0000000;
    } else if (base == -1) {
      ret = 1;
    } else {
      ret = s21_INF;
    }
  } else if (base == -s21_INF && exp < 0) {
    ret = -0.00000000000000000000000000001;
  } else if (base < 0 && exp - s21_floor(exp) != 0) {
    ret = s21_NAN;
  } else {
    double multi = exp * s21_log((s21_fabs(base)));
    if ((base < 0 && exp - s21_floor(exp) == 0 && s21_fmod(exp, 2) == 1) ||
        (base < 0 && exp < 0 && s21_fmod(-exp, 2) == 1)) {
      ret = -s21_exp(multi);
    } else {
      ret = s21_exp(multi);
    }
  }
  return ret;
}
