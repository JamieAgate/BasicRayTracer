#ifndef Ray_H
#define Ray_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Ray
{
public:
	Ray();
	Ray(glm::vec2 _origin);

	glm::vec3 GetOrigin() { return m_origin; }
	glm::vec3 GetDirection() { return m_direction; }

private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
};
#endif // !Ray



