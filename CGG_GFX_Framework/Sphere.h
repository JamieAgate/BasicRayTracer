#include <glm.hpp>
#include <iostream>
#include "Ray.h"

#ifndef Sphere_H
#define Sphere_H

class Ray;

struct intercept
{
	bool hit;
	int distance;
};

class sphere
{
public:
	sphere(int x, int y, int z, float radius);

	glm::vec3 GetNormal(glm::vec3 _pi);
	bool interception(Ray _A, float & _t);

	int getRad() { return radius; }
	glm::vec3 getCent() { return center; }
	glm::vec3 colour;
private:
	glm::vec3 lightOrigin; 
	glm::vec3 lightDir;
	glm::vec3 center;
	float radius;
};
#endif
