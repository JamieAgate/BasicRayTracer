#include "Light.h"



Light::Light()
{

}

Light::Light(glm::vec3 _pos, glm::vec3 _colour, float _intensity)
{
	m_lightToWorld = glm::mat4(0.95292, 0.289503, 0.0901785, 0, -0.0960954, 0.5704, -0.815727, 0, -0.287593, 0.768656, 0.571365, 0, 0, 0, 0, 1);

	m_position = glm::vec4(_pos,0.0f) * m_lightToWorld;
	m_colour = _colour;
	m_intensity = _intensity;
}


Light::~Light()
{
}

void Light::Illuminate(glm::vec3 _hitPoint, glm::vec3 & _lightDir, glm::vec3 & _lightIntensity, float _distance)
{
	_lightDir = _hitPoint - m_position;
	float r2 = glm::length(_lightDir);
	_distance = sqrt(r2);
	_lightDir.x /= _distance;
	_lightDir.y /= _distance;
	_lightDir.z /= _distance;
	glm::normalize(_lightDir);
	_lightIntensity = m_colour * m_intensity / glm::vec3(4 * M_PI * r2);
}
