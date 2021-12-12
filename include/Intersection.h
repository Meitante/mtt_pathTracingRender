#ifndef PATHTRACING_INTERSECTION_H
#define PATHTRACING_INTERSECTION_H

#include <eigen3/Eigen/Eigen>
#include "utility.hpp"

class Intersection
{
public:
    Intersection();
    Intersection(const Intersection& intersection) = default;
    Intersection(Intersection&& intersection) = default;
    
    bool isHappened;
    Eigen::Vector3f coordinate;
    Eigen::Vector3f normal;
};

#endif