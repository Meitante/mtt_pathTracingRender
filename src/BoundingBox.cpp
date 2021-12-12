#include "BoundingBox.h"



BoundingBox::BoundingBox()
:pMin(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest())
,pMax(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
{

}

BoundingBox::BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
:pMin(minX, minY, minZ)
,pMax(maxX, maxY, maxZ)
{

}


BoundingBox::BoundingBox(const BoundingBox& b)
{
    pMin = b.pMin;
    pMax = b.pMax;
}

Eigen::Vector3f BoundingBox::getDiagonal() const
{
    return Eigen::Vector3f(pMax[0] - pMin[0], pMax[1] - pMin[1], pMax[2] - pMin[2]);
}

bool BoundingBox::isIntersectedWithRay(const Ray& ray)
{
    Eigen::Vector3f invDir(1.0f/ray.direction.x(), 1.0f/ray.direction.y(), 1.0f/ray.direction.z());
    std::vector<bool> dirIsPositive{ray.direction.x() > -0.00001, ray.direction.y() > -0.00001, ray.direction.z() > -0.00001};

	float tEnter = -std::numeric_limits<float>::infinity();
	float tExit = std::numeric_limits<float>::infinity();
	for (int i = 0; i < 3; i++)
	{
		float min = (pMin[i] - ray.origin[i]) * invDir[i];
		float max = (pMax[i] - ray.origin[i]) * invDir[i];
		if (!dirIsPositive[i])
		{
			std::swap(min, max);
		}
		tEnter = std::max(min, tEnter);
		tExit = std::min(max, tExit);
	}
	return tEnter <= tExit && tExit >= 0;
}






