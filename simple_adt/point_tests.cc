/* test cases */

#include <gtest/gtest.h>

#include "point.hh"

TEST(PointTest, Initialization)
{
    point_t p1, p2, p3;

    point_init(&p1, 3, 0);
    point_init(&p2, 0, 4);
    point_new(&p3);

    ASSERT_FLOAT_EQ( point_x(&p1), 3.0);
    ASSERT_FLOAT_EQ( point_y(&p1), 0.0);

    ASSERT_FLOAT_EQ( point_x(&p2), 0.0);
    ASSERT_FLOAT_EQ( point_y(&p2), 4.0);

    ASSERT_FLOAT_EQ( point_x(&p3), 0.0);
    ASSERT_FLOAT_EQ( point_y(&p3), 0.0);

}


TEST(PointTest, Add)
{
    point_t p1, p2, p3;

    point_new(&p3);
    point_init(&p1, 3, 0);
    point_init(&p2, 0, 4);
    point_add(&p3, &p1);
    ASSERT_FLOAT_EQ( point_x(&p3), 3.0);
    ASSERT_FLOAT_EQ( point_y(&p3), 0.0);
    point_add(&p3, &p2);
    ASSERT_FLOAT_EQ( point_x(&p3), 3.0);
    ASSERT_FLOAT_EQ( point_y(&p3), 4.0);
}

TEST(PointTest, Distance)
{
    point_t p1, p2, p3;

    point_init(&p1, 3, 0);
    point_init(&p2, 0, 4);
    ASSERT_FLOAT_EQ( point_distance(&p1, &p2), 5.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
