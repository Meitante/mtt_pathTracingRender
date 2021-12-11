#include <gtest/gtest.h>
#include "Ray.h"


TEST(Ray_TestSuite, directionBeingNormalized)
{
    Ray r({0, 1, 2}, {1, 2, 3});
    ASSERT_FLOAT_EQ(r.direction.dot(r.direction), 1);
}

TEST(Ray_TestSuite, destinationShouldBeAsExpected)
{
    Ray r({0, 1, 2}, {1, 0, 0});
    auto des = r.getDestinationAfterT(5);
    ASSERT_FLOAT_EQ(des.x(), 5.0f);
    ASSERT_FLOAT_EQ(des.y(), 1.0f);
    ASSERT_FLOAT_EQ(des.z(), 2.0f);
}