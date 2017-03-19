#include "Sphere.h"





Sphere::Sphere() :
	SceneObject(), pos(glm::vec3()), radius(0)
{

}

Sphere::Sphere(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float radius, float shininess) :
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

float Sphere::Intersect(Ray ray)
{
	float t0, t1;
	glm::vec3 dir = ray.getDirection();
	glm::vec3 L = ray.getOrigin()-pos;
	float a = glm::dot(dir, dir);
	float b = 2 * glm::dot(dir, L);
	float c = glm::dot(L,L) - pow(radius,2);
	if (!solveQuadratic(a, b, c, t0, t1)) return 0;
	if (!solveQuadratic(a, b, c, t0, t1)) return 0;

	if (t0 > t1) std::swap(t0, t1);
	if (t0<0)
	{
		t0 = t1; // Use t1 if t0 is negative
		if (t0 < 0) return 0;
	}
	return t0;
}

Sphere::~Sphere()
{
}

bool Sphere::solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1) const
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}
