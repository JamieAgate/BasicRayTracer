#ifndef Tracer_H
#define Tracer_H

#include <glm.hpp>
#include <vector>
#include <memory>

#include "Ray.h"
#include "Object.h"

class Tracer
{
public:
	glm::vec4 TraceRay(int _x, int _y, std::vector<std::shared_ptr<Object>> _objvector);
private:
	void clamp_colour(glm::vec3& _col);
};

#endif // !Tracer
