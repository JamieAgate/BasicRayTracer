#ifndef Tracer_H
#define Tracer_H

#include <glm.hpp>
#include <vector>
#include <memory>
#include <algorithm>

#include "Ray.h"
#include "Object.h"
#include "Light.h"

struct IntersectedObject
{
	std::weak_ptr<Object> object;
	float t = 0.0f;
};

class Tracer
{
public:
	Tracer();
	glm::vec4 TraceRay(glm::vec3 _origin, glm::vec3 _dir, std::vector<std::shared_ptr<Object>> _objvector, int _depth);

	bool Intersect(Ray _ray,std::vector<std::shared_ptr<Object>> _objects ,IntersectedObject & _data);

	glm::vec3 Reflect(glm::vec3 _incident, glm::vec3 _normal);

	void AddLight(glm::vec3 _pos, glm::vec3 _colour, float _intensity);
private:
	std::vector<std::shared_ptr<Light>> m_lights;

};

#endif // !Tracer
