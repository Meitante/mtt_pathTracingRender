#include <gtest/gtest.h>
#include "MeshTriangle.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Intersection.h"
#include "Sphere.h"

TEST(Object_TestSuite, samplePointShouldBeInsideTriangle)
{
    for(int i = 0; i < 100; i++)
    {
        //TODO: might be invalid triangle
        Triangle triangle(Eigen::Vector3f(getRandomFloat(), getRandomFloat(), getRandomFloat()),
                                    Eigen::Vector3f(getRandomFloat(), getRandomFloat(), getRandomFloat()),
                                    Eigen::Vector3f(getRandomFloat(), getRandomFloat(), getRandomFloat()));
        //TODO: remove this comment
        // Triangle triangle(Eigen::Vector3f(0,0,0), Eigen::Vector3f(1, 0, 0), Eigen::Vector3f(0, 1, 0));
        // std::cout << "vertexs: \n" << triangle.vertex0[0] << ", " << triangle.vertex0[1] << ", " << triangle.vertex0[2] << ", \n" 
        //             << triangle.vertex1[0] << ", " << triangle.vertex1[1] << ", " << triangle.vertex1[2] << ", \n"
        //             << triangle.vertex2[0] << ", " << triangle.vertex2[1] << ", " << triangle.vertex2[2] << std::endl;
        float pdf = 0.0f;
        Intersection intersection;
        triangle.Sample(intersection, pdf);
        ASSERT_TRUE(triangle.isInside(intersection.coordinate));
    }
}

/*
    MeshTriangle Test
*/
TEST(Object_TestSuite, tryToLoadBunny)
{
    auto material = std::make_shared<Material>(Material::MaterialType::DIFFUSE);
    MeshTriangle bb(commonData::bunnyPath, material);
}
