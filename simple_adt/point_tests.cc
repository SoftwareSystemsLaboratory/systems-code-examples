/* test cases */

#include <gtest/gtest.h>

#include "point.hh"

TEST(PointTest, Basics) {
    point_t p1, p2, p3;
    point_init(&p1, 3, 0);
    point_init(&p2, 0, 4);
    point_new(&p3);
    ASSERT_FLOAT_EQ( point_distance(&p1, &p2), 5.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
