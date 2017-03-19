#include "Camera.h"
#include <string>

Camera::Camera() : pos(glm::vec3()), fov(45.0), focal_length(1000), aspect_ratio(1)
{

}

Camera::Camera(glm::vec3 pos, float fov, float focal_length, float aspect_ratio) :
	pos(pos), fov(fov), focal_length(focal_length), aspect_ratio(aspect_ratio)
{

}

std::string Camera::to_string() const
{
	std::string result;
	result += "Camera\n";
	result += "position: X" + std::to_string(pos.x) + " Y" + std::to_string(pos.y) + " Z" + std::to_string(pos.z) + "\n";
	result += "fov: " + std::to_string(fov) + "\n";
	result += "focal length: " + std::to_string(focal_length) + "\n";
	result += "aspect ratio: " + std::to_string(aspect_ratio) + "\n";
	return result;
}

glm::vec3 Camera::getPosition() const
{
	return pos;
}

float Camera::getFoV() const
{
	return fov;
}

float Camera::getFocalLength() const
{
	return focal_length;
}

float Camera::getAspectRatio() const
{ 
	return aspect_ratio;
}

Camera::~Camera()
{
}
