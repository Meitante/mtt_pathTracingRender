#include <gtest/gtest.h>
#include "BoundingBox.h"
#include "Sphere.h"

TEST(BoundingBox_TestSuite, isDiagonal)
{
    BoundingBox b1;
    b1.pMin = {1, 2, 3};
    b1.pMax = {4, 5, 4};

    BoundingBox b2;
    b2.pMin = {0, 0, 0};
    b2.pMax = {1, 1, 1};

    auto diagonal1 = b1.getDiagonal();
    // auto diagonal2 = b2.getDiagonal();

    ASSERT_FLOAT_EQ(diagonal1.dot(diagonal1), 19.0f);

    auto b12 = getUnion(b1, b2);
    auto diagonal12 = b12.getDiagonal();

    ASSERT_FLOAT_EQ(diagonal12.dot(diagonal12), 57.0f);
}

TEST(BoundingBox_TestSuite, isIntersectedWithRay)
{
    BoundingBox b1;
    b1.pMin = {1, 2, 3};
    b1.pMax = {4, 5, 4};

    Ray ray1(0, 0, 0, 1, 2 ,3);
    ASSERT_TRUE(b1.isIntersectedWithRay(ray1));

    Ray ray2(0, 0, 0, 1, 0, 0);
    ASSERT_FALSE(b1.isIntersectedWithRay(ray2));

    Ray ray3(1, 2, 3, 52, 68, 34);
    ASSERT_TRUE(b1.isIntersectedWithRay(ray3));

    Ray ray4(0, 0, 0, 1, 1 ,1);
    ASSERT_TRUE(b1.isIntersectedWithRay(ray4));
}

TEST(BoundingBox_TestSuite, testIntersectedSphere)
{
    float radius = 2.3f;
    Sphere sphere(Eigen::Vector3f(3.0f, 3.0f, 3.0f), radius);

    auto bbSphere = sphere.getBoundingBox();
    ASSERT_FLOAT_EQ(bbSphere.getDiagonal().dot(bbSphere.getDiagonal()), radius * radius * 12);

    Ray ray1(1, 0, 0, 1, 1, 1);
    ASSERT_TRUE(bbSphere.isIntersectedWithRay(ray1));
}


