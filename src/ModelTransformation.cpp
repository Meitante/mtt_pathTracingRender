#include "ModelTransformation.h"

ModelTransformation::ModelTransformation()
:scale(Eigen::Matrix4f::Identity())
,rotation(Eigen::Matrix4f::Identity())
,translation(Eigen::Matrix4f::Identity())
{

}

void ModelTransformation::setScale(float x, float y, float z)
{
    scale <<  x   , 0.0f, 0.0f, 0.0f,
              0.0f,    y, 0.0f, 0.0f,
              0.0f, 0.0f,    z, 0.0f,
              0.0f, 0.0f, 0.0f,    1;
}

void ModelTransformation::setRotation(float xTheta, float yTheta, float zTheta)
{
    xTheta = getRadianFromDegree(xTheta);
    Eigen::Matrix4f aroundX;
    aroundX <<           1,                 0,                 0,                 0,
                         0,  std::cos(xTheta), -std::sin(xTheta),                 0,
                         0,  std::sin(xTheta),  std::cos(xTheta),                 0,
                         0,                 0,                 0,                 1;     

    yTheta = getRadianFromDegree(yTheta);
    Eigen::Matrix4f aroundY;
    aroundY << std::cos(yTheta),                 0, -std::sin(yTheta),                 0,
                              0,                 1,                 0,                 0,
               std::sin(yTheta),                 0,  std::cos(yTheta),                 0,
                              0,                 0,                 0,                 1;   

    zTheta = getRadianFromDegree(zTheta);
    Eigen::Matrix4f aroundZ;
    aroundZ << std::cos(zTheta),                 -std::sin(zTheta),                 0,                 0,
               std::sin(zTheta),                  std::cos(zTheta),                 0,                 0,
                              0,                                 0,                 1,                 0,
                              0,                                 0,                 0,                 1;   

    rotation = aroundZ*(aroundY*aroundX);
}

void ModelTransformation::setTranslation(float x, float y, float z)
{
    translation <<     1, 0.0f, 0.0f,    x,
                    0.0f,    1, 0.0f,    y,
                    0.0f, 0.0f,    1,    z,
                    0.0f, 0.0f, 0.0f,    1;
}


Eigen::Matrix4f ModelTransformation::getScale() const
{
    return scale;
}
Eigen::Matrix4f ModelTransformation::getRotation() const
{
    return rotation;
}
Eigen::Matrix4f ModelTransformation::getTranslation() const
{
    return translation;
}

Eigen::Vector3f ModelTransformation::getVectorAfterApplyOnVector(const Eigen::Vector3f& target) const
{
    Eigen::Vector4f homogeneous = Eigen::Vector4f(target.x(), target.y(), target.z(), 1);
    homogeneous = translation * (rotation * (scale * homogeneous));
    return Eigen::Vector3f{homogeneous.x()/homogeneous.w(),
                           homogeneous.y()/homogeneous.w(),
                           homogeneous.z()/homogeneous.w()};
}
