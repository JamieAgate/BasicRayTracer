#include <glm.hpp>
#include "Ray.h"
#include <gtc/matrix_transform.hpp>

#ifndef Camera_H
#define Camera_H

class Camera
{
public:
	Ray createRay(glm::vec2 _a);
private:
	glm::mat4 viewing;
	glm::mat4 projection;
};
#endif // !Camera
