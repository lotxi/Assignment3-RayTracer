#pragma once
#include <vector>

class Vec3
{
public:
	Vec3();
	Vec3(float, float, float);
	float x, y, z;
};

class SceneObject
{
public:
	virtual std::string  to_string() = 0;
	virtual ~SceneObject();
	SceneObject();
	SceneObject(Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess);
	Vec3 ambient, diffuse, specular;
	float shininess;
};

class Camera
{
public:
	Camera();
	Camera(Vec3, float, float, float);
	std::string to_string();
	Vec3 pos;
	float fov, focal_length, aspect_ratio;
	~Camera();
};

class Plane : public SceneObject
{
public:
	Plane();
	Plane(Vec3 normal, Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess);
	Vec3 position, normal;
	std::string to_string();
	~Plane();
};

class Triangle : public SceneObject
{
public:
	Triangle();
	Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess);
	std::string to_string();
	Vec3 v1, v2, v3;
	~Triangle();
};

class Sphere : public SceneObject
{
public:
	Vec3 pos;
	float radius;
	Sphere();
	Sphere(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float radius, float shininess);
	std::string to_string();
	~Sphere();
};

class Light
{
public:
	Vec3 position, color;
	Light();
	Light(Vec3 position, Vec3 color);
	std::string to_string();
	~Light();
};

class Scene
{
public:
	Scene();
	~Scene();
	Camera* camera;
	Plane* ground;
	std::vector<SceneObject*> objects;
	std::vector<Light*> lights;
	std::string to_string();
};