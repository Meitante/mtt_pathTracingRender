#include <eigen3/Eigen/Eigen>
#include "Renderer.h"
#include "Sphere.h"
#include "Material.h"
#include "Triangle.h"

/*
    This file is to test the output directly.
*/

// TODO: bvh
// TODO: the mapping from radiance to RGB
// Done: time record
// TODO: DIFFUSE kd/understand it.

int main()
{
    auto scene = std::make_unique<Scene>(480, 270);
    // auto scene = std::make_unique<Scene>(2160, 1600);
    // auto scene = std::make_unique<Scene>(1080, 800);
    scene->setEyePos(Eigen::Vector3f(0, 0, 2000));

    /*
        fengexian first start test startTo
    */
    Eigen::Vector3f aLight(8.0f * Eigen::Vector3f(0.747f+0.058f, 0.747f+0.258f, 0.747f) + 
                            15.6f * Eigen::Vector3f(0.740f+0.287f,0.740f+0.160f,0.740f) + 
                            18.4f * Eigen::Vector3f(0.737f+0.642f,0.737f+0.159f,0.737f));
    // Todo: figure out what is the map from raidance to this RGB or vector
    // (8.0f * Vector3f(0.747f+0.058f, 0.747f+0.258f, 0.747f) + 15.6f * Vector3f(0.740f+0.287f,0.740f+0.160f,0.740f) + 18.4f *Vector3f(0.737f+0.642f,0.737f+0.159f,0.737f))
    auto m1 = Material(Material::MaterialType::DIFFUSE, aLight * 1000);
    
    auto m2 = Material(Material::MaterialType::DIFFUSE);
    m2.setDiffuseKd(Eigen::Vector3f(0.0f, 0.4f, 0.6f));

    auto sphere1 = std::make_unique<Sphere>(0, 0, -200, 50);
    sphere1->material = m1;
    auto sphere2 = std::make_unique<Sphere>(-300, -300, -150, 100);
    sphere2->material = m2;
    auto sphere3 = std::make_unique<Sphere>(-100, -400, -100, 50);
    sphere3->material = m2;
    auto sphere4 = std::make_unique<Sphere>(300, 200, -200, 70);
    sphere4->material = m2;
    auto sphere5 = std::make_unique<Sphere>(100, 500, -300, 130);
    sphere5->material = m2;
    auto sphere6 = std::make_unique<Sphere>(-1500, 0, 0, 800);
    sphere6->material = m2;
    auto triangle1 = std::make_unique<Triangle>(Eigen::Vector3f(500, 500, -300),
                                                Eigen::Vector3f(100, 0, -400),
                                                Eigen::Vector3f(1000, 0, 200));
    triangle1->material = m2;
    auto triangle2 = std::make_unique<Triangle>(Eigen::Vector3f(500, -400, -300),
                                                Eigen::Vector3f(450, -500, -400),
                                                Eigen::Vector3f(600, -500, -300));
    triangle2->material = m2;
    /*
        fengexian first start test End
    */

    scene->addObject(std::move(sphere1));
    scene->addObject(std::move(sphere2));
    scene->addObject(std::move(sphere3));
    scene->addObject(std::move(sphere4));
    scene->addObject(std::move(sphere5));
    scene->addObject(std::move(sphere6));
    scene->addObject(std::move(triangle1));
    scene->addObject(std::move(triangle2));
    Renderer r(std::move(scene), "test.ppm");
    r.renderWithTimestampLogged();
    return 0;
}


