#pragma once
#include <glm/glm.hpp>
#include <iostream>

class Camera
{
public:
	Camera();
	Camera(glm::vec3, float, float, float);
	std::string to_string() const;
	glm::vec3 getPosition() const;
	float getFoV() const;
	float getFocalLength() const;
	float getAspectRatio() const;
private:
	glm::vec3 pos;
	float fov, focal_length, aspect_ratio;
	~Camera();
};