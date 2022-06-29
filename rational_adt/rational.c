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

/* module:long_static_overflow_helpers */

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

/* module:statics */

static void rational_internal_init(rational_t *number, long numerator, long denominator, int valid);


/* module:rational_allocate */

rational_t *rational_allocate()
{
    return (rational_t *) malloc(sizeof(rational_t));
}

/* module:rational_init */

void rational_init(rational_t *number, long numerator, long denominator)
{
    number->numerator = numerator;
    number->denominator = denominator;
    rational_internal_init(number, numerator, denominator, 1);
}

/* module:rational_internal_init */

static void rational_internal_init(rational_t *number, long numerator, long denominator, int valid)
{
    number->numerator = numerator;
    number->denominator = denominator;
    number->valid = (denominator != 0) ? valid : 0;
    reduce_fraction(number);
}

/* module:rational_from_rational */

void rational_from_rational(rational_t *number, rational_t *another)
{
    rational_internal_init(number, another->numerator, another->denominator, 1);
    reduce_fraction(number);
}

/* module:rational_from_long */

void rational_from_long(rational_t *number, long whole_number)
{
    rational_internal_init(number, whole_number, 1L, 1);
    reduce_fraction(number);
}

/* module:rational_print */

void rational_print(rational_t *number, FILE *stream, int nl)
{
    fprintf(stream, "%ld/%ld (valid=%d)", number->numerator, number->denominator, number->valid);
    if (nl) fprintf(stream, "\n");
}

/* module:long_gcd */

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

/* module:reduce_fraction */

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

/* module:rational_numerator */

long rational_numerator(rational_t *number)
{
    return number->numerator;
}

/* module:rational_denominator */

long rational_denominator(rational_t *number)
{
    return number->denominator;
}


/*
 * rational addition is:
 *    (n->numerator * n2->denominator + n1->denominator * n2->denominator) / (n1->denominator * n2->denominator)
 *
 *    In this computation, we check for overflow(underflow) on each of these operations. If either is detected,
 *    the result is not valid. C does not have exceptions, so we check the result status.
 *    The & is used instead of && to avoid short circuiting.
 */

/* module:rational_add */

void rational_add(rational_t *n1, rational_t *n2, rational_t *result)
{

    long nd_product, dn_product, dd_product, nd_dn_product_sum;

    int valid = n1->valid & n2->valid
                & long_multiply(n1->numerator, n2->denominator, &nd_product)
                & long_multiply(n2->numerator, n1->denominator, &dn_product)
                & long_multiply(n1->denominator, n2->denominator, &dd_product)
                & long_add(nd_product, dn_product, &nd_dn_product_sum);
    rational_internal_init(result, nd_dn_product_sum, dd_product, valid);
}

/* module:rational_subtract */

void rational_subtract(rational_t *n1, rational_t *n2, rational_t *result)
{
    long nd_product, dn_product, dd_product, nd_dn_product_diff;
    int valid = n1->valid & n2->valid
                & long_multiply(n1->numerator, n2->denominator, &nd_product)
                & long_multiply(n2->numerator, n1->denominator, &dn_product)
                & long_multiply(n1->denominator, n2->denominator, &dd_product)
                & long_subtract(nd_product, dn_product, &nd_dn_product_diff);
    rational_internal_init(result, nd_dn_product_diff, dd_product, valid);
}


/* module:rational_multiply */

void rational_multiply(rational_t *n1, rational_t *n2, rational_t *result)
{
    long nn_product, dd_product;
    int valid = n1->valid & n2->valid
                & long_multiply(n1->numerator, n2->numerator, &nn_product)
                & long_multiply(n2->denominator, n1->denominator, &dd_product);
    rational_internal_init(result, nn_product, dd_product, valid);
}

/* module:rational_divide */

void rational_divide(rational_t *n1, rational_t *n2, rational_t *result)
{
    long nd_product, dn_product;
    int valid = n1->valid & n2->valid
                & long_multiply(n1->numerator, n2->denominator, &nd_product)
                & long_multiply(n2->denominator, n1->numerator, &dn_product);
    rational_internal_init(result, nd_product, dn_product, valid);
}

/* module:rational_compare */

long rational_compare(rational_t *n1, rational_t *n2, rational_comparison_t *result)
{
    long nd_product, dn_product, nd_dn_product_diff;
    result->valid = n1->valid & n2->valid
                    & long_multiply(n1->numerator, n2->denominator, &nd_product)
                    & long_multiply(n2->numerator, n1->denominator, &dn_product)
                    & long_subtract(nd_product, dn_product, &nd_dn_product_diff);
    result->comparison = nd_dn_product_diff;
    return result->comparison;
}

/* module:rational_reciprocal */

void rational_reciprocal(rational_t *number)
{
    long numerator = number->numerator;
    long denominator = number->denominator;
    rational_internal_init(number, denominator, numerator, 1);
}

/* module:rational_negate */

void rational_negate(rational_t *number)
{
    number->numerator = -number->numerator;
}
