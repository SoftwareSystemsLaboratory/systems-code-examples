/* test cases */

#include <gtest/gtest.h>

#include "rational.hh"

TEST(RationalTest, Initialization) {
    rational_t r1, r2, r3;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);

    ASSERT_EQ( rational_numerator(&r1), 1L);
    ASSERT_EQ( rational_denominator(&r1), 2L);

    ASSERT_EQ( rational_numerator(&r2), 3L);
    ASSERT_EQ( rational_denominator(&r2), 4L);

    rational_from_rational(&r3, &r1);
    ASSERT_EQ( rational_numerator(&r3), 1L);
    ASSERT_EQ( rational_denominator(&r3), 2L);

    rational_from_long(&r3, 4L);
    ASSERT_EQ( rational_numerator(&r3), 4L);
    ASSERT_EQ( rational_denominator(&r3), 1L);
}


TEST(RationalTest, SimpleComparison) {
    rational_t r1, r2, r3;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);
    rational_init(&r3, 3, 4);

    ASSERT_LT(rational_compare(&r1, &r2), 0);
    ASSERT_EQ(rational_compare(&r2, &r3), 0);
    ASSERT_GT(rational_compare(&r3, &r1), 0);

    ASSERT_TRUE(rational_lt(&r1,&r2));
    ASSERT_TRUE(rational_le(&r1,&r2));
    ASSERT_TRUE(rational_eq(&r2,&r3));
    ASSERT_TRUE(rational_gt(&r3,&r1));
    ASSERT_TRUE(rational_ge(&r3,&r1));
}

TEST(RationalTest, SimpleAdd) {
    rational_t r1, r2, expected, result;
    rational_init(&r1, 1, 2);
    rational_init(&r2, -1, 4);
    rational_init(&expected, 1, 4);

    rational_add(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}

TEST(RationalTest, SimpleSubtract) {
    rational_t r1, r2, expected, result;
    rational_init(&r1, 2, 3);
    rational_init(&r2, -1, 6);
    rational_init(&expected, 5, 6);

    rational_subtract(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}


TEST(RationalTest, SimpleMultiply) {
    rational_t r1, r2, expected, result;
    rational_init(&r1, 2, 3);
    rational_init(&r2, 30, 20);
    rational_init(&expected, 1, 1);

    rational_multiply(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}

TEST(RationalTest, SimpleDivide) {
    rational_t r1, r2, expected, result;
    rational_init(&r1, -2, 3);
    rational_init(&r2, 2000, -3000);
    rational_init(&expected, 1, 1);

    rational_divide(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}

TEST(RationalTest, SimpleReciprocal) {
    rational_t r1, r2, expected, result;
    rational_from_long(&r1, 4);
    rational_from_rational(&r2, &r1);
    rational_reciprocal(&r2);
    rational_from_long(&expected, 1);
    rational_multiply(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}

TEST(RationalTest, SimpleNegate) {
    rational_t r1, r2, expected, result;
    rational_init(&r1, -1, 4);
    rational_from_rational(&r2, &r1);
    rational_negate(&r1);
    rational_from_long(&expected, 0);
    rational_add(&r1, &r2, &result);
    ASSERT_EQ(rational_compare(&result, &expected), 0);
}

TEST(RationalTest, RandomAdd) {
    for (int i=0; i < 10; i++) {
       rational_t r1, r2, expected, result;
       rational_init(&r1, 1000 - rand() % 1000, 1 + rand() % 1000);
       rational_init(&r2, 1000 - rand() % 1000, 1 + rand() % 1000);
       long add_numerator = rational_numerator(&r1) * rational_denominator(&r2) + rational_denominator(&r1) * rational_numerator(&r2);
       long add_denominator = rational_denominator(&r1) * rational_denominator(&r2);
       rational_init(&expected, add_numerator, add_denominator);
       rational_add(&r1, &r2, &result);
       ASSERT_EQ(rational_compare(&result, &expected), 0);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
