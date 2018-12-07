#include "Sphere.h"

Sphere::Sphere(int x, int y, int z, float _radius)
{
	m_position = glm::vec3(x, y, z);
	m_radius = _radius;
}

glm::vec3 Sphere::GetNormal(glm::vec3 _pi)
{
	return (_pi - m_position) / m_radius;
}

bool Sphere::Interception(Ray _A,float & _t)
{
	glm::vec3 originToCenter = _A.GetOrigin() - m_position;
	float b = 2 * glm::dot(originToCenter, _A.GetDirection());
	float c = glm::dot(originToCenter, originToCenter) - m_radius * m_radius;
	float disc = b * b - 4 * c;
	if (disc < 1e-4) return false;
	disc = sqrt(disc);
	float t0 = -b - disc;
	float t1 = -b + disc;
	_t = (t0 < t1) ? t0 : t1;
	return true;
}