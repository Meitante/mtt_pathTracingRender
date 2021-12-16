#include "Renderer.h"
#include "Sphere.h"
#include "Material.h"

/*
    This file is to test the output directly.
*/

int main()
{
    auto scene = std::make_unique<Scene>(480, 270);
    // auto scene = std::make_unique<Scene>(2160, 1600);
    scene->setEyePos(Eigen::Vector3f(0, 0, 1000));
    Eigen::Vector3f aLight(8.0f * Eigen::Vector3f(0.747f+0.058f, 0.747f+0.258f, 0.747f) + 
                            15.6f * Eigen::Vector3f(0.740f+0.287f,0.740f+0.160f,0.740f) + 
                            18.4f * Eigen::Vector3f(0.737f+0.642f,0.737f+0.159f,0.737f));
    // Todo: figure out what is the map from raidance to this RGB or vector
    // (8.0f * Vector3f(0.747f+0.058f, 0.747f+0.258f, 0.747f) + 15.6f * Vector3f(0.740f+0.287f,0.740f+0.160f,0.740f) + 18.4f *Vector3f(0.737f+0.642f,0.737f+0.159f,0.737f))
    auto m1 = Material(Material::MaterialType::DIFFUSE, aLight * 100);
    auto m2 = Material(Material::MaterialType::DIFFUSE);

    auto sphere1 = std::make_unique<Sphere>(-100, 100, -200, 50);
    sphere1->material = m1;
    auto sphere2 = std::make_unique<Sphere>(-300, -300, -150, 100);
    sphere2->material = m2;

    auto sphere3 = std::make_unique<Sphere>(-100, -400, -100, 50);
    sphere3->material = m2;
    scene->addObject(std::move(sphere1));
    scene->addObject(std::move(sphere2));
    scene->addObject(std::move(sphere3));
    Renderer r(std::move(scene), "test.ppm");
    r.render();
    return 0;
}