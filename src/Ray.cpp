#include "Ray.h"

Ray::Ray(const Eigen::Vector3f& o, const Eigen::Vector3f& dir)
:origin(o)
,direction(dir.normalized())
{

}

Eigen::Vector3f Ray::getDestinationAfterT(float t) const
{
    return origin + t * direction;
}