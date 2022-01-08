#ifndef PATHTRACING_MESHTRIANGLE_H
#define PATHTRACING_MESHTRIANGLE_H


#include "Object.h"
#include "Triangle.h"
#include "BVH.h"

/*
    A class of a Object, but includes many meshes.
*/
class MeshTriangle: public Object
{
public:
    MeshTriangle(const std::string& filename, std::shared_ptr<Material> inMaterial);
    virtual BoundingBox getBoundingBox() const;
    virtual float getSurfaceArea() const;
    virtual Intersection getIntersectionWithRay(const Ray& ray);
    virtual void Sample(Intersection& intersection, float& pdf) const;
private:

public:
    std::vector<std::shared_ptr<Object>> triangles;
    std::unique_ptr<BVH> bvh;
private:
    BoundingBox boundingBox;
};




#endif