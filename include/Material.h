#ifndef PATHTRACING_MATERIAL_H
#define PATHTRACING_MATERIAL_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
#include <eigen3/Eigen/Eigen>
#include <cmath>
#include "utility.hpp"

class Material
{
public:
    enum MaterialType
    {
        DIFFUSE
    };
    Material(MaterialType t = MaterialType::DIFFUSE, Eigen::Vector3f m = {0, 0, 0});
    
    bool hasEmission() const;
    Eigen::Vector3f sample(const Eigen::Vector3f& wi, const Eigen::Vector3f N) const;
    float getPDF(const Eigen::Vector3f &wi, const Eigen::Vector3f &wo, const Eigen::Vector3f &N) const;
    Eigen::Vector3f getBRDF(const Eigen::Vector3f &wi, const Eigen::Vector3f &wo, const Eigen::Vector3f &N) const;
    void setDiffuseKd(const Eigen::Vector3f& kd);

private:
    /*
        A standard direction is about the semisphere where normal being (0, 0, 1),
        also with length = 1
    */
    Eigen::Vector3f sampleStandardDirection() const;
    Eigen::Vector3f getRayWithStandardDirectionAndTargetNormal(const Eigen::Vector3f& stddir, const Eigen::Vector3f& N) const;


public:
    MaterialType type;
    Eigen::Vector3f emission; // emision color

private:
    Eigen::Vector3f diffuseKd;

};

#endif