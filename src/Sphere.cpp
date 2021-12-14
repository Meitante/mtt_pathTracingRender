#include "Sphere.h"
#include "Intersection.h"
#include <_stdio.h>

Sphere::Sphere(const Eigen::Vector3f& pos, float r)
:Object()
,centre(pos)
,radius(r)
{
    assert(r > -0.00001);
}

Sphere::Sphere(float x, float y, float z, float r)
:Object()
,centre(x, y, z)
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

Intersection Sphere::getIntersectionWithRay(const Ray& ray)
{
    Intersection intersection;
    Eigen::Vector3f L = ray.origin - centre;
    float a = ray.direction.dot(ray.direction);
    float b = 2 * ray.direction.dot(L);
    float c = L.dot(L) - radius * radius;
    float t0, t1;
    if (!solveQuadratic(a, b, c, t0, t1)) return intersection;
    if (t0 < 0)
    {
        /*
            if 0 < t0 < t1, the first intersection should be t0
            if t0 < 0 < t1, it means ray origin is inside sphere, t1 should be the intersection.
        */
        t0 = t1;
    }
    if (t0 <= 0.5)
    {
        // isHappened being false by default
        return intersection;
    }


    intersection.isHappened = true;
    intersection.coordinate = ray.getDestinationAfterT(t0);
    intersection.normal = intersection.coordinate - centre;
    intersection.normal = intersection.normal.normalized();
    intersection.material = material;

    return intersection;
}

