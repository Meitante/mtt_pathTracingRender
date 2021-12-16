#ifndef PATHTRACING_SHPERE_H
#define PATHTRACING_SHPERE_H

#include <eigen3/Eigen/Eigen>
#include "Object.h"
#include "Ray.h"
#include "Intersection.h"

class Sphere: public Object
{
public:
    Sphere(const Eigen::Vector3f& pos = Eigen::Vector3f(0, 0, 0), float r = 0.0f);
    Sphere(float x, float y, float z, float r = 0.0);

    virtual BoundingBox getBoundingBox() override;
    virtual float getSurfaceArea() const override;
    virtual Intersection getIntersectionWithRay(const Ray& ray) override;
    virtual void Sample(Intersection& intersection, float& pdf) const override;

    bool isInSurface(Eigen::Vector3f pos) const;


public:
    Eigen::Vector3f centre;
    float radius;


};


#endif