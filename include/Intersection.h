#ifndef PATHTRACING_INTERSECTION_H
#define PATHTRACING_INTERSECTION_H

#include <eigen3/Eigen/Eigen>

class Intersection
{
public:
    Intersection();
    Intersection(const Intersection& intersection) = default;
    Intersection(Intersection&& intersection) = delete;
    
    bool isHappened;
    Eigen::Vector3f coordinate;
};

#endif