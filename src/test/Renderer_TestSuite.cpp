#include <gtest/gtest.h>
#include "Renderer.h"
#include "Scene.h"
#include "Material.h"

TEST(Renderer_TestSuite, test1)
{
    auto scene = std::make_unique<Scene>(480, 270);
    Renderer r(std::move(scene), "test.ppm");
    int n = 1;
    ASSERT_EQ(n, 1);
}

TEST(Renderer_TestSuite, DiffuseMaterialSampling)
{
    for(int i = 0; i < 100; i++)
    {
        Eigen::Vector3f normal(getRandomFloat(), getRandomFloat(), getRandomFloat());
        Material m(Material::MaterialType::DIFFUSE);
        Eigen::Vector3f sampled = m.sample(Eigen::Vector3f(0, 0, 0), normal);
        ASSERT_TRUE(sampled.dot(normal) > -0.00001);
    }
    
}
