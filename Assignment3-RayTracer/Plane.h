#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	Plane();
	Plane(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);
	~Plane();
	std::string to_string();
	double Intersect(Ray ray) override;
private:
	glm::vec3 position, normal;

};
