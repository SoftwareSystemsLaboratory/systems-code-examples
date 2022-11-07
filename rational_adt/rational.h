#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <stdio.h>
#include <stdbool.h>

// {{OSSP:header-typedef:begin}}
typedef struct
{
    long num;
    long den;
    bool valid;
} rational_t;

typedef struct
{
    long comparison; // boolean for type of condition
    bool valid; // whether valid (arising from overflow, etc.)
} rational_comparison_t;
// {{OSSP:header-typedef:end}}

// {{OSSP:header-basic-init:begin}}
extern void rational_init(rational_t *n,
                          long num,
                          long den);
// {{OSSP:header-basic-init:end}}

// {{OSSP:header-advanced-init:begin}}
extern void rational_from_rational(rational_t *number, rational_t *another);

extern void rational_from_long(rational_t *number, long whole_number);
// {{OSSP:header-advanced-init:end}}

// {{OSSP:header-accessors:begin}}
extern long rational_numerator(rational_t *number);

extern long rational_denominator(rational_t *number);
// {{OSSP:header-accessors:end}}

// {{OSSP:header-arithmetic:begin}}
extern void rational_add(rational_t *n1,
                         rational_t *n2,
                         rational_t *result);

extern void rational_subtract(rational_t *n1,
                              rational_t *n2,
                              rational_t *result);

extern void rational_multiply(rational_t *n1,
                              rational_t *n2,
                              rational_t *result);

extern void rational_divide(rational_t *n1,
                            rational_t *n2,
                            rational_t *result);
// {{OSSP:header-arithmetic:end}}

// {{OSSP:header-unary-inplace:begin}}
extern void rational_negate(rational_t *number);

extern void rational_reciprocal(rational_t *number);
// {{OSSP:header-unary-inplace:end}}

// {{OSSP:header-compare:begin}}
extern long rational_compare(rational_t *n1,
                             rational_t *n2,
                             rational_comparison_t *result);
// {{OSSP:header-compare:end}}

// {{OSSP:header-print:begin}}
extern void rational_print(rational_t *number,
                           FILE *stream,
                           bool add_newline);
// {{OSSP:header-print:end}}

// {{OSSP:header-utililties:begin}}
extern long long_add(long a, long b, long *c);

extern long long_multiply(long a, long b, long *c);

extern long long_subtract(long a, long b, long *c);
// {{OSSP:header-utililties:end}}


// {{OSSP:header-rational_static_interfaces:begin}}

extern void reduce_fraction(rational_t *number);

extern long long_gcd(long a, long b);
// {{OSSP:header-rational_static_interfaces:end}}

// {{OSSP:header-allocate:begin}}
extern rational_t *rational_allocate();
// {{OSSP:header-allocate:end}}

#endif
