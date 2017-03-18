#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Ray.h"

class SceneObject
{
public:
	virtual std::string  to_string() = 0;
	virtual ~SceneObject();
	SceneObject();
	SceneObject(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

protected:
	virtual double Intersect(Ray) = 0;
	glm::vec3 ambient, diffuse, specular;
	float shininess;
};
