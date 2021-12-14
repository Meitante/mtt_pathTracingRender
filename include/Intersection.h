#ifndef PATHTRACING_INTERSECTION_H
#define PATHTRACING_INTERSECTION_H

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
};

#endif