#include "SceneObject.h";


SceneObject::SceneObject() : ambient(glm::vec3()), diffuse(glm::vec3()), specular(glm::vec3()), shininess(0)
{
}

SceneObject::SceneObject(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{

}
