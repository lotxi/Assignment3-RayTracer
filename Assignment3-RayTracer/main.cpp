#include "Scene.h"
#include "InputReader.h"
#include "Sphere.h"
#include <cimg/CImg.h>
#include "Plane.h"
#include <thread>
#define MAX_RAY_DEPTH = 5;

const float ambient_light = 1.0;
const int sample_count = 10;
double accuracy = 0.00001;
const int max_ray_depth = 10;
int count = 0;
glm::vec3 cam_dir = glm::vec3(0, 0, -1);
glm::vec3 cam_down = glm::vec3(0, -1, 0);
glm::vec3 cam_right = glm::vec3(1, 0, 0);

float saturate(float x)
{
	if (x > 255.f)
	{
		return 255.f;
	}
	if (x < 0)
	{
		return 0.f;
	}
	return x;
}

glm::vec3 saturate(glm::vec3 c)
{
	glm::vec3 result = glm::vec3(saturate(c.x), saturate(c.y), saturate(c.z));

	return result;
}

void writeImage(glm::vec3* pixels, int width, int height)
{
	cimg_library::CImg<float> image(width, height, 1, 3, 0);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			float red = pixels[index].x * 255;
			float green = pixels[index].y * 255;
			float blue = pixels[index].z * 255;
			image(x, height - y - 1, 0, 0) = red;
			image(x, height - y - 1, 0, 1) = green;
			image(x, height - y - 1, 0, 2) = blue;
		}
	}
	image.normalize(0, 255);
	image.save("render.bmp");
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
	{
		main_disp.wait();
	}
}

int closest(const std::vector<float>& intersections)
{
	int index_min;
	// Prevent unneeded calculations
	if (intersections.size() == 0) // No intersections were found
	{
		return -1;
	}

	if (intersections.size() == 1) // Only one intersection found
	{
		if (intersections[0] > accuracy) // Make sure the distance is greater than 0
		{
			return 0;
		}
		return -1; // The only intersection distance is negative

	}
	// Determine the closest intersection to camera
	double max = 0;
	for (int i = 0; i < intersections.size(); i++)
	{
		if (intersections[i] > max) max = intersections[i];
	}
	// Starting from the maximum value, find the minimum positive value
	if (max > 0)
	{
		for (int i = 0; i < intersections.size(); i++)
		{
			if (intersections[i] > 0 && intersections[i] <= max)
			{
				max = intersections.at(i);
				index_min = i;
			}
		}
		return index_min;
	}
	return -1;

}

float getRandomFloat(const float &low, const float &high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}


glm::vec3 getColorAt(const glm::vec3& intersection_position, const glm::vec3& intersection_direction, const std::vector<SceneObject*>& objects, const std::vector<Light*>& lights, int index, double accuracy, int depth)
{
	//Ambient color
	glm::vec3 color = ambient_light*objects.at(index)->getAmbient();

	glm::vec3 surface_diffuse = objects.at(index)->getDiffuse();
	glm::vec3 surface_specular = objects.at(index)->getSpecular();
	float surface_shininess = objects.at(index)->getShininess();
	glm::vec3 object_normal = normalize(objects.at(index)->getNormalAt(intersection_position));


	glm::vec3 final_color = color;

	if (depth < max_ray_depth && surface_shininess > 0)
	{
		//reflection from objects with specular intensity
		float dot1 = dot(object_normal, -intersection_direction);
		glm::vec3 scalar1 = dot1 * object_normal;
		glm::vec3 add1 = scalar1 + intersection_direction;
		glm::vec3 scalar2 = add1 * 2.f;
		glm::vec3 add2 = scalar2 - intersection_direction;
		glm::vec3 reflection_direction = normalize(add2);
		glm::vec3 reflection_ray_origin = intersection_position + (0.01f*reflection_direction);

		Ray reflection_ray(reflection_ray_origin, reflection_direction);
		// Determine the first object the reflection ray intersects first
		std::vector<float> reflection_intersections;
		for (int reflection_index = 0; reflection_index < objects.size(); reflection_index++)
		{
			reflection_intersections.push_back(objects.at(reflection_index)->Intersect(reflection_ray));
		}
		int index_closest_reflection = closest(reflection_intersections);
		if (index_closest_reflection >= 0)
		{

			if (reflection_intersections.at(index_closest_reflection) > accuracy) {
				glm::vec3 reflection_position = intersection_position + reflection_intersections.at(index_closest_reflection) * reflection_direction;


				glm::vec3 reflection_intersection_color = getColorAt(reflection_position, reflection_direction, objects, lights, index_closest_reflection, accuracy, depth + 1);
				final_color += reflection_intersection_color*0.25f;//*objects.at(index)->getShininess();
			}

		}
	}

	for (int light_index = 0; light_index < lights.size(); light_index++)
	{
		glm::vec3 light_direction = normalize(lights.at(light_index)->getPosition() - intersection_position);
		float cosine_angle = dot(object_normal, light_direction);
		if (cosine_angle > 0)
		{
			// Check for shadows
			bool shadowed = false;
			float distance_to_light = length(lights.at(light_index)->getPosition() - intersection_position);
			glm::vec3 shadow_ray_origin = intersection_position + light_direction*(float)0.3;
			Ray shadow_ray(shadow_ray_origin, light_direction);
			std::vector<float> secondary_intersections;
			for (int object_index = 0; object_index < objects.size(); object_index++)
			{
				secondary_intersections.push_back(objects.at(object_index)->Intersect(shadow_ray));
			}
			int index_closest = closest(secondary_intersections);
			if (index_closest >= 0)
			{
				if (secondary_intersections[index_closest] > accuracy && secondary_intersections[index_closest] <= distance_to_light)
				{
					shadowed = true;
					break;
				}
			}

			if (!shadowed) {
				glm::vec3 addedLight = glm::vec3(0, 0, 0);

				glm::vec3 diffuse = surface_diffuse * std::max((float)0, cosine_angle);

				glm::vec3 r = glm::normalize(2 * dot(light_direction, object_normal) * object_normal - light_direction);
				float rDotL = dot(r, -intersection_direction);
				if (rDotL > accuracy) {
					glm::vec3 specular = surface_specular * std::max((float)0, pow(rDotL, surface_shininess));

					//addedLight += lights.at(light_index)->getColor()*(diffuse + specular);
					addedLight.x += lights.at(light_index)->getColor().x*(diffuse.x + specular.x);
					addedLight.y += lights.at(light_index)->getColor().y*(diffuse.y + specular.y);
					addedLight.z += lights.at(light_index)->getColor().z*(diffuse.z + specular.z);
				}
				else
				{
					//addedLight += lights.at(light_index)->getColor()*(diffuse);
					addedLight.x += lights.at(light_index)->getColor().x*diffuse.x;
					addedLight.y += lights.at(light_index)->getColor().y*diffuse.y;
					addedLight.z += lights.at(light_index)->getColor().z*diffuse.z;
				}
				final_color += addedLight;
			}
		}

	}
	return saturate(final_color);
}


void computePixels(const int & xMin, const int &  xMax, const int &yMin, const int &yMax, const Scene &scene, glm::vec3* pixels)
{
	int width = scene.width;
	int height = scene.height;

	float aspect_ratio = scene.camera->getAspectRatio();
	glm::vec3 Cam_ray_origin = scene.camera->getPosition();
	float fov = glm::radians(scene.camera->getFoV());

	for (int x = xMin; x < xMax; x++)
	{
		for (int y = yMin; y < yMax; y++)
		{
			std::vector<glm::vec3> samples;

			for (int i = 0; i < sample_count; i++)
			{
				float offset_x = getRandomFloat(0, 1);
				float offset_y = getRandomFloat(0, 1);
				float xamt, yamt;
				// Compute values for the ray direction
				if (width > height)
				{
					xamt = ((x + offset_x) / width)*aspect_ratio - (((width - height) / (float)height) / 2);
					yamt = ((height - y) + offset_y) / height;
				}
				else if (height > width)
				{
					xamt = (x + offset_x) / width;
					yamt = (((height - y) + offset_y) / height) / aspect_ratio - (((height - width) / (float)width) / 2);
				}
				else
				{
					// The image is square
					xamt = (x + offset_x) / width;
					yamt = ((height - y) + offset_y) / height;
				}
				std::vector<float> intersections;
				glm::vec3 Cam_ray_direction = glm::normalize(cam_dir + cam_right*static_cast<float>(xamt - 0.5) + cam_down*static_cast<float>(yamt - 0.5));
				Ray cam_ray(Cam_ray_origin, Cam_ray_direction);
				for (int j = 0; j < scene.objects.size(); j++)
				{
					intersections.push_back(scene.objects[j]->Intersect(cam_ray));
				}
				int index_closest = closest(intersections);
				int index = y*width + x;

				if (index_closest >= 0)
				{
					// Determine the position / direction vectors at intersection point
					if (intersections.at(index_closest) > accuracy)
					{
						glm::vec3 intersection_position = Cam_ray_origin + (Cam_ray_direction*intersections.at(index_closest));
						glm::vec3 intersection_color = getColorAt(intersection_position, Cam_ray_direction, scene.objects, scene.lights, index_closest, accuracy, 0);
						samples.push_back(intersection_color);
						/*pixels[index].x = intersection_color.x;
						pixels[index].y = intersection_color.y;
						pixels[index].z = intersection_color.z;*/
					}
				}
				else
				{
					samples.push_back(glm::vec3(0, 0, 0));
					/*	pixels[index].x = 0;
					pixels[index].y = 0;
					pixels[index].z = 0;*/
				}

			}

			glm::vec3 sum(0, 0, 0);
			for (int i = 0; i < samples.size(); i++)
			{
				sum += samples.at(i);
			}
			glm::vec3 color(0, 0, 0);
			color.x = sum.x / sample_count;
			color.y = sum.y / sample_count;
			color.z = sum.z / sample_count;

			int index = y*width + x;
			pixels[index] = color;

		}
	}
}

int main()
{


	InputReader* input = new InputReader("scene7.txt");

	Scene scene = input->scene;

	int width = scene.width;
	int height = scene.height;
	int numPixels = width * height;
	glm::vec3* pixels = new glm::vec3[numPixels];
	//glm::vec3* pixels = new glm::vec3[numPixels];

	float aspect_ratio = scene.camera->getAspectRatio();
	glm::vec3 Cam_ray_origin = scene.camera->getPosition();
	float fov = glm::radians(scene.camera->getFoV());



	srand(static_cast <unsigned>(time(0)));
	int xMid, yMid;
	xMid = ceil(width / 2);
	yMid = ceil(height / 2);


	const clock_t begin_time = clock();
	std::vector<std::thread> threads;
	threads.push_back(std::thread(computePixels, 0,xMid, 0, yMid, scene, pixels));
	threads.push_back(std::thread(computePixels, 0, xMid, yMid, height, scene, pixels));
	threads.push_back(std::thread(computePixels, xMid, width, 0, yMid, scene,pixels));
	threads.push_back(std::thread(computePixels, xMid, width, yMid, height, scene,pixels));
	//void computePixels(glm::vec3* pixels, const int & xMin, const int &  xMax, const Scene &scene)

	std::cout << "synchronizing all threads...\n";
	for (auto& th : threads) th.join();

	std::cout << "Reached end of raycast loop after " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
	writeImage(pixels, width, height);

	return 0;

}
