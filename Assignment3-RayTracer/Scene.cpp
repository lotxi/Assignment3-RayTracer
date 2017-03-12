#include "Scene.h"
#include <string>

Vec3::Vec3():
x(0),y(0),z(0)
{
}

Vec3::Vec3(float x, float y, float z):
x(x),y(y),z(z)
{
}

SceneObject::~SceneObject()
{
}

SceneObject::SceneObject() : ambient(Vec3()), diffuse(Vec3()), specular(Vec3()), shininess(0)
{
}

SceneObject::SceneObject(Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :
	ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{

}


Camera::Camera() : pos(Vec3()), fov(45.0), focal_length(1000), aspect_ratio(1)
{

}

Camera::Camera(Vec3 pos, float fov, float focal_length, float aspect_ratio) :
	pos(pos), fov(fov), focal_length(focal_length), aspect_ratio(aspect_ratio)
{

}

std::string Camera::to_string()
{
	std::string result;
	result += "Camera\n";
	result += "position: X" + std::to_string(pos.x) + " Y" + std::to_string(pos.y) + " Z" + std::to_string(pos.z) + "\n";
	result += "fov: " + std::to_string(fov) + "\n";
	result += "focal length: " + std::to_string(focal_length) + "\n";
	result += "aspect ratio: " + std::to_string(aspect_ratio) + "\n";
	return result;
}

Camera::~Camera()
{
}

Plane::Plane() :
	SceneObject(), position(Vec3()), normal(Vec3())
{
}

Plane::Plane(Vec3 normal, Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :
	SceneObject(ambient, diffuse, specular, shininess), normal(normal), position(position)
{
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

Sphere::Sphere() :
	SceneObject(), pos(Vec3()), radius(0)
{

}

Sphere::Sphere(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float radius, float shininess) :
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

Sphere::~Sphere()
{
}

Triangle::Triangle() :
	SceneObject(), v1(Vec3()), v2(Vec3()), v3(Vec3())
{

}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :
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

Triangle::~Triangle()
{
}

Light::Light() :
	position(Vec3()), color(Vec3())
{

}

Light::Light(Vec3 position, Vec3 color) :
	position(position), color(color)
{
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

Scene::Scene()
{
	camera = nullptr;
	ground = nullptr;
}

Scene::~Scene()
{
}

std::string Scene::to_string()
{
	std::string result = "\n";
	result += camera->to_string() + "\n";
	if (ground != nullptr)
	{
		result += ground->to_string() + "\n";
	}
	
	result += "Lights\n";
	for (int i=0; i<lights.size(); i++)
	{
		result += "#" + std::to_string(i) + " " + lights.at(i)->to_string() + "\n";
	}
	result += "Scene Objects\n";
	for (int i=0; i<objects.size(); i++)
	{
		result += "#" + std::to_string(i) + " " +objects.at(i)->to_string() +"\n";
	}

	return result;
}
