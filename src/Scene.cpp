#include "Scene.h"



Scene::Scene(unsigned int w, unsigned int h)
:width(w)
,height(h)
,eyePos(0, 0, 0)
{
    backgroundColor = {0.25, 0.5, 0.75};
}


void Scene::setEyePos(const Eigen::Vector3f& in_eyePos)
{
    eyePos = in_eyePos;
}


void Scene::addObject(std::unique_ptr<Object> obj)
{
    objectList.push_back(std::move(obj));
}

Eigen::Vector3f Scene::getColorByTracingRay(const Ray& ray)
{
    for(int i = 0; i < objectList.size(); ++i)
    {   
        if(objectList[i]->getBoundingBox().isIntersectedWithRay(ray))
        {
            auto intersection = objectList[i]->getIntersectionWithRay(ray);
            if(intersection.isHappened)
            {
                return Eigen::Vector3f(1, 0, 0);
            }
        }
        else
        {
            continue;
        }

    }
    return Eigen::Vector3f(0, 0, 0);
}