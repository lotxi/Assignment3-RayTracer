#include "Light.h"

Light::Light() :
	position(glm::vec3()), color(glm::vec3())
{

}

Light::Light(glm::vec3 position, glm::vec3 color) :
	position(position), color(color)
{
}

glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec3 Light::getColor()
{
	return color;
}

std::string Light::to_string()
{
	std::string result;
	result += "Light\n";
	result += "position: X" + std::to_string(position.x) + " Y" + std::to_string(position.y) + " Z" + std::to_string(position.z) + "\n";
	result += "color: R" + std::to_string(color.x) + " G" + std::to_string(color.y) + " B" + std::to_string(color.z) + "\n";
	return result;
}

Light::~Light()
{
}
