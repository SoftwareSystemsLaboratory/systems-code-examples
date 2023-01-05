#include <math.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "rational.h"
#include "lwlog.h"

#define LOG_COLOR (1)
#define LOG_LEVEL (7)

// {{OSSP:module-overflow-helpers:begin}}
inline long long_add(long a, long b, long *c)
{
    return __builtin_saddl_overflow(a, b, c) == 0;
}

inline long long_multiply(long a, long b, long *c)
{
    return __builtin_smull_overflow(a, b, c) == 0;
}

inline long long_subtract(long a, long b, long *c)
{
    return __builtin_ssubl_overflow(a, b, c) == 0;
}
// {{OSSP:module-overflow-helpers:end}}


// {{OSSP:module-statics:begin}}
static void rational_internal_init(rational_t *number,
                                   long num,
                                   long den,
                                   bool valid);
// {{OSSP:module-statics:end}}


// {{OSSP:module-rational_allocate:begin}}
rational_t *rational_allocate()
{
    return (rational_t *) malloc(sizeof(rational_t));
}
// {{OSSP:module-rational_allocate:end}}


// {{OSSP:module-rational_init:begin}}
void rational_init(rational_t *n,
                   long num,
                   long den)
{
    rational_internal_init(n, num, den, true);
}
// {{OSSP:module-rational_init:end}}


// {{OSSP:module-rational_internal_init:begin}}
static void rational_internal_init(rational_t *number,
                                   long num,
                                   long den,
                                   bool valid)
{
    number->num = num;
    number->den = den;
    number->valid = valid;
    if (den == 0)
        number->valid = false;
    reduce_fraction(number);
}
// {{OSSP:module-rational_internal_init:end}}


// {{OSSP:module-rational_from_rational:begin}}
void rational_from_rational(rational_t *number,
                            rational_t *another)
{
    rational_internal_init(number,
                           another->num,
                           another->den,
                           true);
}
// {{OSSP:module-rational_from_rational:end}}


// {{OSSP:module-rational_from_long:begin}}
void rational_from_long(rational_t *number,
                        long whole_number)
{
    rational_internal_init(number,
                           whole_number,
                           1L,
                           true);
}
// {{OSSP:module-rational_from_long:end}}


// {{OSSP:module-rational_print:begin}}
void rational_print(rational_t *number,
                    FILE *stream,
                    bool add_newline)
{
    fprintf(stream, "%ld/%ld (valid=%d)",
            number->num, number->den, number->valid);
    if (add_newline)
        fprintf(stream, "\n");
}
// {{OSSP:module-rational_print:end}}


// {{OSSP:module-long_gcd:begin}}
long long_gcd(long a, long b)
{
    if (a == 0 && b == 0)
    {
        lwlog_err("Either a (== %ld) or b (== %ld) must be non-zero", a, b);
        return 0;
    }

    if (b == 0)
    {
        return labs(a);
    }
    else
    {
        return long_gcd(b, a % b);
    }
}
// {{OSSP:module-long_gcd:end}}


// {{OSSP:module-reduce_fraction:begin}}
void reduce_fraction(rational_t *number)
{
    long common_divisor = long_gcd(number->num, number->den);
    if (common_divisor == 0)
        return;

    number->num /= common_divisor;
    number->den /= common_divisor;
    if (number->den < 0)
    {
        number->den = -number->den;
        number->num = -number->num;
    }
}
// {{OSSP:module-reduce_fraction:end}}


// {{OSSP:module-rational_numerator:begin}}
long rational_numerator(rational_t *number)
{
    return number->num;
}
// {{OSSP:module-rational_numerator:end}}


// {{OSSP:module-rational_denominator:begin}}
long rational_denominator(rational_t *number)
{
    return number->den;
}
// {{OSSP:module-rational_denominator:end}}


// {{OSSP:module-rational_add:begin}}
void rational_add(rational_t *n1,
                  rational_t *n2,
                  rational_t *result)
{

    long num1_den2_product, den1_num2_product, den1_x_den2, sum;

    bool v0 = n1->valid && n2->valid;
    bool v1 = long_multiply(n1->num, n2->den, &num1_den2_product);
    bool v2 = long_multiply(n2->num, n1->den, &den1_num2_product);
    bool v3 = long_multiply(n1->den, n2->den, &den1_x_den2);
    bool v4 = long_add(num1_den2_product, den1_num2_product, &sum);
    bool valid = v0 && v1 && v2 && v3 && v4;
    rational_internal_init(result, sum, den1_x_den2, valid);
}
// {{OSSP:module-rational_add:end}}


// {{OSSP:module-rational_subtract:begin}}
void rational_subtract(rational_t *n1,
                       rational_t *n2,
                       rational_t *result)
{
    long num1_den2_product, den1_num2_product, den1_x_den2, diff;
    bool v0 = n1->valid && n2->valid;
    bool v1 = long_multiply(n1->num, n2->den, &num1_den2_product);
    bool v2 = long_multiply(n2->num, n1->den, &den1_num2_product);
    bool v3 = long_multiply(n1->den, n2->den, &den1_x_den2);
    bool v4 = long_subtract(num1_den2_product, den1_num2_product, &diff);
    bool valid = v0 && v1 && v2 && v3 && v4;
    rational_internal_init(result, diff, den1_x_den2, valid);
}
// {{OSSP:module-rational_subtract:end}}


// {{OSSP:module-rational_multiply:begin}}
void rational_multiply(rational_t *n1,
                       rational_t *n2,
                       rational_t *result)
{
    long num1_x_num2, den1_x_den2;
    bool v0 = n1->valid && n2->valid;
    bool v1 = long_multiply(n1->num, n2->num, &num1_x_num2);
    bool v2 = long_multiply(n2->den, n1->den, &den1_x_den2);
    bool valid = v0 && v1 && v2;
    rational_internal_init(result, num1_x_num2, den1_x_den2, valid);
}
// {{OSSP:module-rational_multiply:end}}


// {{OSSP:module-rational_divide:begin}}
void rational_divide(rational_t *n1,
                     rational_t *n2,
                     rational_t *result)
{
    long num1_x_den2, den1_x_num2;
    bool v0 = n1->valid && n2->valid;
    bool v1 = long_multiply(n1->num, n2->den, &num1_x_den2);
    bool v2 = long_multiply(n2->den, n1->num, &den1_x_num2);
    bool valid = v0 && v1 && v2;
    rational_internal_init(result, num1_x_den2, den1_x_num2, valid);
}
// {{OSSP:module-rational_divide:end}}

// {{OSSP:module-rational_compare:begin}}
long rational_compare(rational_t *n1,
                      rational_t *n2,
                      rational_comparison_t *result)
{
    long num1_x_den2, den1_x_num2, diff;
    bool v0 = n1->valid && n2->valid;
    bool v1 = long_multiply(n1->num, n2->den, &num1_x_den2);
    bool v2 = long_multiply(n2->num, n1->den, &den1_x_num2);
    bool v3 = long_subtract(num1_x_den2, den1_x_num2, &diff);
    result->comparison = diff;
    result->valid = v0 && v1 && v2 && v3;
    return result->comparison;
}
// {{OSSP:module-rational_compare:end}}


// {{OSSP:module-rational_reciprocal:begin}}
void rational_reciprocal(rational_t *number)
{
    long num = number->num;
    long den = number->den;
    bool valid = number->valid;
    rational_internal_init(number, den, num, valid);
}
// {{OSSP:module-rational_reciprocal:end}}


// {{OSSP:module-rational_negate:begin}}
void rational_negate(rational_t *number)
{
    number->num = -number->num;
}
// {{OSSP:module-rational_negate:end}}
