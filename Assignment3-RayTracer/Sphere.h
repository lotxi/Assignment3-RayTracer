#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
	Sphere();
	Sphere(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float radius, float shininess);
	std::string to_string() override;
	virtual float Intersect(Ray ray);
	~Sphere();

private:
	glm::vec3 pos;
	float radius;
	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const;
};
