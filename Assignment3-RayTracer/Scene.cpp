#include "Scene.h"
#include <string>
#include <iostream>
#include <glm/detail/type_mat.hpp>

Scene::Scene()
{
	camera = nullptr;
	width = 0;
	height = 0;
}

bool Scene::build_scene()
{
	// Calculate height
	height = glm::round(tan(glm::radians(camera->getFoV() / 2)) * 2 * camera->getFocalLength());
	//Calculate width
	width = glm::round(camera->getAspectRatio()*height);


	std::cout << width << " x " << height << std::endl;
	// For each pixel, convert the coordinate from screen space to world space

	return true;
}

Scene::~Scene()
{
	//delete camera;
	//for (auto light: lights)
	//{
	//	delete light;
	//  light = nullptr;
	//}
	//for (auto object: objects)
	//{
	//	delete object;
	//}
}

std::string Scene::to_string()
{
	std::string result = "\n";
	result += camera->to_string() + "\n";
	
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

