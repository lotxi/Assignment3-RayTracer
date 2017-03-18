#include "Sphere.h"





Sphere::Sphere() :
	SceneObject(), pos(glm::vec3()), radius(0)
{

}

Sphere::Sphere(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float radius, float shininess) :
	SceneObject(ambient, diffuse, specular, shininess), pos(position), radius(radius)
{
}

std::string Sphere::to_string()
{
	std::string result;
	result += "Sphere\n";
	result += "position: X" + std::to_string(pos.x) + " Y" + std::to_string(pos.y) + " Z" + std::to_string(pos.z) + "\n";
	result += "rad: " + std::to_string(radius) + "\n";
	result += "ambient: R" + std::to_string(ambient.x) + " G" + std::to_string(ambient.y) + " B" + std::to_string(ambient.z) + "\n";
	result += "diffuse: R" + std::to_string(diffuse.x) + " G" + std::to_string(diffuse.y) + " B" + std::to_string(diffuse.z) + "\n";
	result += "specular: R" + std::to_string(specular.x) + " G" + std::to_string(specular.y) + " B" + std::to_string(specular.z) + "\n";
	result += "shininess: " + std::to_string(shininess) + "\n";
	return result;

}

double Sphere::Intersect(Ray ray)
{
	return 0;
}

Sphere::~Sphere()
{
}
