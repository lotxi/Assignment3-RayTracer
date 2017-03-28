#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Plane.h"
#include "Triangle.h"
#include "Light.h"


class Scene
{
public:
	Scene();
	bool build_scene();
	~Scene();
	Camera* camera;
	std::vector<SceneObject*> objects;
	std::vector<Light*> lights;
	std::string to_string();
	int width;
	int height;
};