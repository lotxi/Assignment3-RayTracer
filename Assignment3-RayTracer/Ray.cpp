#include "Ray.h"

Ray::Ray()
{
	origin = glm::vec3(0, 0, 0);
	direction = glm::vec3(1, 0, 0);
}

Ray::Ray(glm::vec3 o, glm::vec3 d)
{
	origin = o;
	direction = d;
}

glm::vec3 Ray::getOrigin() const
{
	return origin;
}

glm::vec3 Ray::getDirection() const
{
	return direction;
}

