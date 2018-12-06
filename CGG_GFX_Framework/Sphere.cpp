#include "Sphere.h"

sphere::sphere(int x, int y, int z, int _radius)
{
	center.x = x;
	center.y = y;
	center.z = z;
	radius = _radius;

	lightOrigin.x = 0;
	lightOrigin.y = 0;
	lightOrigin.z = 1;
}

glm::vec3 sphere::closestPoint(Ray _A, glm::vec3 _b)
{
	return _A.origin + ((_b - _A.origin)*_A.direction) * _A.direction;
}

bool sphere::interception(Ray _A)
{
	float t0, t1;
	// geometric solution
	glm::vec3 L = center - _A.origin;
	float tca = glm::dot(L,_A.direction);
	float d2 = glm::dot(L,L) - tca * tca;
	if (d2 > radius) return false;
	float thc = sqrt(radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	
	float sn = glm::max(glm::dot(glm::vec3(t0, t1,0), glm::vec3(-1, -1,-1)),0.0f);
	colour.x = 225.0f * sn;
	//colour.x = glm::distance(t0,t1);

	if (t0 < 0)
	{
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}
	return true;
}

float sphere::shadeRed(Ray _A, glm::vec3 _b)
{
	return 0;
}