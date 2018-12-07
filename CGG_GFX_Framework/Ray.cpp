#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"

Ray::Ray(glm::vec2 _origin)
{
	m_origin = glm::vec3(_origin.x,_origin.y,0.0f);
	m_direction = glm::vec3(0, 0, 1.0f);
}
