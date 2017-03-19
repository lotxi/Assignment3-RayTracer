#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	Plane();

	Plane(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);
	~Plane();
	std::string to_string() override;
	virtual float Intersect(Ray ray);
	glm::vec3 getPosition() const;
	glm::vec3 getNormal() const;
private:
	glm::vec3 position, normal;

};
