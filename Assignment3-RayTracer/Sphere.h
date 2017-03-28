#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
	Sphere();
	Sphere(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float radius, float shininess);
	std::string to_string() override;
	float Intersect(const Ray &ray) const override;
	glm::vec3 getNormalAt(const glm::vec3 &point) const override;
	~Sphere();

private:
	glm::vec3 pos;
	float radius;
	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const;
};
