#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <stdio.h>

typedef struct {
  long numerator;
  long denominator;
} rational_t;

extern rational_t* rational_allocate();
extern void rational_init(rational_t* number, long numerator, long denominator);
extern void rational_from_rational(rational_t* number, rational_t* another);
extern void rational_from_long(rational_t* number, long whole_number);
extern long rational_numerator(rational_t* number);
extern long rational_denominator(rational_t* number);
extern void rational_add(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_subtract(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_multiply(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_divide(rational_t* n1, rational_t* n2, rational_t* result);
extern long rational_compare(rational_t* n1, rational_t* n2);
extern void rational_print(rational_t* number, FILE* stream, int nl);
extern void rational_negate(rational_t* number);
extern void rational_reciprocal(rational_t* number);

#endif
