#include <math.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "rational.h"
#include "lwlog.h"

#define LOG_COLOR (1)
#define LOG_LEVEL (7)

/* rational_c:rational_static_interfaces */

static void reduce_fraction(rational_t* number);

static long long_gcd(long a, long b);

/* rational_c:rational_allocate */

rational_t* rational_allocate() {
  return (rational_t*) malloc(sizeof(rational_t));
}

/* rational_c:rational_init */

void rational_init(rational_t* number, long numerator, long denominator) {
  number->numerator = numerator;
  number->denominator = denominator;
  reduce_fraction(number);
}

/* rational_c:rational_from_rational */

void rational_from_rational(rational_t* number, rational_t* another) {
  number->numerator = another->numerator;
  number->denominator = another->denominator;
  reduce_fraction(number);
}

/* rational_c:rational_from_long */

void rational_from_long(rational_t* number, long whole_number) {
  number->numerator = whole_number;
  number->denominator = 1L;
  reduce_fraction(number);
}

/* rational_c:rational_print */

void rational_print(rational_t* number, FILE* stream, int nl) {
  fprintf(stream, "%ld/%ld", number->numerator, number->denominator);
  if (nl) fprintf(stream, "\n");
}

/* rational_c:long_gcd */

static long long_gcd(long a, long b)
{
   if (a == 0 && b == 0) {
     lwlog_err("Either a (== %d) or b (== %d) must be non-zero", a, b);
     return 0;
   }

   if (b == 0) {
      return labs(a);
   } else {
      return long_gcd(b, a % b);
   }
}

/* rational_c:reduce_fraction */

static void reduce_fraction(rational_t* number) {
   long common_divisor = long_gcd(number->numerator, number->denominator);
   if (common_divisor == 0)
     return;
   number->numerator /= common_divisor;
   number->denominator /= common_divisor;
   if (number->denominator < 0) {
      number->denominator = -number->denominator;
      number->numerator = -number->numerator;
   }
}

/* rational_c:rational_numerator */

long rational_numerator(rational_t* number) {
  return number->numerator;
}

/* rational_c:rational_denominator */

long rational_denominator(rational_t* number) {
  return number->denominator;
}

/* rational_c:rational_add */

void rational_add(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result,
      n1->numerator * n2->denominator + n1->denominator * n2->numerator,
      n1->denominator * n2->denominator);
}

/* rational_c:rational_subtract */

void rational_subtract(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result,
      n1->numerator * n2->denominator - n1->denominator * n2->numerator,
      n1->denominator * n2->denominator);
}


/* rational_c:rational_multiply */

void rational_multiply(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result, n1->numerator * n2->numerator,
      n1->denominator * n2->denominator);
}

/* rational_c:rational_divide */

void rational_divide(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result, n1->numerator * n2->denominator,
      n1->denominator * n2->numerator);
}

/* rational_c:rational_compare */

long rational_compare(rational_t* n1, rational_t* n2) {
  return n1->numerator * n2->denominator - n2->numerator * n1->denominator;
}

/* rational_c:rational_gt */

int rational_gt(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) > 0;
}

/* rational_c:rational_lt */

int rational_lt(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) < 0;
}

/* rational_c:rational_eq */

int rational_eq(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) == 0;
}

/* rational_c:rational_ge */

int rational_ge(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) >= 0;
}

/* rational_c:rational_le */

int rational_le(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) <= 0;
}

/* rational_c:rational_reciprocal */

void rational_reciprocal(rational_t* number) {
  long numerator = number->numerator;
  long denominator = number->denominator;
  number->numerator = denominator;
  number->denominator = numerator;
}

/* rational_c:rational_negate */

void rational_negate(rational_t* number) {
  number->numerator = -number->numerator;
}
