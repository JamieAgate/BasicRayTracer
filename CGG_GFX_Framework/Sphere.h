#include <glm.hpp>
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
	sphere(int x, int y, int z, int radius);

	float shadeRed(Ray _A, glm::vec3 _b);
	int shadeGreen(Ray _A, glm::vec3 _b);
	int shadeBlue(Ray _A, glm::vec3 _b);

	glm::vec3 closestPoint(Ray _A, glm::vec3 _b);
	bool interception(Ray _A);
	glm::vec3 normal(glm::vec3 center, glm::vec3 _a);

	int getRad() { return radius; }
	glm::vec3 getCent() { return center; }
	glm::vec3 colour;
private:
	glm::vec3 lightOrigin; 
	glm::vec3 lightDir;
	glm::vec3 center;
	int radius;
};
#endif
