#include <math.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "rational.h"

/* internal functions */
static void reduce_fraction(rational_t* number);
static long long_gcd(long a, long b);

rational_t* rational_allocate() {
  return (rational_t*) malloc(sizeof(rational_t));
}

void rational_init(rational_t* number, long numerator, long denominator) {
  assert(denominator != 0);
  number->numerator = numerator;
  number->denominator = denominator;
  reduce_fraction(number);
}

void rational_from_rational(rational_t* number, rational_t* another) {
  number->numerator = another->numerator;
  number->denominator = another->denominator;
  reduce_fraction(number);
}

void rational_from_long(rational_t* number, long whole_number) {
  number->numerator = whole_number;
  number->denominator = 1L;
  reduce_fraction(number);
}

void rational_print(rational_t* number, FILE* stream, int nl) {
  fprintf(stream, "%ld/%ld", number->numerator, number->denominator);
  if (nl) fprintf(stream, "\n");
}

/* keep as self-contained as possible */
static long long_gcd(long a, long b)
{
   // assume a or b is not 0 ; make into C assertion
   assert(a != 0 || b != 0);

   if (b == 0) {
      return labs(a);
   } else {
      return long_gcd(b, a % b);
   }
}

static void reduce_fraction(rational_t* number) {
   assert(number->denominator != 0);
   long common_divisor = long_gcd(number->numerator, number->denominator);
   number->numerator /= common_divisor;
   number->denominator /= common_divisor;
   if (number->denominator < 0) {
      number->denominator = -number->denominator;
      number->numerator = -number->numerator;
   }
}

long rational_numerator(rational_t* number) {
  return number->numerator;
}

long rational_denominator(rational_t* number) {
  return number->denominator;
}

void rational_add(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result,
      n1->numerator * n2->denominator + n1->denominator * n2->numerator,
      n1->denominator * n2->denominator);
}

void rational_subtract(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result,
      n1->numerator * n2->denominator - n1->denominator * n2->numerator,
      n1->denominator * n2->denominator);
}


void rational_multiply(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result, n1->numerator * n2->numerator,
      n1->denominator * n2->denominator);
}

void rational_divide(rational_t* n1, rational_t* n2, rational_t* result) {
  rational_init(result, n1->numerator * n2->denominator,
      n1->denominator * n2->numerator);
}

long rational_compare(rational_t* n1, rational_t* n2) {
  return n1->numerator * n2->denominator - n2->numerator * n1->denominator;
}

int rational_gt(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) > 0;
}

int rational_lt(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) < 0;
}

int rational_eq(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) == 0;
}

int rational_ge(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) >= 0;
}

int rational_le(rational_t* n1, rational_t* n2) {
  return rational_compare(n1,n2) <= 0;
}

void rational_reciprocal(rational_t* number) {
  long numerator = number->numerator;
  long denominator = number->denominator;
  number->numerator = denominator;
  number->denominator = numerator;
}

void rational_negate(rational_t* number) {
  number->numerator = -number->numerator;
}
