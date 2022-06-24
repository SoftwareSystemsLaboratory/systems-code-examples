#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <stdio.h>

/* header:typedef */
typedef struct {
    long numerator;
    long denominator;
    int valid;
} rational_t;

typedef struct {
    long comparison; /* boolean for type of condition */
    int valid; /* whether valid (arising from overflow, etc.) */
} rational_comparison_t;

/* header:basic-init */
extern void rational_init(rational_t *number, long numerator, long denominator);

/* header:advanced-init */
extern void rational_from_rational(rational_t *number, rational_t *another);

extern void rational_from_long(rational_t *number, long whole_number);

/* header:accessors */
extern long rational_numerator(rational_t *number);

extern long rational_denominator(rational_t *number);

/* header:arithmetic */
extern void rational_add(rational_t *n1, rational_t *n2, rational_t *result);

extern void rational_subtract(rational_t *n1, rational_t *n2, rational_t *result);

extern void rational_multiply(rational_t *n1, rational_t *n2, rational_t *result);

extern void rational_divide(rational_t *n1, rational_t *n2, rational_t *result);

/* header:unary-inplace */
extern void rational_negate(rational_t *number);

extern void rational_reciprocal(rational_t *number);

/* header:compare */
extern long rational_compare(rational_t *n1, rational_t *n2, rational_comparison_t *result);

/* header:print */
extern void rational_print(rational_t *number, FILE *stream, int nl);

/* header:utililties */

extern long long_add(long a, long b, long *c);

extern long long_multiply(long a, long b, long *c);

extern long long_subtract(long a, long b, long *c);

/* header:rational_static_interfaces */

extern void reduce_fraction(rational_t *number);

extern long long_gcd(long a, long b);

/* header:allocate */
extern rational_t *rational_allocate();

#endif
