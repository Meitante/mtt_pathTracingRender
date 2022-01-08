#include "Sphere.h"
#include "Intersection.h"



Sphere::Sphere(const Eigen::Vector3f& pos, float r)
:Object()
,centre(pos)
,radius(r)
{
    area = 4 * PI * radius;
    assert(r > -0.00001);
}

Sphere::Sphere(float x, float y, float z, float r)
:Object()
,centre(x, y, z)
,radius(r)
{
    area = 4 * PI * radius;
    assert(r > -0.00001);
}


BoundingBox Sphere::getBoundingBox() const
{
    return BoundingBox(centre.x() - radius, centre.y() - radius, centre.z() - radius,
                       centre.x() + radius, centre.y() + radius, centre.z() + radius);
}

float Sphere::getSurfaceArea() const
{
    return area;
}

void Sphere::Sample(Intersection& intersection, float& pdf) const
{
    /*
        uniform sample in a sphere surface
    */
    float a = getRandomFloat();
    float b = getRandomFloat();
    Eigen::Vector3f dir(
        2 * std::cos(2 * PI * b) * std::sqrt(a*(1-a)),
        2 * std::sin(2 * PI * b) * std::sqrt(a*(1-a)),
        (1 - 2 * a)
    );
    // float theta = 2.0 * PI * getRandomFloat(), phi = PI * getRandomFloat();
    // Eigen::Vector3f dir(std::sin(phi)*std::cos(theta), std::sin(phi)*std::sin(theta), std::cos(phi));
    intersection.coordinate = centre + radius * dir;
    intersection.normal = dir;
    intersection.material = material;
    pdf = 1.0f / getSurfaceArea();
}

bool Sphere::isInSurface(Eigen::Vector3f pos) const
{
    Eigen::Vector3f testRadius = pos - centre;
    auto diff = testRadius.norm() - radius;
    return diff > -0.00001 and diff < 0.00001;
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
    if (t0 < -0.00001)
    {   
        /*
            if 0 < t0 < t1, the first intersection should be t0
            if t0 < 0 < t1, it means ray origin is inside sphere, t1 should be the intersection.
        */
        t0 = t1;

        /*
            The sampled point might be just under the sufrace of shpere.
            Of course, we can not say sphere intersected with the ray from the point  to outside(normal direction). 
        */
        if(t0 < 0.1)
        {
            return intersection;
        }
    }
    if (t0 < -0.00001)
    {
        return intersection;
    }

    intersection.isHappened = true;
    intersection.coordinate = ray.getDestinationAfterT(t0);
    intersection.normal = intersection.coordinate - centre;
    intersection.normal = intersection.normal.normalized();
    intersection.material = material;
    intersection.tOfRayWhenIntersected = t0;
    return intersection;
}

