#include "BVH.h"

BVH::BVHNode::BVHNode()
:boundingbox()
,left(nullptr)
,right(nullptr)
,object(nullptr)
,totalArea(0.0f)
{

}


BVH::BVH(std::vector<std::shared_ptr<Object>> ObjectList, int maxObjectsInNode, SplitMethod splitMethod)
:root(nullptr)
,splitMethod(splitMethod)
,objectList(ObjectList)
,maxObjectsInNode(std::min(100, maxObjectsInNode))
{
    std::cout << "Generating BVH" << std::endl;
    if (objectList.empty())
    {
        return;
    }
    root = buildBVH(objectList);
}

BVH::~BVH()
{

}

BVH::BVHNode* BVH::buildBVH(std::vector<std::shared_ptr<Object>> objects)
{
    switch (splitMethod)
    {
    case SplitMethod::NAIVE:
        return buildNaiveBVH(objects);
        break;
    
    default:
        assert(false);
    }
}

BVH::BVHNode* BVH::buildNaiveBVH(std::vector<std::shared_ptr<Object>> objects)
{
    BVH::BVHNode* node = new BVH::BVHNode();

    // Compute bounds of all primitives in BVH node
    BoundingBox bounds;
    for (int i = 0; i < objects.size(); ++i)
    {
        bounds = getUnion(bounds, objects[i]->getBoundingBox());
    }
    if (objects.size() == 1)
    {
        // Create leaf _BVHBuildNode_
        node->boundingbox = objects[0]->getBoundingBox();
        node->object = objects[0];
        node->left = nullptr;
        node->right = nullptr;
        node->totalArea = objects[0]->getSurfaceArea();
        return node;
    }
    else if (objects.size() == 2)
    {
        node->left = buildNaiveBVH(std::vector{objects[0]});
        node->right = buildNaiveBVH(std::vector{objects[1]});

        node->boundingbox = getUnion(node->left->boundingbox, node->right->boundingbox);
        node->totalArea = node->left->totalArea + node->right->totalArea;
        return node;
    }
    else
    {
        BoundingBox centroidBounds;
        for (int i = 0; i < objects.size(); ++i)
        {
            centroidBounds = getUnion(centroidBounds, objects[i]->getBoundingBox().getCentroid());
        }
 
        int dim = centroidBounds.getTheDimensionWithMaxLength();
        switch (dim)
        {
        case 0:
            std::sort(objects.begin(), objects.end(), [](auto f1, auto f2)
            {
                return f1->getBoundingBox().getCentroid().x() <
                       f2->getBoundingBox().getCentroid().x();
            });
            break;
        case 1:
            std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
                return f1->getBoundingBox().getCentroid().y() <
                       f2->getBoundingBox().getCentroid().y();
            });
            break;
        case 2:
            std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
                return f1->getBoundingBox().getCentroid().z() <
                       f2->getBoundingBox().getCentroid().z();
            });
            break;
        }

        auto beginning = objects.begin();
        auto middling = objects.begin() + (objects.size() / 2);
        auto ending = objects.end();

        auto leftshapes = std::vector<std::shared_ptr<Object>>(beginning, middling);
        auto rightshapes = std::vector<std::shared_ptr<Object>>(middling, ending);

        assert(objects.size() == (leftshapes.size() + rightshapes.size()));
        std::cout << "good" << std::endl;
        node->left = buildNaiveBVH(leftshapes);
        node->right = buildNaiveBVH(rightshapes);

        node->boundingbox = getUnion(node->left->boundingbox, node->right->boundingbox);
        node->totalArea = node->left->totalArea + node->right->totalArea;
    }

    return node;
}

Intersection BVH::getInsectionWithRay(const Ray& ray) const
{
    if(nullptr == root)
    {
        return Intersection();
    }
    return getInsectionWithRay(root, ray);
}

Intersection BVH::getInsectionWithRay(BVHNode* node, const Ray& ray) const
{
    if(node->boundingbox.isIntersectedWithRay(ray))
    {
        if(nullptr == node->left and nullptr == node->right)
        {
            return node->object->getIntersectionWithRay(ray);
        }
        else
        {
            Intersection inter1 = BVH::getInsectionWithRay( node->left, ray);
            Intersection inter2 = BVH::getInsectionWithRay( node->right, ray);
            return inter1.tOfRayWhenIntersected > inter2.tOfRayWhenIntersected ? inter2 : inter1;          
        }
    }
    else
    {
        return Intersection();
    }
}
