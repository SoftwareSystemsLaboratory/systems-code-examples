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
static void rational_internal_init(rational_t *number, long numerator, long denominator, int valid);
// {{OSSP:module-statics:end}}


// {{OSSP:module-rational_allocate:begin}}
rational_t *rational_allocate()
{
    return (rational_t *) malloc(sizeof(rational_t));
}
// {{OSSP:module-rational_allocate:end}}


// {{OSSP:module-rational_init:begin}}
void rational_init(rational_t *number, long numerator, long denominator)
{
    rational_internal_init(number, numerator, denominator, 1);
}
// {{OSSP:module-rational_init:end}}


// {{OSSP:module-rational_internal_init:begin}}
static void rational_internal_init(rational_t *number, long numerator, long denominator, int valid)
{
    number->numerator = numerator;
    number->denominator = denominator;
    number->valid = (denominator != 0) ? valid : 0;
    reduce_fraction(number);
}
// {{OSSP:module-rational_internal_init:end}}


// {{OSSP:module-rational_from_rational:begin}}
void rational_from_rational(rational_t *number, rational_t *another)
{
    rational_internal_init(number,
        another->numerator, another->denominator, 1);
    reduce_fraction(number);
}
// {{OSSP:module-rational_from_rational:end}}


// {{OSSP:module-rational_from_long:begin}}
void rational_from_long(rational_t *number, long whole_number)
{
    rational_internal_init(number, whole_number, 1L, 1);
    reduce_fraction(number);
}
// {{OSSP:module-rational_from_long:end}}


// {{OSSP:module-rational_print:begin}}
void rational_print(rational_t *number, FILE *stream, int nl)
{
    fprintf(stream, "%ld/%ld (valid=%d)", number->numerator, number->denominator, number->valid);
    if (nl) fprintf(stream, "\n");
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
    long common_divisor = long_gcd(number->numerator, number->denominator);
    if (common_divisor == 0)
        return;

    number->numerator /= common_divisor;
    number->denominator /= common_divisor;
    if (number->denominator < 0)
    {
        number->denominator = -number->denominator;
        number->numerator = -number->numerator;
    }
}
// {{OSSP:module-reduce_fraction:end}}


// {{OSSP:module-rational_numerator:begin}}
long rational_numerator(rational_t *number)
{
    return number->numerator;
}
// {{OSSP:module-rational_numerator:end}}


// {{OSSP:module-rational_denominator:begin}}
long rational_denominator(rational_t *number)
{
    return number->denominator;
}
// {{OSSP:module-rational_denominator:end}}


// {{OSSP:module-rational_add:begin}}
void rational_add(rational_t *n1, rational_t *n2, rational_t *result)
{

    long num1_den2_product, den1_num2_product, dd_product, product_sum;

    int valid = n1->valid && n2->valid;
    valid = valid && long_multiply(n1->numerator, n2->denominator, &num1_den2_product);
    valid = valid && long_multiply(n2->numerator, n1->denominator, &den1_num2_product);
    valid = valid && long_multiply(n1->denominator, n2->denominator, &dd_product);
    valid = valid && long_add(num1_den2_product, den1_num2_product, &product_sum);
    rational_internal_init(result, product_sum, dd_product, valid);
}
// {{OSSP:module-rational_add:end}}


// {{OSSP:module-rational_subtract:begin}}
void rational_subtract(rational_t *n1, rational_t *n2, rational_t *result)
{
    long num1_den2_product, den1_num2_product, dd_product, product_diff;
    int valid = n1->valid && n2->valid;
    valid = valid && long_multiply(n1->numerator, n2->denominator, &num1_den2_product);
    valid = valid && long_multiply(n2->numerator, n1->denominator, &den1_num2_product);
    valid = valid && long_multiply(n1->denominator, n2->denominator, &dd_product);
    valid = valid && long_subtract(num1_den2_product, den1_num2_product, &product_diff);
    rational_internal_init(result, product_diff, dd_product, valid);
}
// {{OSSP:module-rational_subtract:end}}


// {{OSSP:module-rational_multiply:begin}}
void rational_multiply(rational_t *n1, rational_t *n2, rational_t *result)
{
    long nn_product, dd_product;
    int valid = n1->valid && n2->valid;
    valid = valid && long_multiply(n1->numerator, n2->numerator, &nn_product);
    valid = valid && long_multiply(n2->denominator, n1->denominator, &dd_product);
    rational_internal_init(result, nn_product, dd_product, valid);
}
// {{OSSP:module-rational_multiply:end}}


// {{OSSP:module-rational_divide:begin}}
void rational_divide(rational_t *n1, rational_t *n2, rational_t *result)
{
    long num1_den2_product, den1_num2_product;
    int valid = n1->valid && n2->valid;
    valid = valid && long_multiply(n1->numerator, n2->denominator, &num1_den2_product);
    valid = valid && long_multiply(n2->denominator, n1->numerator, &den1_num2_product);
    rational_internal_init(result, num1_den2_product, den1_num2_product, valid);
}
// {{OSSP:module-rational_divide:end}}

// {{OSSP:module-rational_compare:begin}}
long rational_compare(rational_t *n1, rational_t *n2, rational_comparison_t *result)
{
    long num1_den2_product, den1_num2_product, product_diff;
    int valid = n1->valid && n2->valid;
    valid = valid && long_multiply(n1->numerator, n2->denominator, &num1_den2_product);
    valid = valid && long_multiply(n2->numerator, n1->denominator, &den1_num2_product);
    valid = valid && long_subtract(num1_den2_product, den1_num2_product, &product_diff);
    result->valid = valid;
    result->comparison = product_diff;
    return result->comparison;
}
// {{OSSP:module-rational_compare:end}}


// {{OSSP:module-rational_reciprocal:begin}}
void rational_reciprocal(rational_t *number)
{
    long numerator = number->numerator;
    long denominator = number->denominator;
    rational_internal_init(number, denominator, numerator, number->valid);
}
// {{OSSP:module-rational_reciprocal:end}}


// {{OSSP:module-rational_negate:begin}}
void rational_negate(rational_t *number)
{
    number->numerator = -number->numerator;
}
// {{OSSP:module-rational_negate:end}}
