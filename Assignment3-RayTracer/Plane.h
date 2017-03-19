#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	Plane();

	Plane(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);
	~Plane();
	std::string to_string() override;
	float Intersect(Ray ray) override;
	glm::vec3 getPosition() const;
	glm::vec3 getNormalAt(glm::vec3 point) override;
private:
	glm::vec3 position, normal;

};
