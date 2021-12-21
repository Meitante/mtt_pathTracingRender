#include "Material.h"

Material::Material(MaterialType t, Eigen::Vector3f m)
:type(t)
,emission(m)
,diffuseKd(std::numeric_limits<float>::infinity(), 0, 0)
{

}

bool Material::hasEmission() const
{
    return std::fabs(emission[0] + emission[1] + emission[2]);
}


Eigen::Vector3f Material::sampleStandardDirection() const
{
    /*
        uniform sample in the semisphere
        uniform definition:
            Given any tiny area in the surface, the probability of
            a sampled point locating inside this area is invariant
            whatever which area being considerd.
    */
    float x_1 = getRandomFloat(), x_2 = getRandomFloat();
    float z = std::fabs(1.0f - 2.0f * x_1);
    float r = std::sqrt(1.0f - z * z), phi = 2 * PI * x_2;
    return Eigen::Vector3f(r*std::cos(phi), r*std::sin(phi), z);
}

Eigen::Vector3f Material::getRayWithStandardDirectionAndTargetNormal(const Eigen::Vector3f& stddir, const Eigen::Vector3f& N) const
{
    Eigen::Vector3f B, C;
    if (std::fabs(N.x()) > std::fabs(N.y())){
        float invLen = 1.0f / std::sqrt(N.x() * N.x() + N.z() * N.z());
        C = Eigen::Vector3f(N.z() * invLen, 0.0f, -N.x() *invLen);
    }
    else {
        float invLen = 1.0f / std::sqrt(N.y() * N.y() + N.z() * N.z());
        C = Eigen::Vector3f(0.0f, N.z() * invLen, -N.y() *invLen);
    }
    B = C.cross(N);
    return stddir.x() * B + stddir.y() * C + stddir.z() * N;
}


Eigen::Vector3f Material::sample([[maybe_unused]]const Eigen::Vector3f& wi, const Eigen::Vector3f N) const
{
    switch(type)
    {
        case MaterialType::DIFFUSE:
        {
            return getRayWithStandardDirectionAndTargetNormal(sampleStandardDirection(), N);
            break;
        }
    }
    assert(false);
}

float Material::getPDF([[maybe_unused]]const Eigen::Vector3f &wi, const Eigen::Vector3f &wo, const Eigen::Vector3f &N) const
{
    switch(type)
    {
        case MaterialType::DIFFUSE:
        {
            /*
                uniformly sample probability 1 / (2 * PI)
                but only focus on the situation wo is "above" the semisphere
                possibility will be zero when output is to the contrary side
            */
            if (wo.dot(N) > 0.0f)
                return 0.5f / PI;
            else
                return 0.0f;
            break;
        }
    }
    assert(false);
}

void Material::setDiffuseKd(const Eigen::Vector3f& kd)
{
    assert(type == MaterialType::DIFFUSE);
    diffuseKd = kd;
}

Eigen::Vector3f Material::getBRDF(const Eigen::Vector3f &wi, const Eigen::Vector3f &wo, const Eigen::Vector3f &N) const
{
    switch(type)
    {
        case MaterialType::DIFFUSE:
        {
            // calculate the contribution of diffuse   model
            // TODO: figure out how diffuse brdf get.
            assert(diffuseKd.x() < 1.0f + 0.0001);
            float cosalpha = N.dot(wo);
            if (cosalpha > 0.0f)
            {
                return  diffuseKd / PI;
            }
            else
                return Eigen::Vector3f(0, 0, 0);
            break;
        }
    }
    assert(false);
}


