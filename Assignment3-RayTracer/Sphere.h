#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
	Sphere();
	Sphere(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float radius, float shininess);
	std::string to_string();
	double Intersect(Ray ray) override;
	~Sphere();

private:
	glm::vec3 pos;
	float radius;

};
