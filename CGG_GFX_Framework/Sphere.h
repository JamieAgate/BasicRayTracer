#pragma once
#ifndef Sphere_H
#define Sphere_H

#include <iostream>

#include "Object.h"

class Ray;

struct intercept
{
	bool hit;
	float distance;
};

class Sphere : public Object
{
public:
	Sphere(int x, int y, int z, float radius);
	Sphere(int x, int y, int z, float radius, glm::vec3 _colour, float _reflective);
	
	glm::vec3 GetNormal(glm::vec3 _pi) override;

	bool Interception(Ray _A, float& _t) override;

private:

};
#endif
