#include "Ray.h"

Ray::Ray(const Eigen::Vector3f& o, const Eigen::Vector3f& dir)
:origin(o)
,direction(dir.normalized())
{

}

Ray::Ray(float ox, float oy, float oz, float d1, float d2, float d3)
:origin(ox, oy, oz)
,direction(d1, d2, d3)
{
    direction.normalize();
}

Eigen::Vector3f Ray::getDestinationAfterT(float t) const
{
    return origin + t * direction;
}