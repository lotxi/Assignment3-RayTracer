#pragma once
#include <glm/glm.hpp>

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;
public:
	Ray();
	Ray(glm::vec3, glm::vec3);
	glm::vec3 getOrigin() const;
	glm::vec3 getDirection() const;
};