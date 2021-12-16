#include <gtest/gtest.h>
#include "Intersection.h"
#include "Sphere.h"

TEST(Intersection_TestSuite, sampleInSurface)
{
    for(int i = 0; i < 100; i++)
    {
        auto s = Sphere(Eigen::Vector3f(getRandomFloat(), getRandomFloat(), getRandomFloat()), getRandomFloat());
        Intersection intersection;
        float pdf;
        s.Sample(intersection, pdf);
        ASSERT_TRUE(s.isInSurface(intersection.coordinate));
    }
}

TEST(Intersection_TestSuite, intersection1)
{
    auto s = Sphere(Eigen::Vector3f(0, 0, 0), 100);

    Eigen::Vector3f o1(0, 0, -99);
    Eigen::Vector3f dir1(0, 0, 1);
    Ray ray1(o1, dir1);
    ASSERT_TRUE(s.getIntersectionWithRay(ray1).isHappened);

    Eigen::Vector3f o2(0, 0, -100);
    Eigen::Vector3f dir2(0, 0, 1);
    Ray ray2(o2, dir2);
    ASSERT_TRUE(s.getIntersectionWithRay(ray2).isHappened);
}
