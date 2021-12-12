#ifndef PATHTRACING_SCENE_H
#define PATHTRACING_SCENE_H

#include <eigen3/Eigen/Eigen>
#include <iostream>

#include "Ray.h"

class Scene
{
public:
    Scene(unsigned int w, unsigned int h);
    Scene(const Scene& s) = delete;
    Scene(Scene&& s) = delete;


    // Eigen::Vector3f getColorFromTracingRay(const Ray&);
    void setEyePos(const Eigen::Vector3f& in_eyePos);

public:
    unsigned int width;
    unsigned int height;
    Eigen::Vector3f eyePos;

    Eigen::Vector3f backgroundColor;

private:

};


#endif