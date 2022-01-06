#ifndef PATHTRACING_INTERSECTION_H
#define PATHTRACING_INTERSECTION_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
#include <eigen3/Eigen/Eigen>
#include "utility.hpp"
#include "Material.h"

class Intersection
{
public:
    Intersection();
    
    bool isHappened;
    Eigen::Vector3f coordinate;
    Eigen::Vector3f normal;
    Material material;
    float tOfRayWhenIntersected; // a recording value, not necesary
};

#endif