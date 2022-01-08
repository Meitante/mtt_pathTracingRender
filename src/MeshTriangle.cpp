#include "MeshTriangle.h"


MeshTriangle::MeshTriangle(const std::string& filename,
                            std::shared_ptr<Material> inMaterial,
                            const ModelTransformation& modelTransformation)
:triangles()
,bvh(nullptr)
,boundingBox()
{
    objl::Loader loader;
    if(!loader.LoadFile(filename))
    {
        std::cout << "Loading file failing: " << filename << std::endl;
        assert(false);
    }
    material = inMaterial;
    assert(loader.LoadedMeshes.size() == 1);
    auto mesh = loader.LoadedMeshes[0];
    // Initial the min and max vertex for bounding box.
    Eigen::Vector3f minVertex = Eigen::Vector3f{std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity(),
                                                std::numeric_limits<float>::infinity()};
    Eigen::Vector3f maxVertex = Eigen::Vector3f{-std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity(),
                                                -std::numeric_limits<float>::infinity()};
    
    // For every face/triangle, three vertices determine a face.
    for (int i = 0; i < mesh.Vertices.size(); i += 3)
    {
        std::array<Eigen::Vector3f, 3> faceVertices;
        // Find these three vertices.
        for (int j = 0; j < 3; j++)
        {
            auto vertex = Eigen::Vector3f(mesh.Vertices[i + j].Position.X,
                                          mesh.Vertices[i + j].Position.Y,
                                          mesh.Vertices[i + j].Position.Z);
            vertex = modelTransformation.getVectorAfterApplyOnVector(vertex);
            faceVertices[j] = vertex;
            // update the min and max vertex.
            minVertex = Eigen::Vector3f(std::min(minVertex.x(), vertex.x()),
                                        std::min(minVertex.y(), vertex.y()),
                                        std::min(minVertex.z(), vertex.z()));
            maxVertex = Eigen::Vector3f(std::max(maxVertex.x(), vertex.x()),
                                        std::max(maxVertex.y(), vertex.y()),
                                        std::max(maxVertex.z(), vertex.z()));
        }
        // TODO: a better transformation from triangle to object should be done here.
        auto tri = std::shared_ptr<Object>(new Triangle(faceVertices[0], faceVertices[1],
                                faceVertices[2], material));
        triangles.push_back(tri);
    }

    boundingBox = BoundingBox(minVertex, maxVertex);

    std::vector<std::shared_ptr<Object>> trianglePointerList;
    for(auto tri: triangles)
    {
        trianglePointerList.push_back(tri);
        area += tri->getSurfaceArea();
    }
    bvh = std::make_unique<BVH>(trianglePointerList);
}

BoundingBox MeshTriangle::getBoundingBox() const
{
    return boundingBox;
}

float MeshTriangle::getSurfaceArea() const
{
    return area;
}

Intersection MeshTriangle::getIntersectionWithRay(const Ray& ray)
{
    assert(bvh != nullptr);
    return bvh->getInsectionWithRay(ray);
}

void MeshTriangle::Sample(Intersection& intersection, float& pdf) const
{
    float thresholdP = getRandomFloat();
    float thresholdArea = thresholdP * area;
    int i = 0;
    float areaSum = 0.0f;
    for(i = 0; i < triangles.size();i++)
    {
        areaSum += triangles[i]->getSurfaceArea();
        if(areaSum >= thresholdArea - 0.00001)
        {
            break;
        }    
    }
    triangles[i]->Sample(intersection, pdf);
}
