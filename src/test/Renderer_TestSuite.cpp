#include <gtest/gtest.h>
#include "Renderer.h"
#include "Scene.h"

TEST(Renderer_TestSuite, test1)
{
    auto scene = std::make_unique<Scene>(480, 270);
    Renderer r(std::move(scene), "test.ppm");
    int n = 1;
    ASSERT_EQ(n, 1);
}

