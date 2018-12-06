#include "Sphere.h"

sphere::sphere(int x, int y, int z, float _radius)
{
	center.x = x;
	center.y = y;
	center.z = z;
	radius = _radius;

	lightOrigin.x = 0.0f;
	lightOrigin.y = 0.0f;
	lightOrigin.z = 1.0f;
}

glm::vec3 sphere::GetNormal(glm::vec3 _pi)
{
	return (_pi - center) / radius;
}

bool sphere::interception(Ray _A,float & _t)
{
	// geometric solution
	glm::vec3 originToCenter = _A.origin - center;
	float b = 2 * glm::dot(originToCenter, _A.direction);
	float c = glm::dot(originToCenter, originToCenter) - radius * radius;
	float disc = b * b - 4 * c;
	if (disc < 1e-4) return false;
	disc = sqrt(disc);
	float t0 = -b - disc;
	float t1 = -b + disc;
	_t = (t0 < t1) ? t0 : t1;
	return true;
}