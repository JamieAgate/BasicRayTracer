#include "Tracer.h"

Tracer::Tracer()
{
}

glm::vec4 Tracer::TraceRay(glm::vec3 _origin, glm::vec3 _dir, std::vector<std::shared_ptr<Object>> _objVector, int _depth)
{
	Ray currentRay(_origin, _dir);
	IntersectedObject data;

	if (!Intersect(currentRay, _objVector, data) || _depth > 3)
	{
		return glm::vec4(0.0f, 50.0f, 100.0f, 1.0f);
	}
	
	glm::vec4 colour = glm::vec4(0.0f);
	glm::vec3 hitPoint = currentRay.GetOrigin() + currentRay.GetDirection() * data.t;
	glm::vec3 normal = data.object.lock()->GetNormal(hitPoint);
	float dt = 0;
	glm::vec3 reflect = glm::vec3(0.0f);

	for (std::shared_ptr<Light> l : m_lights)
	{
		glm::vec3 lightDir, lightIntensity;
		l->Illuminate(hitPoint, lightDir, lightIntensity, data.t);
		Ray ray(hitPoint + normal * 0.0001f, lightDir);
		IntersectedObject lightData;
		dt = glm::dot(glm::normalize(lightDir), glm::normalize(normal));
		bool vis = Intersect(ray, _objVector, lightData);
		if (vis)
		{
			colour += glm::vec4(lightIntensity * data.object.lock()->GetColour() * l->GetColour() * std::max(0.0f,glm::dot(normal,-lightDir)), 0.0f);
		}
	}
	
	if (data.object.lock()->GetReflective() > 0.0f)
	{
		reflect = Reflect(currentRay.GetDirection(), normal);
		glm::normalize(reflect);
		colour += glm::vec4(data.object.lock()->GetReflective()) * TraceRay(hitPoint + (glm::normalize(normal) * 0.0001f), reflect, _objVector, _depth++);
	}

	return glm::clamp(colour,0.0f,255.0f);
}

bool Tracer::Intersect(Ray _ray, std::vector<std::shared_ptr<Object>> _objects,  IntersectedObject & _data)
{
	std::vector<std::weak_ptr<Object>> interacredObj;

	for (std::shared_ptr<Object> obj : _objects)
	{
		if (obj->Interception(_ray, _data.t))
		{
			interacredObj.push_back(obj);
		}
	}

	if (interacredObj.size() == 0)
	{
		return false;
	}

	std::weak_ptr<Object> obj = interacredObj.front();
	float tempT = _data.t;
	obj.lock()->Interception(_ray, _data.t);

	if (interacredObj.size() > 1)
	{
		for (std::weak_ptr<Object> object : interacredObj)
		{
			object.lock()->Interception(_ray, tempT);

			if (tempT < _data.t)
			{
				_data.t = tempT;
				_data.object = object;
			}
		}
		if (_data.object.lock() != nullptr)
		{
			return true;
		}
	}
	else
	{
		_data.object = obj;
		if (_data.object.lock() != nullptr)
		{
			return true;
		}
	}

	return false;
}

glm::vec3 Tracer::Reflect(glm::vec3 _incident, glm::vec3 _normal)
{
	return _incident - 2 * glm::dot(_incident, _normal) * _normal;
}

void Tracer::AddLight(glm::vec3 _pos, glm::vec3 _colour, float _intensity)
{
	m_lights.push_back(std::make_shared<Light>(_pos, _colour, _intensity));
}

