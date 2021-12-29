#ifndef PATHTRACING_BVH_H
#define PATHTRACING_BVH_H

#include <eigen3/Eigen/Eigen>
#include <vector>
#include <assert.h>
#include "Object.h"
#include "memory"

class BVH
{
public:
    enum class SplitMethod
    {
        NAIVE
    };

    class BVHNode
    {
    public:
        BVHNode();

        BoundingBox boundingbox;
        BVHNode* left;
        BVHNode* right;
        std::shared_ptr<Object> object;
        float totalArea;
    };

public:
    BVH(std::vector<std::shared_ptr<Object>> ObjectList, int maxObjectsInNode = 1, SplitMethod splitMethod = SplitMethod::NAIVE);
    ~BVH();

    Intersection getInsectionWithRay(const Ray& ray) const;
    Intersection getInsectionWithRay(BVHNode* node, const Ray& ray) const;

private:
    BVHNode* buildBVH(std::vector<std::shared_ptr<Object>> objects);
    BVHNode* buildNaiveBVH(std::vector<std::shared_ptr<Object>> objects);
public:

private:
    BVHNode* root;
    SplitMethod splitMethod;
    std::vector<std::shared_ptr<Object>> objectList;
    unsigned int maxObjectsInNode;
    
};


#endif