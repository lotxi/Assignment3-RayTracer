#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <istream>
#include <cmath>
#include "Scene.h"
#include <iterator>
#pragma once
class InputReader
{
public:
	void ReadCamera();
	static glm::vec3 parseVector(std::string line);
	static float parseFloat(std::string line);
	InputReader();
	void ReadPlane();
	void ReadTriangle();
	void ReadSphere();
	void ReadLight();
	InputReader(std::string file);
	Scene scene;

private:
	std::ifstream input;
};