#ifndef PATHTRACING_TRIANGLE_H
#define PATHTRACING_TRIANGLE_H
#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
#include <eigen3/Eigen/Eigen>
#include "Object.h"

class Triangle: public Object
{
public:
    Triangle(const Eigen::Vector3f& v0, const Eigen::Vector3f& v1, const Eigen::Vector3f& v2);
    virtual BoundingBox getBoundingBox() const;
    virtual float getSurfaceArea() const;
    virtual Intersection getIntersectionWithRay(const Ray& ray);
    virtual void Sample(Intersection& intersection, float& pdf) const;

    bool isInside(const Eigen::Vector3f& p) const;
private:
        

public:
    // vertex given in counter-clockwise order
    Eigen::Vector3f vertex0;
    Eigen::Vector3f vertex1;
    Eigen::Vector3f vertex2;
    Eigen::Vector3f edge1; // vertex1 - vertex0
    Eigen::Vector3f edge2; // vertex2 - vertex0
    Eigen::Vector3f normal;
    


};


#endif