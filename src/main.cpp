#include "Renderer.h"
#include "Sphere.h"
#include "Material.h"

/*
    This file is to test the output directly.
*/

int main()
{
    auto scene = std::make_unique<Scene>(480, 270);

    scene->setEyePos(Eigen::Vector3f(0, 0, 1000));

    auto m1 = Material(Material::MaterialType::DIFFUSE, Eigen::Vector3f(0.8, 0.2, 0.1));
    auto m2 = Material(Material::MaterialType::DIFFUSE);

    auto sphere1 = std::make_unique<Sphere>(-100, 100, -800, 50);
    sphere1->material = m1;
    auto sphere2 = std::make_unique<Sphere>(-300, -300, -500, 100);
    sphere2->material = m2;
    scene->addObject(std::move(sphere1));
    scene->addObject(std::move(sphere2));

    Renderer r(std::move(scene), "test.ppm");
    r.render();
    return 0;
}