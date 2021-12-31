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
}


TEST(RationalTest, Comparison) {
    rational_t r1, r2, r3;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);
    rational_init(&r3, 3, 4);

    ASSERT_LT(rational_compare(&r1, &r2), 0);
    ASSERT_EQ(rational_compare(&r2, &r3), 0);
    ASSERT_GT(rational_compare(&r3, &r1), 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
