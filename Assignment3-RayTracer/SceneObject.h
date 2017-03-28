#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Ray.h"

class SceneObject
{
public:
	virtual ~SceneObject() = default;
	virtual std::string  to_string() = 0;
	virtual float Intersect(const Ray&) const= 0;
	virtual glm::vec3 getNormalAt(const glm::vec3 & point) const = 0;
	SceneObject();
	SceneObject(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	glm::vec3 getAmbient() const { return ambient; }
	glm::vec3 getDiffuse() const { return diffuse; }
	glm::vec3 getSpecular() const { return specular; }
	float getShininess() const { return shininess; }


protected:
	glm::vec3 ambient, diffuse, specular;
	float shininess;
};
