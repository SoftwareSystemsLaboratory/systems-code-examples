#include <gtest/gtest.h>
#include <limits.h>

#include "rational.hh"

// {{OSSP:module-rational_tests_HelpersUtilities:begin}}
TEST(RationalTest, HelpersUtilities)
{
    long a, b, c, success;

    /* test LONG_MAX boundaries */

    a = LONG_MAX;
    b = 1;
    ASSERT_FALSE(long_add(a, b, &c)); /* overflow on LONG_MAX + 1 */
    ASSERT_TRUE(long_subtract(a, b, &c)); /* no overflow on LONG_MAX - 1 */
    ASSERT_TRUE(long_multiply(a, b, &c)); /* no overflow on LONG_MAX * 1 */

    /* test LONG_MIN boundaries */

    a = LONG_MIN;
    ASSERT_FALSE(long_subtract(a, b, &c)); /* underflow on LONG_MAX - 1 */
    ASSERT_TRUE(long_add(a, b, &c)); /* no underflow on LONG_MAX + 1 */
    ASSERT_TRUE(long_multiply(a, b, &c)); /* no underflow on LONG_MAX * 1 */

    /* test LONG_MIN and LONG_MAX overflows on multiply */

    a = LONG_MAX;
    b = 2;
    ASSERT_FALSE(long_multiply(a, b, &c)); /* overflow on LONG_MAX * 2 */
    a = LONG_MIN;
    b = 2;
    ASSERT_FALSE(long_multiply(a, b, &c)); /* underflow on LONG_MIN * 2 */

    /* test normal in-range behavior (things not expected to over/underflow */
    a = 25;
    b = 35;
    ASSERT_TRUE(long_add(a, b, &c)); /* no overflow on a + b */
    ASSERT_TRUE(long_subtract(a, b, &c)); /* no overflow on a - b */
    ASSERT_TRUE(long_multiply(a, b, &c)); /* no overflow on a * b */
}
// {{OSSP:module-rational_tests_HelpersUtilities:end}}


// {{OSSP:module-rational_tests_Initialization:begin}}
TEST(RationalTest, Initialization)
{
    rational_t r1, r2, r3;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);

    ASSERT_EQ(rational_numerator(&r1), 1L);
    ASSERT_EQ(rational_denominator(&r1), 2L);

    ASSERT_EQ(rational_numerator(&r2), 3L);
    ASSERT_EQ(rational_denominator(&r2), 4L);

    rational_from_rational(&r3, &r1);
    ASSERT_EQ(rational_numerator(&r3), 1L);
    ASSERT_EQ(rational_denominator(&r3), 2L);

    rational_from_long(&r3, 4L);
    ASSERT_EQ(rational_numerator(&r3), 4L);
    ASSERT_EQ(rational_denominator(&r3), 1L);
}
// {{OSSP:module-rational_tests_Initialization:end}}

// {{OSSP:module-rational_tests_SimpleComparison:begin}}
TEST(RationalTest, SimpleComparison)
{
    rational_t r1, r2, r3;
    rational_comparison_t comparison;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);
    rational_init(&r3, 3, 4);

    ASSERT_LT(rational_compare(&r1, &r2, &comparison), 0);
    ASSERT_EQ(rational_compare(&r2, &r3, &comparison), 0);
    ASSERT_GT(rational_compare(&r3, &r1, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleComparison:end}}

// {{OSSP:module-rational_tests_SimpleAdd:begin}}
TEST(RationalTest, SimpleAdd)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_init(&r1, 1, 2);
    rational_init(&r2, -1, 4);
    rational_init(&expected, 1, 4);

    rational_add(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleAdd:end}}

// {{OSSP:module-rational_tests_SimpleSubtract:begin}}
TEST(RationalTest, SimpleSubtract)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_init(&r1, 2, 3);
    rational_init(&r2, -1, 6);
    rational_init(&expected, 5, 6);

    rational_subtract(&r1, &r2, &result);

    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleSubtract:end}}


// {{OSSP:module-rational_tests_SimpleMultiply:begin}}
TEST(RationalTest, SimpleMultiply)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_init(&r1, 2, 3);
    rational_init(&r2, 30, 20);
    rational_init(&expected, 1, 1);

    rational_multiply(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleMultiply:end}}

// {{OSSP:module-rational_tests_SimpleDivide:begin}}
TEST(RationalTest, SimpleDivide)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_init(&r1, -2, 3);
    rational_init(&r2, 2000, -3000);
    rational_init(&expected, 1, 1);

    rational_divide(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleDivide:end}}

// {{OSSP:module-rational_tests_SimpleReciprocal:begin}}

TEST(RationalTest, SimpleReciprocal)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_from_long(&r1, 4);
    rational_from_rational(&r2, &r1);
    rational_reciprocal(&r2);
    rational_from_long(&expected, 1);
    rational_multiply(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleReciprocal:end}}

// {{OSSP:module-rational_tests_SimpleNegate:begin}}

TEST(RationalTest, SimpleNegate)
{
    rational_t r1, r2, expected, result;
    rational_comparison_t comparison;

    rational_init(&r1, -1, 4);
    rational_from_rational(&r2, &r1);
    rational_negate(&r1);
    rational_from_long(&expected, 0);
    rational_add(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
}
// {{OSSP:module-rational_tests_SimpleNegate:end}}

// {{OSSP:module-rational_tests_RandomAdd:begin}}
TEST(RationalTest, RandomAdd)
{
    for (int i = 0; i < 10; i++)
    {
        rational_t r1, r2, expected, result;
        rational_comparison_t comparison;

        rational_init(&r1, 1000 - rand() % 1000, 1 + rand() % 1000);
        rational_init(&r2, 1000 - rand() % 1000, 1 + rand() % 1000);

        long rand_num =
                rational_numerator(&r1) * rational_denominator(&r2) +
                rational_denominator(&r1) * rational_numerator(&r2);
        long rand_den =
                rational_denominator(&r1) * rational_denominator(&r2);
        rational_init(&expected, rand_num, rand_den);
        rational_add(&r1, &r2, &result);
        ASSERT_EQ(rational_compare(&result, &expected, &comparison), 0);
    }
}
// {{OSSP:module-rational_tests_RandomAdd:end}}


// {{OSSP:module-rational_tests_main:begin}}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// {{OSSP:module-rational_tests_main:end}}
