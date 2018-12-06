#include "Camera.h"

Ray Camera::createRay(glm::vec2 _a)
{
	Ray rtn;
	rtn.origin = glm::vec3(_a.x,_a.y,0);
	rtn.direction = glm::vec3(0,0,1);

	rtn.direction = glm::vec3(glm::perspective(45.0f, 1.0f,-1.0f,1.0f) * glm::vec4(rtn.direction,1));
	rtn.origin = glm::vec3(glm::perspective(45.0f, 1.0f,-1.0f,1.0f) * glm::vec4(rtn.origin,1)); 
	return rtn;
}