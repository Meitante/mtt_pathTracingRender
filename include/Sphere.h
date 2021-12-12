#ifndef PATHTRACING_SHPERE_H
#define PATHTRACING_SHPERE_H

#include <eigen3/Eigen/Eigen>
#include "Object.h"

class Sphere: public Object
{
public:
    Sphere(const Eigen::Vector3f& pos = Eigen::Vector3f(0, 0, 0), float r = 0.0f);


    virtual BoundingBox getBoundingBox() override;
    virtual float getSurfaceArea() override;

public:
    Eigen::Vector3f centre;
    float radius;


};


#endif