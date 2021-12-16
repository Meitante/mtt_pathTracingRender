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
    Intersection resIntersection;
    for(int i = 0; i < objectList.size(); ++i)
    {   
        if(objectList[i]->getBoundingBox().isIntersectedWithRay(ray))
        {
            auto intersection = objectList[i]->getIntersectionWithRay(ray);
            if(intersection.isHappened and intersection.tOfRayWhenIntersected < resIntersection.tOfRayWhenIntersected)
            {
                resIntersection = intersection;
            }
        }
    }
    return resIntersection;
}

void Scene::sampleLight(Intersection& intersection, float& pdf) const
{
    for (uint32_t k = 0; k < objectList.size(); ++k)
    {
        if (objectList[k]->hasEmission())
        {
            objectList[k]->Sample(intersection, pdf);
            break;
        }
    }
    return;

    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objectList.size(); ++k)
    {
        if (objectList[k]->hasEmission())
        {
            emit_area_sum += objectList[k]->getSurfaceArea();
        }
    }
    float p = getRandomFloat() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objectList.size(); ++k)
    {
        if (objectList[k]->hasEmission())
        {
            emit_area_sum += objectList[k]->getSurfaceArea();
            if (p <= emit_area_sum)
            {
                objectList[k]->Sample(intersection, pdf);
                break;
            }
        }
    }
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
            implement the direct radiance
        */
		Intersection lightIntersection;
		float lightPDF = 0.0f;
		sampleLight(/*out*/lightIntersection, /*out*/lightPDF);

		auto& N = intersection.normal;
		auto& NN = lightIntersection.normal;
		auto& objPos = intersection.coordinate;
		auto& lightPos = lightIntersection.coordinate;
		auto diff = lightPos - objPos;
		auto lightDir = diff.normalized();
		float lightDistanceSquare = diff.dot(diff);

		Ray light(objPos, lightDir);
		Intersection light2obj = getIntersectionWithRay(light);
        // std::cout << std::endl;
        // if(!intersection.material.hasEmission())
        // {
        //     // return Eigen::Vector3f(0, 1.0f, 0.0f);
        //     // std::cout << "ff" << std::endl;
        //     if(!light2obj.material.hasEmission())
        //     {
        //         return Eigen::Vector3f(0, 0.0f, 1.0f);
        //         std::cout << "光线击中非发光体 " << std::endl;
        //         std::cout << "objPos: " << objPos[0] << " " << objPos[1] << " " << objPos[2] << " " <<std::endl;
        //         std::cout << "lightPos: " << lightPos[0] << " " << lightPos[1] << " " << lightPos[2] << " " <<std::endl;
        //         return Eigen::Vector3f(0, 0.0f, 0.0f);
        //     }
        //     if(light2obj.material.hasEmission())
        //     {
        //         return Eigen::Vector3f(0, 1.0f, 0.0f);  
        //         std::cout << "光线击中发光体 " << std::endl;
        //         std::cout << "objPos: " << objPos[0] << " " << objPos[1] << " " << objPos[2] << " " <<std::endl;
        //         std::cout << "lightPos: " << lightPos[0] << " " << lightPos[1] << " " << lightPos[2] << " " <<std::endl;
                
                
        //     }
        // }
        // return Eigen::Vector3f(0.0, 0.0f, 1.0f);

        // if (light2obj.isHappened)
        // {
        //     return Eigen::Vector3f(0, 0.8f, 0.2f);
        // }
        // else
        // {
        //     return Eigen::Vector3f(0, 0.0f, 0.0f);
        // }

        if (light2obj.isHappened and (light2obj.coordinate - lightPos).norm() < 0.01f)
        // if (light2obj.isHappened and light2obj.material.hasEmission())
		{
            // return Eigen::Vector3f(0, 0.8f, 0.2f);
            auto& lightEmission = lightIntersection.material.emission;
			Eigen::Vector3f BRDF = intersection.material.getBRDF(ray.direction, lightDir, N);
			dirL = 1.0f * Eigen::Vector3f(lightEmission[0] * BRDF[0], lightEmission[1] * BRDF[1], lightEmission[2] * BRDF[2])
                    * lightDir.dot(N) 
                    * (-lightDir).dot(NN) / lightDistanceSquare / lightPDF;
            
            // std::cout << "lightPDF: " << lightPDF <<
            //             "lightDistance:" << lightDistanceSquare <<
                        
            //             "BRDF: " << BRDF[0] << " " << BRDF[1] << " " << BRDF[2] <<
            //             "lightEmission: " << lightEmission[0] << " " << lightEmission[1] << " " << lightEmission[2] <<
            //             "dirL: " << dirL[0] << " " << dirL[1] << " " << dirL[2] << std::endl;

            // std::cout << "dirL: " << dirL[0] << " " << dirL[1] << " " << dirL[2] << std::endl;
		}
        // else
        // {
        //     return Eigen::Vector3f(0, 0.0f, 0.0f);
        // }

        // return dirL + indirL;
        /*
            implement the indirect radiance
        */
       if (getRandomFloat() < RussianRoulette)
		{
            
            Eigen::Vector3f nextDir = intersection.material.sample(-ray.direction, normalInObj);
            nextDir.normalize();
            Ray nextRay(objCoordinate, nextDir);
            Intersection nextInter = getIntersectionWithRay(nextRay);
            // int sb = 0;
            // while(true)
            // {   
            //     if(intersection.material.hasEmission())
            //     {
            //         std::cout << "onlyEmission";
            //     }
            //     if(!intersection.material.hasEmission() and !nextInter.material.hasEmission())
            //     {
            //         std::cout << "自己撞自己";
            //     }
            //     // if(!intersection.material.hasEmission() and nextInter.material.hasEmission())
            //     // {
            //     //     std::cout << "撞到别人 " << std::endl;
            //     // }
            //     if(sb > 100)
            //     {
            //         break;
            //     }
            //     if((nextInter.isHappened and nextInter.material.hasEmission()))
            //     {
            //         return Eigen::Vector3f(0.0, 0.8f, 0.2);
            //         break;
            //     }
            //     nextDir = intersection.material.sample(ray.direction, normalInObj);
            //     nextRay = Ray(objCoordinate, nextDir);
            //     nextInter = getIntersectionWithRay(nextRay);
            //     ++sb;
            // }

			if (nextInter.isHappened && !nextInter.material.hasEmission())
			{
				float pdf = intersection.material.getPDF(ray.direction, nextDir, normalInObj);
				Eigen::Vector3f BRDF = intersection.material.getBRDF(ray.direction, nextDir, normalInObj);
                Eigen::Vector3f colorFromTracingRay = getColorByTracingRay(nextRay, depth + 1);

				indirL =  Eigen::Vector3f(colorFromTracingRay[0] * BRDF[0], colorFromTracingRay[1] * BRDF[1], colorFromTracingRay[2] * BRDF[2]) 
                        * nextDir.dot(normalInObj) / pdf / RussianRoulette;

                // std::cout << "pdf: " << pdf <<
                //             "BRDF: " << BRDF[0] << " " << BRDF[1] << " " << BRDF[2] <<
                //             "colorFromTracingRay: " << colorFromTracingRay[0] << " " << colorFromTracingRay[1] << " " << colorFromTracingRay[2] <<
                //             "indirL: " << indirL[0] << " " << indirL[1] << " " << indirL[2] << std::endl;
                std::cout << "indirL: " << indirL[0] << " " << indirL[1] << " " << indirL[2] << std::endl;
			}
		}

        return dirL + indirL;
    }


    

    return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
}