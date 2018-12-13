#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm.hpp>
#include <cmath>

# define M_PI 3.14159265358979323846

class Light
{
public:
	Light();
	Light(glm::vec3 _pos, glm::vec3 _colour, float _intensity);
	~Light();

	glm::vec3 GetColour() { return m_colour; }

	void Illuminate(glm::vec3 _hitPoint, glm::vec3& _lightDir, glm::vec3& _lightIntensity, float _distance);

private:
	glm::vec3 m_position;
	glm::vec3 m_colour;

	glm::mat4 m_lightToWorld;

	float m_intensity;
};

#endif // !_LIGHT_H_



