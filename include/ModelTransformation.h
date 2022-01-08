#ifndef PATHTRACING_MODELTRANSFORMATION_H
#define PATHTRACING_MODELTRANSFORMATION_H

#include <eigen3/Eigen/Eigen>
#include <utility.hpp>

/*
    The centre is set in (0, 0, 0) at the begin.
*/
class ModelTransformation
{
public:
    ModelTransformation();
    void setScale(float x, float y, float z);
    // Theta as degree measure
    void setRotation(float xTheta, float yTheta, float zTheta);
    void setTranslation(float x, float y, float z);
    Eigen::Matrix4f getScale() const;
    Eigen::Matrix4f getRotation() const;
    Eigen::Matrix4f getTranslation() const;

    Eigen::Vector3f getVectorAfterApplyOnVector(const Eigen::Vector3f& target) const;
private:
    Eigen::Matrix4f scale;
    Eigen::Matrix4f rotation;
    Eigen::Matrix4f translation;
};


#endif