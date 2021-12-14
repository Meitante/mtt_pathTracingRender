#ifndef PATHTRACING_OBJECT_H
#define PATHTRACING_OBJECT_H

#include "BoundingBox.h"
#include "Material.h"




/*
    An abstract class for all kinds of objects.
*/

class Object
{
public:
    Object()
    :material()
    {};
    virtual ~Object(){};


    virtual BoundingBox getBoundingBox() = 0;
    virtual float getSurfaceArea() = 0;
    virtual Intersection getIntersectionWithRay(const Ray& ray) = 0;

public:
    Material material;

};


#endif