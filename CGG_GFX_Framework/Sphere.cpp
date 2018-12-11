#include "Sphere.h"

Sphere::Sphere(int x, int y, int z, float _radius)
{
	m_position = glm::vec3(x, y, z);
	m_radius = _radius;
}

Sphere::Sphere(int x, int y, int z, float _radius, glm::vec3 _colour, float _reflective)
	: Object(_colour, _reflective)
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
	glm::vec3 originToCenter = m_position - _A.GetOrigin();
	float tca = glm::dot(originToCenter, _A.GetDirection());
	if (tca < 0) return false;
	float d2 = glm::dot(originToCenter, originToCenter) - tca * tca;
	if (d2 > m_radius * m_radius) return false;
	float thc = sqrt(m_radius * m_radius - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 < 0) t0 = t1;
	if (t0 < INFINITY)
	{
		_t = t0;
		return true;
	}
	return false;
}