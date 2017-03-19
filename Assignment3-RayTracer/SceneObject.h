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
	glm::vec3 getAmbient() const { return ambient; }
	glm::vec3 getDiffuse() const { return diffuse; }
	glm::vec3 getSpecular() const { return specular; }
	float getShininess() const { return shininess; }

protected:
	virtual float Intersect(Ray) = 0;
	glm::vec3 ambient, diffuse, specular;
	float shininess;
};
