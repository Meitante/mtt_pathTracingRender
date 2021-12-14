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

Intersection Scene::getIntersectionWithRay(const Ray& ray)
{
    // TODO: implement BVH
    for(int i = 0; i < objectList.size(); ++i)
    {   
        if(objectList[i]->getBoundingBox().isIntersectedWithRay(ray))
        {
            auto intersection = objectList[i]->getIntersectionWithRay(ray);
            if(intersection.isHappened)
            {
                return intersection;
            }
        }
    }
    return Intersection(); // isHappened = false
}

Eigen::Vector3f Scene::getColorByTracingRay(const Ray& ray, int depth)
{
    Intersection intersection = getIntersectionWithRay(ray);
    if(intersection.isHappened)
    {
        if(intersection.material.hasEmission())
        {
            return intersection.material.emission;
            if(depth == 0)
            {
                return intersection.material.emission;
            }
            else
            {
                return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
            }
        }

        auto& objCoordinate = intersection.coordinate;
        auto& normalInObj = intersection.normal;

        /*
            L : the radiance
        */
        Eigen::Vector3f dirL(0, 0, 0);
	    Eigen::Vector3f indirL(0, 0, 0);

        // TODO: implement the direct 


        /*
            implement the indirect radiance
        */
       if (getRandomFloat() < RussianRoulette)
		{
            int sb = 0;
            Eigen::Vector3f nextDir = intersection.material.sample(-ray.direction, normalInObj);
            Ray nextRay(objCoordinate, nextDir);
            Intersection nextInter = getIntersectionWithRay(nextRay);
            while(true)
            {   
                if(intersection.material.hasEmission())
                {
                    std::cout << "onlyEmission";
                }
                if(!intersection.material.hasEmission() and !nextInter.material.hasEmission())
                {
                    std::cout << "自己撞自己";
                }
                // if(!intersection.material.hasEmission() and nextInter.material.hasEmission())
                // {
                //     std::cout << "撞到别人 " << std::endl;
                // }
                if(sb > 100)
                {
                    break;
                }
                if((nextInter.isHappened and nextInter.material.hasEmission()))
                {
                    return Eigen::Vector3f(0.0, 0.8f, 0.2);
                    break;
                }
                nextDir = intersection.material.sample(ray.direction, normalInObj);
                nextRay = Ray(objCoordinate, nextDir);
                nextInter = getIntersectionWithRay(nextRay);
                ++sb;
            }

			if (nextInter.isHappened) //&& !nextInter.material.hasEmission())
			{
				float pdf = intersection.material.getPDF(ray.direction, nextDir, normalInObj);
				Eigen::Vector3f BRDF = intersection.material.getBRDF(ray.direction, nextDir, normalInObj);
                Eigen::Vector3f colorFromTracingRay = getColorByTracingRay(nextRay, depth + 1);

				indirL =  Eigen::Vector3f(colorFromTracingRay[0] * BRDF[0], colorFromTracingRay[1] * BRDF[1], colorFromTracingRay[2] * BRDF[2]) 
                        * nextDir.dot(normalInObj) / pdf / RussianRoulette;

                std::cout << "pdf: " << pdf <<
                            "BRDF: " << BRDF[0] << " " << BRDF[1] << " " << BRDF[2] <<
                            "colorFromTracingRay: " << colorFromTracingRay[0] << " " << colorFromTracingRay[1] << " " << colorFromTracingRay[2] <<
                            "indirL: " << indirL[0] << " " << indirL[1] << " " << indirL[2] << std::endl;
			}
		}

        return dirL + indirL;
    }


    

    return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
}