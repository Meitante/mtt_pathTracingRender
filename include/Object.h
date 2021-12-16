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
    virtual float getSurfaceArea() const = 0 ;
    virtual Intersection getIntersectionWithRay(const Ray& ray) = 0;
    /*
        randomly sample a point in the surface,
        intersection information is outputed as the point,
        also output PDF
    */
    virtual void Sample(Intersection& intersection, float& pdf) const = 0;
    virtual bool hasEmission() const
    {
        return material.hasEmission();
    }

public:
    Material material;

};


#endif