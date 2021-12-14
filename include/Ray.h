#ifndef PATHTRACING_RAY_H
#define PATHTRACING_RAY_H

#include <eigen3/Eigen/Eigen>

class Ray
{
public:
    Ray(const Eigen::Vector3f& o, const Eigen::Vector3f& dir);
    Ray(float ox, float oy, float oz, float d1, float d2, float d3);

    Eigen::Vector3f getDestinationAfterT(float t) const;


public:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;

private:

};



#endif