#include "InputReader.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"


enum object_type
{
	camera,
	light,
	sphere,
	triangle,
	plane,
	errortype
};
object_type hashit(std::string const& input)
{
	if (input == "camera") return camera;
	if (input == "light") return light;
	if (input == "sphere") return sphere;
	if (input == "triangle") return triangle;
	if (input == "plane") return plane;
	return errortype;
}


void InputReader::ReadCamera()
{
	glm::vec3 position;
	float fov, aspect_ratio, focal_length;
	std::string line;
	getline(input, line);
	//Parse camera position
	position = parseVector(line);
	getline(input, line);
	fov = parseFloat(line);
	getline(input, line);
	focal_length = parseFloat(line);
	getline(input, line);
	aspect_ratio = parseFloat(line);

	std::cout << "Finished reading camera" << std::endl;

	// Create camera from inputs
	scene.camera = new Camera(position, fov, focal_length, aspect_ratio);
}

void InputReader::ReadPlane()
{
	glm::vec3 normal, position, ambient, diffuse, specular;
	float shininess;

	std::string line;

	getline(input, line);
	normal = parseVector(line);

	getline(input, line);
	position = parseVector(line);

	getline(input, line);
	ambient = parseVector(line);

	getline(input, line);
	diffuse = parseVector(line);

	getline(input, line);
	specular = parseVector(line);

	getline(input, line);
	shininess = parseFloat(line);

	std::cout << "Finished reading plane" << std::endl;
	// Create plane from inputs
	scene.objects.push_back(new Plane(normal, position, ambient, diffuse, specular, shininess));
}

void InputReader::ReadTriangle()
{
	glm::vec3 v1, v2, v3, ambient, diffuse, specular;
	float shininess;

	std::string line;

	getline(input, line);
	v1 = parseVector(line);

	getline(input, line);
	v2 = parseVector(line);

	getline(input, line);
	v3 = parseVector(line);

	getline(input, line);
	ambient = parseVector(line);

	getline(input, line);
	diffuse = parseVector(line);

	getline(input, line);
	specular = parseVector(line);

	getline(input, line);
	shininess = parseFloat(line);

	std::cout << "Finished reading triangle" << std::endl;
	// Create triangle from inputs
	scene.objects.push_back(new Triangle(v1, v2, v3, ambient, diffuse, specular, shininess));
}



void InputReader::ReadSphere()
{
	glm::vec3 position, ambient, diffuse, specular;
	float radius, shininess;

	std::string line;

	getline(input, line);
	position = parseVector(line);

	getline(input, line);
	radius = parseFloat(line);

	getline(input, line);
	ambient = parseVector(line);

	getline(input, line);
	diffuse = parseVector(line);

	getline(input, line);
	specular = parseVector(line);

	getline(input, line);
	shininess = parseFloat(line);

	std::cout << "Finished reading sphere" << std::endl;
	// Create sphere from inputs
	scene.objects.push_back(new Sphere(position, ambient, diffuse, specular, radius, shininess));
}

void InputReader::ReadLight()
{
	glm::vec3 position, color;

	std::string line;

	getline(input, line);
	position = parseVector(line);

	getline(input, line);
	color = parseVector(line);

	std::cout << "Finished reading light" << std::endl;

	// Create light from inputs
	scene.lights.push_back(new Light(position, color));
}


glm::vec3 InputReader::parseVector(std::string line)
{
	std::stringstream ss(line);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	float x, y, z;
	x = stof(vstrings[1]);
	y = stof(vstrings[2]);
	z = stof(vstrings[3]);

	return glm::vec3(x, y, z);

}

float InputReader::parseFloat(std::string line)
{
	std::stringstream ss(line);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	return stof(vstrings[1]);
}


InputReader::InputReader()
{
	
}

InputReader::~InputReader()
{

}

InputReader::InputReader(std::string file)
{
	input.open(file);
	if (input.is_open())
	{
		std::string line;
		std::vector<std::string> currentObject;
		getline(input, line);
		std::cout << line << std::endl;
		int objectCount = stoi(line); // Read number of objects in scene

		for (int i = 0; i < objectCount; i++) // For each object, read the objects data from file
		{
			getline(input, line); // Read object type
			switch (hashit(line))
			{
			case camera:
				std::cout << "Reading camera..." << std::endl;
				ReadCamera();
				break;
			case plane:
				std::cout << "Reading plane..." << std::endl;
				ReadPlane();
				break;
			case triangle:
				std::cout << "Reading triangle..." << std::endl;
				ReadTriangle();
				break;
			case sphere:
				std::cout << "Reading sphere..." << std::endl;
				ReadSphere();
				break;
			case light:
				std::cout << "Reading light..." << std::endl;
				ReadLight();
				break;
			default:
				break;
			}
		}

		if (scene.camera != nullptr)
		{
			scene.build_scene();
		}
	}
}
