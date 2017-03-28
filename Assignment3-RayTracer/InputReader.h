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
	InputReader();
	~InputReader();
	InputReader(std::string file);
	Scene scene;

private:
	std::ifstream input;
	void ReadCamera();
	void ReadPlane();
	void ReadTriangle();
	void ReadSphere();
	void ReadLight();
	static glm::vec3 parseVector(std::string line);
	static float parseFloat(std::string line);
};