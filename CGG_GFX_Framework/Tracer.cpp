#include "Tracer.h"

glm::vec4 Tracer::TraceRay(int _x, int _y, std::vector<std::shared_ptr<Object>> _objVector)
{
	float t;

	glm::vec2 coord(_x, _y);
	Ray currentRay(coord);

	std::vector<std::weak_ptr<Object>> interacredObj;

	for (std::shared_ptr<Object> obj : _objVector)
	{
		if (obj->Interception(currentRay, t))
		{
			interacredObj.push_back(obj);
		}
	}

	if (interacredObj.size() == 0)
	{
		return glm::vec4(0.0f);
	}

	std::weak_ptr<Object> obj = interacredObj.front();
	float tempT;
	obj.lock()->Interception(currentRay, t);

	if (interacredObj.size() > 1)
	{
		for (std::weak_ptr<Object> object : interacredObj)
		{
			object.lock()->Interception(currentRay, tempT);

			if (tempT < t)
			{
				t = tempT;
				obj = object;
			}
		}
	}
	

	glm::vec3 pi = currentRay.GetOrigin() + currentRay.GetDirection() * t;
	glm::vec3 LightDir = glm::vec3(450.0f, 450.0f, 0.0f) - pi;
	glm::vec3 Normal = obj.lock()->GetNormal(pi);
	float dt = glm::dot(glm::normalize(LightDir), glm::normalize(Normal));

	glm::vec3 colour = (obj.lock()->GetColour() + glm::vec3(255.0f) * dt) * 0.5f;
	clamp_colour(colour);
	return glm::vec4(colour, 1.0f);
}

void Tracer::clamp_colour(glm::vec3& _col)
{
	_col.x = (_col.x > 255) ? 255 : (_col.x < 0) ? 0 : _col.x;
	_col.y = (_col.y > 255) ? 255 : (_col.y < 0) ? 0 : _col.y;
	_col.z = (_col.z > 255) ? 255 : (_col.z < 0) ? 0 : _col.z;
}