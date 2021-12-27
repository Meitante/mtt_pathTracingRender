#include "Triangle.h"

Triangle::Triangle(const Eigen::Vector3f& v0, const Eigen::Vector3f& v1, const Eigen::Vector3f& v2)
:Object()
,vertex0(v0)
,vertex1(v1)
,vertex2(v2)
,edge1(vertex1 - vertex0)
,edge2(vertex2 - vertex0)
,normal((edge1.cross(edge2)).normalized())
,area((edge1.cross(edge2)).norm()*0.5f)
{
    assert(vertex0 != vertex1 and vertex1 != vertex2 and vertex2 != vertex0);
}


BoundingBox Triangle::getBoundingBox() const
{
    auto maxOf3 = [=](float x, float y, float z)->float{return std::max<float>(std::max<float>(x, y), z);};
    auto minOf3 = [=](float x, float y, float z)->float{return std::min<float>(std::min<float>(x, y), z);};
    return BoundingBox(
        minOf3(vertex0[0], vertex1[0], vertex2[0]),
        minOf3(vertex0[1], vertex1[1], vertex2[1]),
        minOf3(vertex0[2], vertex1[2], vertex2[2]),
        maxOf3(vertex0[0], vertex1[0], vertex2[0]),
        maxOf3(vertex0[1], vertex1[1], vertex2[1]),
        maxOf3(vertex0[2], vertex1[2], vertex2[2])
    );
}

/*
    surfaceArea is only about one side, but not both side
*/
float Triangle::getSurfaceArea() const
{
    return area;
}

Intersection Triangle::getIntersectionWithRay(const Ray& ray)
{
    Intersection intersection;
    // TODO:understand it
    if (ray.direction.dot(normal) > 0)
        return intersection;
    float u, v, t_tmp = 0;
    Eigen::Vector3f S1 = ray.direction.cross(edge2);
    float det = edge1.dot(S1);
    if (std::fabs(det) < 0.00001)
        return intersection;

    float invDet = 1. / det;
    Eigen::Vector3f S = ray.origin - vertex0;
    u = S.dot(S1) * invDet;
    if (u < 0 || u > 1)
        return intersection;
    Eigen::Vector3f S2 = S.cross(edge1);
    v = ray.direction.dot(S2) * invDet;
    if (v < 0 || u + v > 1)
        return intersection;
    t_tmp = edge2.dot(S2) * invDet;
    if (t_tmp < 0)
    {
        return intersection;
    }

    
    intersection.isHappened = true;
    intersection.coordinate = ray.getDestinationAfterT(t_tmp);
    intersection.normal = normal;
    intersection.tOfRayWhenIntersected = t_tmp;
    intersection.material = material; 

    return intersection;
}


void Triangle::Sample(Intersection& intersection, float& pdf) const
{
    float x = std::sqrt(getRandomFloat());
    float y = getRandomFloat();
    intersection.coordinate =  vertex0 + x * edge1 + x * y * (vertex2 - vertex1);
    intersection.normal = normal;
    intersection.material = material;
    pdf = 1.0f/area;
}


/*
    Points in edges are judged as being inside
*/
bool Triangle::isInside(const Eigen::Vector3f& p) const
{
    //TODO: maybe a fast implement
    Eigen::Vector3f edge(vertex1 - vertex0);
    Eigen::Vector3f testPointLine(p - vertex0);
    Eigen::Vector3f cross010p = edge.cross(testPointLine);

    edge = vertex2 - vertex1;
    testPointLine = p - vertex1;
    Eigen::Vector3f cross121p = edge.cross(testPointLine);

    edge = vertex0 - vertex2;
    testPointLine = p - vertex2;
    Eigen::Vector3f cross202p = edge.cross(testPointLine);
    
    if(cross010p.dot(cross121p) >= -0.00001f and cross121p.dot(cross202p) >= -0.00001f and cross202p.dot(cross010p) >= -0.00001f)
    {
        return true;
    }
    return false;
}
