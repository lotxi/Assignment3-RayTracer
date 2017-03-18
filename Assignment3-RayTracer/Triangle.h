#pragma once
#include "SceneObject.h"

class Triangle : public SceneObject
{
public:
	Triangle();
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	std::string to_string();
	double Intersect(Ray ray) override;
	~Triangle();
private:
	glm::vec3 v1, v2, v3;
};
