#include "Sphere.h"

Sphere::Sphere(int x, int y, int z, float _radius)
	: Object()
{
	m_position = glm::vec3(x, y, z);
	m_radius = _radius;
}

Sphere::Sphere(int x, int y, int z, float _radius, glm::vec3 _colour, float _reflective)
	: Object(_colour, _reflective)
{
	m_objectToWorld = glm::mat4(0.0f);
	m_objectToWorld[0][0] = 10.0f;
	m_objectToWorld[1][1] = 10.0f;
	m_objectToWorld[2][2] = 10.0f;
	m_objectToWorld[3][2] = -40.0f;
	m_position = glm::vec4(x, y, z,0.0f) * m_objectToWorld;
	m_radius = _radius;
}

glm::vec3 Sphere::GetNormal(glm::vec3 _pi)
{
	return (_pi - m_position) / m_radius;
}

bool Sphere::Interception(Ray _A,float & _t)
{
	glm::vec3 originToCenter = _A.GetOrigin() - m_position;

	float a = glm::dot(_A.GetDirection(), _A.GetDirection());
	float b = 2 * glm::dot(_A.GetDirection(), originToCenter);
	float c = glm::dot(originToCenter, originToCenter) - m_radius * m_radius;

	float discr = b * b - 4 * a*c;

	float t0 = 0.0f , t1 = 0.0f;
	if (discr < 0) return false;
	else if (discr == 0)
	{
		t0 = t1 = -0.5f * b / a;
	}
	else
	{
		float q = (b > 0) ?
			-0.5f * (b + sqrt(discr)) :
			-0.5f * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0) return false;
	}

	_t = t0;

	return true;

	/*float tca = glm::dot(originToCenter, _A.GetDirection());
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
	return false;*/
}