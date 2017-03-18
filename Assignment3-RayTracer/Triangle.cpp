#include "Triangle.h"

Triangle::Triangle() :
	SceneObject(), v1(glm::vec3()), v2(glm::vec3()), v3(glm::vec3())
{

}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	SceneObject(ambient, diffuse, specular, shininess), v1(v1), v2(v2), v3(v3)
{

}

std::string Triangle::to_string()
{
	std::string result;
	result += "Triangle\n";
	result += "v1: X" + std::to_string(v1.x) + " Y" + std::to_string(v1.y) + " Z" + std::to_string(v1.z) + "\n";
	result += "v2: X" + std::to_string(v2.x) + " Y" + std::to_string(v2.y) + " Z" + std::to_string(v2.z) + "\n";
	result += "v3: X" + std::to_string(v3.x) + " Y" + std::to_string(v3.y) + " Z" + std::to_string(v3.z) + "\n";
	result += "ambient: R" + std::to_string(ambient.x) + " G" + std::to_string(ambient.y) + " B" + std::to_string(ambient.z) + "\n";
	result += "diffuse: R" + std::to_string(diffuse.x) + " G" + std::to_string(diffuse.y) + " B" + std::to_string(diffuse.z) + "\n";
	result += "specular: R" + std::to_string(specular.x) + " G" + std::to_string(specular.y) + " B" + std::to_string(specular.z) + "\n";
	result += "shininess: " + std::to_string(shininess) + "\n";
	return result;

}

double Triangle::Intersect(Ray ray)
{
	return 0;
}

Triangle::~Triangle()
{
}
