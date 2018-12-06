#include <glm.hpp>
#include "Ray.h"
#include "Sphere.h"
#include <vector>
#ifndef Tracer_H
#define Tracer_H

class Tracer
{
public:
	glm::vec4 tracer(Ray _A);
private:
	std::vector<sphere> objects;
};

#endif // !Tracer
