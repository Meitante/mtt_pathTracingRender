#ifndef PATHTRACING_MESHTRIANGLE_H
#define PATHTRACING_MESHTRIANGLE_H

#include "Object.h"
#include "Triangle.h"

/*
    A class of a Object, but includes many meshes.
*/
class MeshTriangle: public Object
{
public:
    MeshTriangle(const std::string& filename, const Material& inMaterial = Material());

private:

public:
    std::vector<Triangle> triangles;
    BoundingBox boundingBox;
private:


};




#endif