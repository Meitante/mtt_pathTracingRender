#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <eigen3/Eigen/Eigen>

class Ray
{
public:
    Ray(const Eigen::Vector3f& o, const Eigen::Vector3f& dir);
    Ray(const Ray& r) = default;
    Ray(const Ray&& r) = delete;

    Eigen::Vector3f getDestinationAfterT(float t) const;


public:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;

private:

};



#endif