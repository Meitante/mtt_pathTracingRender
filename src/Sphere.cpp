#include "Sphere.h"


Sphere::Sphere(const Eigen::Vector3f& pos, float r)
:Object()
,centre(pos)
,radius(r)
{
    assert(r > -0.00001);
}

BoundingBox Sphere::getBoundingBox()
{
    return BoundingBox(centre.x() - radius, centre.y() - radius, centre.z() - radius,
                       centre.x() + radius, centre.y() + radius, centre.z() + radius);
}

float Sphere::getSurfaceArea()
{
    return 4 * PI * radius;
}
