#include "Tracer.h"

Tracer::Tracer()
{
}

glm::vec3 Tracer::TraceRay(glm::vec3 _origin, glm::vec3 _dir, std::vector<std::shared_ptr<Object>> _objVector, int _depth)
{
	Ray currentRay(_origin, _dir);
	IntersectedObject data;

	if (!Intersect(currentRay, _objVector, data, e_diffuse) || _depth > 6)
	{
		return glm::vec3(0.0f, 50.0f, 100.0f);
	}
	
	glm::vec3 colour = glm::vec4(0.0f);
	glm::vec3 hitPoint = currentRay.GetOrigin() + currentRay.GetDirection() * data.t;
	glm::vec3 normal = data.object.lock()->GetNormal(hitPoint);
	float dt = 0;
	glm::vec3 reflect = glm::vec3(0.0f);

	switch (data.object.lock()->GetReflective())
	{
	case(1):
		{
			//reflect = Reflect(currentRay.GetDirection(), normal);
			//glm::normalize(reflect);
			//colour += data.object.lock()->GetReflective() * TraceRay(hitPoint + (glm::normalize(normal) * 0.0001f), reflect, _objVector, _depth++);

			glm::vec3 refractionColor(0.0f), reflectionColor(0.0f);
			// compute fresnel
			float kr, ior = 1.6f;
			Fresnel(_dir, normal, ior, kr);
			bool outside = glm::dot(normal, _dir) < 0.0f;
			glm::vec3 bias = 0.001f * normal;
			// compute refraction if it is not a case of total internal reflection
			if (kr < 1) {
				glm::vec3 refractionDirection = glm::normalize(Refract(_dir, normal, ior));
				glm::vec3 refractionRayOrig = outside ? hitPoint - bias : hitPoint + bias;
				refractionColor = TraceRay(refractionRayOrig, refractionDirection, _objVector, _depth+ 1);
			}

			glm::vec3 reflectionDirection = glm::normalize(Reflect(_dir, normal));
			glm::vec3 reflectionRayOrig = outside ? hitPoint + bias : hitPoint - bias;
			reflectionColor = TraceRay(reflectionRayOrig, reflectionDirection, _objVector, _depth+ 1);

			// mix the two
			colour += (data.object.lock()->GetColour() * 0.3f) + (reflectionColor * kr + refractionColor * (1 - kr));
			break;
		}
	case(0):
		{
			for (std::shared_ptr<Light> l : m_lights)
			{
				glm::vec3 lightDir, lightIntensity;
				IntersectedObject lightData;
				l->Illuminate(hitPoint, lightDir, lightIntensity, lightData.t);
				Ray ray(hitPoint + normal * 0.001f, -lightDir);
				bool vis = !Intersect(ray, _objVector, lightData, e_shadow);
				if (vis)
				{
					colour += lightIntensity * data.object.lock()->GetColour() * std::max(0.0f, glm::dot(normal, -lightDir));
				}
			}
			break;
		}
	default:
		//return glm::vec4(0.0f, 50.0f, 100.0f, 1.0f);
		break;
	}
	return glm::clamp(colour,0.0f,255.0f);
}

void Tracer::Fresnel(glm::vec3 _incident, glm::vec3 _normal, float _ior, float & _kr)
{
	float cosi = glm::clamp(glm::dot(_incident,_normal),-1.0f,1.0f);
	float etai = 1, etat = _ior;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		_kr = 1;
	}
	else {
		float cost = sqrtf(std::max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		_kr = (Rs * Rs + Rp * Rp) / 2;
	}
}

bool Tracer::Intersect(Ray _ray, std::vector<std::shared_ptr<Object>> _objects,  IntersectedObject & _data, E_RAY_TYPE _raytype)
{
	float t = INFINITY;
	_data.object.lock() = nullptr;
	for (std::shared_ptr<Object> obj : _objects)
	{
		if (obj->Interception(_ray, _data.t))
		{
			if (_data.t < t);
			{
				if (obj->GetReflective() > 0.0f && _raytype == e_shadow) continue;
				_data.object = obj;
				t = _data.t;
			}
		}
	}

	return (_data.object.lock() != nullptr);
}

glm::vec3 Tracer::Reflect(glm::vec3 _incident, glm::vec3 _normal)
{
	return _incident - 2 * glm::dot(_incident, _normal) * _normal;
}

glm::vec3 Tracer::Refract(glm::vec3 _incident, glm::vec3 _normal, float _ior)
{
	float cosi = glm::clamp(glm::dot(_incident, _normal),-1.0f,1.0f);
	float etai = 1, etat = _ior;
	glm::vec3 n = _normal;
	if (cosi < 0) 
	{ 
		cosi = -cosi; 
	}
	else 
	{ 
		std::swap(etai, etat); 
		n = -_normal; 
	}
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	if(k < 0.0f)
	{
		return glm::vec3(0.0f);
	}

	return eta * _incident + (eta * cosi - sqrtf(k)) * n;
}

void Tracer::AddLight(glm::vec3 _pos, glm::vec3 _colour, float _intensity)
{
	m_lights.push_back(std::make_shared<Light>(_pos, _colour, _intensity));
}

