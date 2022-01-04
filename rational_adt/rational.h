#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <stdio.h>

typedef struct {
  long numerator;
  long denominator;
} rational_t;

// most common initialization [construction]
extern void rational_init(rational_t* number, long numerator, long denominator);

// initialize from another rational_t [like copy constructor]
extern void rational_from_rational(rational_t* number, rational_t* another);

// initialize from a whole number [similar to general initialization with implicit/default denominator of 1]
extern void rational_from_long(rational_t* number, long whole_number);

// accessors [in the Java sense]
extern long rational_numerator(rational_t* number);
extern long rational_denominator(rational_t* number);

// core arithmetic operations [non-destructive]
extern void rational_add(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_subtract(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_multiply(rational_t* n1, rational_t* n2, rational_t* result);
extern void rational_divide(rational_t* n1, rational_t* n2, rational_t* result);

// in-place operations
extern void rational_negate(rational_t* number);
extern void rational_reciprocal(rational_t* number);

// relational operator(s)
extern long rational_compare(rational_t* n1, rational_t* n2);

// convenience functions
extern int rational_lt(rational_t* n1, rational_t* n2);
extern int rational_gt(rational_t* n1, rational_t* n2);
extern int rational_ge(rational_t* n1, rational_t* n2);
extern int rational_le(rational_t* n1, rational_t* n2);
extern int rational_eq(rational_t* n1, rational_t* n2);

// output to stream
extern void rational_print(rational_t* number, FILE* stream, int nl);

// Allocate an instance dynamically.

extern rational_t* rational_allocate();

#endif
