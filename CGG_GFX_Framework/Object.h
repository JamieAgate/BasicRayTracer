#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <glm.hpp>

#include "Ray.h"

class Object
{
public:
	Object();
	~Object();

	virtual bool Interception(Ray _ray, float& _t) { return false; }
	virtual glm::vec3 GetNormal(glm::vec3 _pi) { return glm::vec3(0.0f); }

	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetColour() { return m_colour; }

protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	float m_radius;

	glm::vec3 m_colour;
};

#endif // !_OBJECT_H_


