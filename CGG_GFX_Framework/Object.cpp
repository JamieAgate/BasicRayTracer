#include "Object.h"

Object::Object()
{
	m_colour = glm::vec3(255.0f, 0.0f, 0.0f);
	m_reflectivness = 0;
}

Object::Object(glm::vec3 _colour, float _type)
{
	m_colour = _colour;
	m_reflectivness = _type;
}


Object::~Object()
{
}
