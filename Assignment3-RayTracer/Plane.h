#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	Plane();
	Plane(glm::vec3 normal, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	~Plane();
	std::string to_string() override;
	float Intersect(const Ray & ray) const override;
	glm::vec3 getNormalAt(const glm::vec3& point) const override;
private:
	glm::vec3 position, normal;

};
