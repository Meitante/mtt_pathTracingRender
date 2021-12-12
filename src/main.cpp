#include "Renderer.h"
#include "Sphere.h"

/*
    This file is to test the output directly.
*/

int main()
{
    auto scene = std::make_unique<Scene>(480, 270);

    scene->setEyePos(Eigen::Vector3f(0, 0, 1000));
    auto sphere1 = std::make_unique<Sphere>(100, 100, -300, 50);
    auto sphere2 = std::make_unique<Sphere>(-300, -300, -500, 100);
    scene->addObject(std::move(sphere1));
    scene->addObject(std::move(sphere2));

    Renderer r(std::move(scene), "test.ppm");
    r.render();
    return 0;
}