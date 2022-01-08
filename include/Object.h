#ifndef PATHTRACING_OBJECT_H
#define PATHTRACING_OBJECT_H

#include "BoundingBox.h"
#include "Material.h"
#include "OBJ_Loader.hpp"




/*
    An abstract class for all kinds of objects.
*/

namespace objl
{}

class Object
{
public:
    Object()
    :material()
    ,area(0.0f)
    {};
    virtual ~Object(){};


    virtual BoundingBox getBoundingBox() const = 0;
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
        return material->hasEmission();
    }

public:
    std::shared_ptr<Material> material;

protected:
    float area;

};


#endif