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
