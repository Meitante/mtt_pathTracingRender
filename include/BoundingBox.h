#ifndef PATHTRACING_BOUNDINGBOX_H
#define PATHTRACING_BOUNDINGBOX_H

#include <eigen3/Eigen/Eigen>
#include <iostream>
#include "Ray.h"
#include "Intersection.h"

/*
    Every sides are parallel to coordinate axis
    So a box can be descirbe by two points.
*/

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(float minx, float minY, float minZ, float maxX, float maxY, float maxZ);
    BoundingBox(const Eigen::Vector3f& min, const Eigen::Vector3f& max);
    BoundingBox(const BoundingBox& b);
    ~BoundingBox(){};

    Eigen::Vector3f getDiagonal() const;
    bool isIntersectedWithRay(const Ray& ray);

public:
    Eigen::Vector3f pMin = {0, 0, 0};
    Eigen::Vector3f pMax = {0, 0, 0};

private:

};

/*
    frequency call function list, should be inline.
*/

/*
    Not mathematical union
    return another boundingbox bounding these two bounding box
    
*/
inline BoundingBox getUnion(const BoundingBox& b1, const BoundingBox& b2)
{
    BoundingBox res;

    for(int i = 0; i < 3; i++)
    {
        res.pMin[i] = std::min(b1.pMin[i], b2.pMin[i]);
        res.pMax[i] = std::max(b1.pMax[i], b2.pMax[i]);
    }
    return res;
}

#endif