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
	glm::vec3 TraceRay(glm::vec3 _origin, glm::vec3 _dir, std::vector<std::shared_ptr<Object>> _objvector, int _depth);

	void AddLight(glm::vec3 _pos, glm::vec3 _colour, float _intensity);

	enum E_RAY_TYPE {e_diffuse, e_shadow};
private:
	void Fresnel(glm::vec3 _incident, glm::vec3 _normal, float ior, float& kr);
	glm::vec3 Reflect(glm::vec3 _incident, glm::vec3 _normal);
	glm::vec3 Refract(glm::vec3 _incident, glm::vec3 _normal, float _ior);
	bool Intersect(Ray _ray,std::vector<std::shared_ptr<Object>> _objects ,IntersectedObject & _data, E_RAY_TYPE _raytype);
	std::vector<std::shared_ptr<Light>> m_lights;
};

#endif // !Tracer
