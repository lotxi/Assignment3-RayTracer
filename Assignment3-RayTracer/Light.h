#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>

class Light
{
public:
	Light();
	Light(glm::vec3 position, glm::vec3 color);
	glm::vec3 getPosition();
	glm::vec3 getColor();
	std::string to_string();
	~Light();

private: 
	glm::vec3 position, color;
	
};