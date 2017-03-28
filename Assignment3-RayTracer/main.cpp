#include "Scene.h"
#include "InputReader.h"
#include "Sphere.h"
#include <cimg/CImg.h>
#include "Plane.h"
#include <thread>
#include <mutex>

const int sample_count = 25;
const int thread_count = 10;
const double accuracy = 0.00001;
const int max_ray_depth = 4;
const float ambient_constant = 0.75;
const float reflectivity_constant = 0.3;
const glm::vec3 cam_dir = glm::vec3(0, 0, -1);
const glm::vec3 cam_down = glm::vec3(0, -1, 0);
const glm::vec3 cam_right = glm::vec3(1, 0, 0);

// Clamp a float to [0,1]
float saturate(const float &f)
{
	if (f > 1.f)
	{
		return 1.f;
	}
	if (f < 0)
	{
		return 0.f;
	}
	return f;
}

// Clamp a vec3 of floats to [0, 255]
glm::vec3 saturate(const glm::vec3 &color)
{
	return glm::vec3(saturate(color.x), saturate(color.y), saturate(color.z));
}

// Writes color data from an array of vec3s to a bitmap file
void writeImage(glm::vec3* pixels, const int &width, const int &height, const std::string &FileName)
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
	//image.normalize(0, 255); 
	image.save((FileName + ".bmp").c_str());
	/*cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
	{
		main_disp.wait();
	}*/
}

int closest(const std::vector<float>& intersections)
{
	int index_min;
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
	for (unsigned int i = 0; i < intersections.size(); i++)
	{
		if (intersections[i] > max) max = intersections[i];
	}
	// Starting from the maximum value, find the minimum positive value
	if (max > 0)
	{
		for (unsigned int i = 0; i < intersections.size(); i++)
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

// Returns a random float within the specified range (incluisve)
float getRandomFloat(const float &low, const float &high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

glm::vec3 getColorAt(const glm::vec3& intersection_position, const glm::vec3& intersection_direction, const std::vector<SceneObject*>& objects, const std::vector<Light*>& lights, const int& index, const int& depth)
{
	// Add base ambient colour
	auto final_color = ambient_constant*objects.at(index)->getAmbient();

	auto surface_diffuse = objects.at(index)->getDiffuse();
	auto surface_specular = objects.at(index)->getSpecular();
	auto surface_shininess = objects.at(index)->getShininess();
	auto object_normal = normalize(objects.at(index)->getNormalAt(intersection_position));
	float minimum_distance;

	if (depth < max_ray_depth && surface_shininess > 0)
	{
		//Add reflection from objects with shininess
		auto reflection_direction = normalize((dot(object_normal, -intersection_direction) * object_normal + intersection_direction)*2.f - intersection_direction);
		auto reflection_ray_origin = intersection_position + (0.01f*reflection_direction);


		Ray reflection_ray(reflection_ray_origin, reflection_direction);
		// Determine the first object the reflection ray intersects with
		minimum_distance = INFINITY;
		int closest_index = -1;
		for (unsigned int reflection_index = 0; reflection_index < objects.size(); reflection_index++)
		{
			float distance = objects.at(reflection_index)->Intersect(reflection_ray);
			if (distance < minimum_distance && distance > accuracy)
			{
				minimum_distance = distance;
				closest_index = reflection_index;
			}
		}
		// If the ray intersected an object, calcul
		if (closest_index >= 0)
		{
			glm::vec3 reflection_position = intersection_position + minimum_distance * reflection_direction;
			glm::vec3 reflection_intersection_color = getColorAt(reflection_position, reflection_direction, objects, lights, closest_index, depth + 1);
			final_color += reflection_intersection_color*reflectivity_constant;
		}

	}

	// Cycle through each light and add its colour to the surface if the surface is not in shadow
	for (auto light : lights)
	{
		auto light_position = light->getPosition();
		auto light_direction = normalize(light_position - intersection_position);
		auto cosine_angle = dot(object_normal, light_direction);

		if (cosine_angle > 0)
		{
			// Check for shadows
			bool shadowed = false;
			auto distance_to_light = length(light_position - intersection_position);
			auto shadow_ray_origin = intersection_position + light_direction*(float)0.1;
			Ray shadow_ray(shadow_ray_origin, light_direction);

			minimum_distance = INFINITY;
			int closest_index = -1;
			for (unsigned int object_index = 0; object_index < objects.size(); object_index++)
			{
				auto distance = objects.at(object_index)->Intersect(shadow_ray);
				if (distance<minimum_distance && distance > accuracy)
				{
					minimum_distance = distance;
					closest_index = object_index;
				}
			}
			if (closest_index >= 0)
			{
				if (minimum_distance <= distance_to_light)
				{
					shadowed = true;
					break;
				}
			}

			if (!shadowed) { // The surface is not in shadow, add color from this light source
				auto light_color = light->getColor();
				auto addedLight = glm::vec3(0, 0, 0);
				auto diffuse = surface_diffuse * std::max((float)0, cosine_angle);

				auto r = glm::normalize(2 * dot(light_direction, object_normal) * object_normal - light_direction);
				auto rDotL = dot(r, -intersection_direction);

				// If the dot product is not negative, add diffuse and specular component from light
				if (rDotL > accuracy) {
					auto specular = surface_specular * std::max((float)0, pow(rDotL, surface_shininess));
					addedLight.x += light_color.x*(diffuse.x + specular.x);
					addedLight.y += light_color.y*(diffuse.y + specular.y);
					addedLight.z += light_color.z*(diffuse.z + specular.z);
				}
				else // Add only diffuse component from light
				{
					addedLight.x += light->getColor().x*diffuse.x;
					addedLight.y += light->getColor().y*diffuse.y;
					addedLight.z += light->getColor().z*diffuse.z;
				}
				final_color += addedLight;
			}
		}

	}
	return saturate(final_color);
}



// Compute the colour of pixels in the specified range
void computePixels(const int xMin, const int xMax, const int yMin, const int yMax, const Scene &scene, glm::vec3* pixels)
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

			// Average the specified number of samples from the pixel
			for (int i = 0; i < sample_count; i++)
			{
				// Offset the ray direction by a random amount
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
				glm::vec3 Cam_ray_direction = glm::normalize(cam_dir + cam_right*static_cast<float>(xamt - 0.5) + cam_down*static_cast<float>(yamt - 0.5));
				Ray cam_ray(Cam_ray_origin, Cam_ray_direction);

				int closest_index = -1;
				float minimum_distance = INFINITY;

				for (unsigned int j = 0; j < scene.objects.size(); j++)
				{
					float distance = scene.objects[j]->Intersect(cam_ray);
					if (distance< minimum_distance && distance > accuracy)
					{
						minimum_distance = distance;
						closest_index = j;
					}
				}

				if (closest_index >= 0)
				{
					glm::vec3 intersection_position = Cam_ray_origin + (Cam_ray_direction*minimum_distance);
					glm::vec3 intersection_color = getColorAt(intersection_position, Cam_ray_direction, scene.objects, scene.lights, closest_index, 0);
					samples.push_back(intersection_color);
				}
				else // No intersection, use background colour
				{
					samples.push_back(glm::vec3(0, 0, 0));
				}
			}

			glm::vec3 sum(0, 0, 0);
			for (unsigned int i = 0; i < samples.size(); i++)
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

// Read an input file and render the resulting scene to a .bmp file of the same name
void CreateRender(std::string FileName)
{
	InputReader* input = new InputReader(FileName + ".txt");

	Scene scene = input->scene;

	int width = scene.width;
	int height = scene.height;
	int numPixels = width * height;
	glm::vec3* pixels = new glm::vec3[numPixels];
	//glm::vec3* pixels = new glm::vec3[numPixels];

	float aspect_ratio = scene.camera->getAspectRatio();
	glm::vec3 Cam_ray_origin = scene.camera->getPosition();
	float fov = glm::radians(scene.camera->getFoV());


	const clock_t begin_time = clock();
	std::vector<std::thread> threads;

	for (int i = 0; i < thread_count; i++)
	{
		threads.push_back(std::thread(computePixels, i*(width / thread_count), (i + 1)*(width / thread_count), 0, height, scene, pixels));
	}

	std::cout << "Rendering " << FileName << ".txt ..." << std::endl;
	for (auto& th : threads) th.join();

	std::cout << "Reached end of raycast loop after " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds" << std::endl;
	writeImage(pixels, width, height, FileName);

	delete[] pixels;
	delete input;
}

int main()
{
	srand(static_cast <unsigned>(time(0)));
	for (int i = 1; i <= 4; i++)
	{
		CreateRender("scene" + std::to_string(i));
	}
	return 0;

}
