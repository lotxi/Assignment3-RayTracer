#include "Plane.h"

Plane::Plane() :
	SceneObject(), position(glm::vec3()), normal(glm::vec3())
{
}

Plane::Plane(glm::vec3 normal, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	SceneObject(ambient, diffuse, specular, shininess), normal(normal), position(position)
{
}

double Plane::Intersect(Ray ray)
{
	return 0;
}

glm::vec3 Plane::getPosition() const
{
	return position;
}

glm::vec3 Plane::getNormal() const
{
	return normal;
}


std::string Plane::to_string()
{
	std::string result;
	result += "Plane\n";
	result += "normal: X" + std::to_string(normal.x) + " Y" + std::to_string(normal.y) + " Z" + std::to_string(normal.z) + "\n";
	result += "position: X" + std::to_string(position.x) + " Y" + std::to_string(position.y) + " Z" + std::to_string(position.z) + "\n";
	result += "ambient: R" + std::to_string(ambient.x) + " G" + std::to_string(ambient.y) + " B" + std::to_string(ambient.z) + "\n";
	result += "diffuse: R" + std::to_string(diffuse.x) + " G" + std::to_string(diffuse.y) + " B" + std::to_string(diffuse.z) + "\n";
	result += "specular: R" + std::to_string(specular.x) + " G" + std::to_string(specular.y) + " B" + std::to_string(specular.z) + "\n";
	result += "shininess: " + std::to_string(shininess) + "\n";
	return result;
}

Plane::~Plane()
{
}