/* test cases */

#include <gtest/gtest.h>

#include "rational.hh"

TEST(PointTest, Initialization) {
    rational_t r1, r2, r3;

    rational_init(&r1, 1, 2);
    rational_init(&r2, 300, 400);

    
    ASSERT_EQ( rational_numerator(&r1), 1L);
    ASSERT_EQ( rational_denominator(&r1), 2L);

    ASSERT_EQ( rational_numerator(&r2), 3L);
    ASSERT_EQ( rational_denominator(&r2), 4L);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
