#ifndef PATHTRACING_SCENE_H
#define PATHTRACING_SCENE_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <vector>
#include <memory>


#include "Ray.h"
#include "Object.h"
#include "Intersection.h"
#include "BVH.h"


class Scene
{
public:
    Scene(unsigned int w, unsigned int h);
    Scene(const Scene& s) = delete;
    Scene(Scene&& s) = delete;
    ~Scene();

    Eigen::Vector3f getColorByTracingRay(const Ray& ray, int depth = 0);
    void setEyePos(const Eigen::Vector3f& in_eyePos);
    void addObject(std::shared_ptr<Object> obj);
    Intersection getIntersectionWithRay(const Ray& ray);
    void sampleLight(Intersection& intersection, float& pdf) const;
    void buildBVH();

public:
    unsigned int width;
    unsigned int height;
    Eigen::Vector3f eyePos;
    float fov = 40;
    Eigen::Vector3f backgroundColor;
    std::vector<std::shared_ptr<Object>> objectList;
    //TODO: make bvh unique ptr
    BVH* bvh;

private:

};


#endif