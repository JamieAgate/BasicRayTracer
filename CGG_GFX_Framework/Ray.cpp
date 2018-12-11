#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"

Ray::Ray(glm::vec2 _origin, float _aspectRatio)
{
	m_origin = glm::vec3(_origin.x,_origin.y,0.0f);

	m_direction = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * glm::perspective(45.0f, _aspectRatio, 0.1f, 10000.0f);
}

Ray::Ray(glm::vec3 _origin, glm::vec3 _dir)
{
	m_origin = _origin;
	m_direction = _dir;
}
