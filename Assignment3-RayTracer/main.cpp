#include "Scene.h"
#include "InputReader.h"
#pragma warning(disable:4996)
#include "Sphere.h"
#include <cimg/CImg.h>
#include "Plane.h"


float ambient_light = 0.6;

void writeImage(int width, int height, glm::vec3* pixels)
{
	cimg_library::CImg<float> image(width, height, 1, 3, 0);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			float red = pixels[index].x * 255;
			float blue = pixels[index].y * 255;
			float green = pixels[index].z * 255;
			image(x, height - y - 1, 0, 0) = red;
			image(x, height - y - 1, 0, 1) = blue;
			image(x, height - y - 1, 0, 2) = green;
		}
	}
	image.save("render.bmp");
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
	{
		main_disp.wait();
	}
}

//void saveBMP(const char * fileName, int w, int h, int dpi, glm::vec3 *data)
//{
//	std::cout << "Writing to bmp..." << std::endl;
//	FILE *f;
//	int k = w*h;
//	int s = 4 * k;
//	int filesize = 54 + s;
//
//
//	double factor = 39.375;
//	int m = static_cast<int>(factor);
//
//	int ppm = dpi*m;
//	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0 };
//	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
//
//	bmpfileheader[2] = (unsigned char)(filesize);
//	bmpfileheader[3] = (unsigned char)(filesize >> 8);
//	bmpfileheader[4] = (unsigned char)(filesize >> 16);
//	bmpfileheader[5] = (unsigned char)(filesize >> 24);
//
//	bmpinfoheader[4] = (unsigned char)(w);
//	bmpinfoheader[5] = (unsigned char)(w >> 8);
//	bmpinfoheader[6] = (unsigned char)(w >> 16);
//	bmpinfoheader[7] = (unsigned char)(w >> 24);
//
//	bmpinfoheader[8] = (unsigned char)(h);
//	bmpinfoheader[9] = (unsigned char)(h >> 8);
//	bmpinfoheader[10] = (unsigned char)(h >> 16);
//	bmpinfoheader[11] = (unsigned char)(h >> 24);
//
//	bmpinfoheader[21] = (unsigned char)(s);
//	bmpinfoheader[22] = (unsigned char)(s >> 8);
//	bmpinfoheader[23] = (unsigned char)(s >> 16);
//	bmpinfoheader[24] = (unsigned char)(s >> 24);
//
//	bmpinfoheader[25] = (unsigned char)(ppm);
//	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
//	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
//	bmpinfoheader[28] = (unsigned char)(ppm >> 24);
//
//
//	bmpinfoheader[29] = (unsigned char)(ppm);
//	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
//	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
//	bmpinfoheader[32] = (unsigned char)(ppm >> 24);
//
//	f = fopen(fileName, "wb");
//	fwrite(bmpfileheader, 1, 14, f);
//	fwrite(bmpinfoheader, 1, 40, f);
//
//	for (int i = 0; i < k; i++)
//	{
//		double red = data[i].x * 255;
//		double green = data[i].y * 255;
//		double blue = data[i].z * 255;
//		unsigned char color[3] = { (int)floor(blue),(int)floor(green),(int)floor(red) };
//		fwrite(color, 1, 3, f);
//	}
//	fclose(f);
//	std::cout << "Writing complete." << std::endl;
//}

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
		if (intersections[0] > 0) // Make sure the distance is greater than 0
		{
			return 0;
		}
		else
		{
			return -1; // The only intersection distance is negative
		}
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

glm::vec3 getColorAt(const glm::vec3& intersection_position, const glm::vec3& intersection_direction, const std::vector<SceneObject*>& objects, const std::vector<Light*>& lights, int index, double accuracy)
{
	// Shadow Ray


	// Reflection Ray
	

	// Shadow Ray


	// Refraction Ray


	glm::vec3 object_color = objects.at(index)->getAmbient();
	glm::vec3 object_normal = objects.at(index)->getNormalAt(intersection_position);

	glm::vec3 final_color = object_color * ambient_light;
	for (int light_index = 0; light_index < lights.size(); light_index++)
	{
		glm::vec3 light_direction = normalize(lights.at(light_index)->getPosition() - intersection_position);
		float cosine_angle = dot(object_normal, light_direction);
		if (cosine_angle > 0)
		{
			// Check for shadows
			bool shadowed = false;
			glm::vec3 distance_to_light = normalize(lights.at(light_index)->getPosition() - intersection_position);
			float distance_to_light_magnitude = length(distance_to_light);
			Ray shadow_ray(intersection_position, normalize(lights.at(light_index)->getPosition() - intersection_position));
			std::vector<float> secondary_intersections;
			for (int object_index = 0; object_index < objects.size(); object_index++)
			{
				secondary_intersections.push_back(objects.at(object_index)->Intersect(shadow_ray));
			}

			for (int c = 0; c < secondary_intersections.size(); c++)
			{
				if (secondary_intersections.at(c) > accuracy)
				{
					if (secondary_intersections.at(c) <= distance_to_light_magnitude)
					{
						shadowed = true;
						break;
					}

				}
			}
			if (!shadowed) {
				final_color += object_color * lights.at(light_index)->getColor()*cosine_angle;
			}
		}
		return final_color;
	}
}

	int main()
	{
		int dpi = 72;
		double accuracy = 0.00001;

		glm::vec3 X = glm::vec3(1, 0, 0);
		glm::vec3 Y = glm::vec3(0, 1, 0);
		glm::vec3 Z = glm::vec3(0, 0, 1);

		glm::vec3 cam_dir = glm::vec3(0, 0, -1);
		glm::vec3 cam_down = glm::vec3(0, -1, 0);
		glm::vec3 cam_right = glm::vec3(1, 0, 0);

		//Sphere scene_sphere(glm::vec3(0, 10, -30), glm::vec3(0.1, 0.5, 0.5), glm::vec3(0.4, 0.6, 0.2), glm::vec3(0.2, 0.5, 0.5), 3, 1.0);
		//Plane scene_plane(Y, glm::vec3(), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.8, 0.8, 0.2), glm::vec3(0.5, 0.5, 0.5),1.0);
		//Camera scene_camera()

		InputReader* input = new InputReader("scene7.txt");
		Scene scene = input->scene;

		int width = scene.width;
		int height = scene.height;
		int numPixels = width * height;
		glm::vec3* pixels = new glm::vec3[numPixels];

		float aspect_ratio = scene.camera->getAspectRatio();
		glm::vec3 Cam_ray_origin = scene.camera->getPosition();


		float xamt, yamt;
		glm::vec3 pHit;
		glm::vec3 nHit;
		glm::vec3 dHit;
		int index = 0;

		for (int x = 0; x < width; x++)
		{
			std::cout << "Tracing pixels for x=" << x << "... " << std::endl;
			for (int y = 0; y < height; y++)
			{
				//No anti-aliasing
				if (width > height)
				{
					xamt = ((x + 0.5) / width)*aspect_ratio - (((width - height) / (float)height) / 2);
					yamt = ((height - y) + 0.5) / height;
				}
				else if (height > width)
				{
					xamt = (x + 0.5) / width;
					yamt = (((height - y) + 0.5) / height) / aspect_ratio - (((height - width) / (float)width) / 2);
				}
				else
				{
					// The image is square
					xamt = (x + 0.5) / width;
					yamt = ((height - y) + 0.5) / height;
				}
				glm::vec3 Cam_ray_direction = glm::normalize(cam_dir + (cam_right*(float)(xamt - 0.5) + (cam_down*(float)(yamt - 0.5))));
				Ray cam_ray(Cam_ray_origin, Cam_ray_direction);

				std::vector<float> intersections;

				for (int i = 0; i < scene.objects.size(); i++)
				{
					intersections.push_back(scene.objects[i]->Intersect(cam_ray));
				}
				int index_closest = closest(intersections);



				index = y*width + x;



				if (index_closest >= 0)
				{
					// Determine the position / direction vectors at intersection point
					if (intersections.at(index_closest) > accuracy)
					{
						glm::vec3 intersection_position = Cam_ray_origin + (Cam_ray_direction*intersections.at(index_closest));
						glm::vec3 intersection_direction = Cam_ray_direction;
						glm::vec3 intersection_color = getColorAt(intersection_position, intersection_direction, scene.objects, scene.lights, index_closest, accuracy);

						pixels[index].x = intersection_color.x;
						pixels[index].y = intersection_color.y;
						pixels[index].z = intersection_color.z;
					}
				}
				else
				{
					pixels[index].x = 0;
					pixels[index].y = 0;
					pixels[index].z = 0;
				}
				/*index = y*width + x;
				if ((x>200 && x< 440) && (y>200 && y<280))
				{
					pixels[index].x = 0.5;
					pixels[index].y = 0.1;
					pixels[index].z = 1.0;
				}
				else
				{
					pixels[index].x = 0.1;
					pixels[index].y = 0.1;
					pixels[index].z = 0.2;
				}*/
			}

		}
		std::cout << "Reached end of raycast loop" << std::endl;
		writeImage(width, height, pixels);
		//saveBMP("scene.bmp", width, height, dpi, pixels);

		/*InputReader* input = new InputReader("scene5.txt");
		Scene scene = input->scene;*/
		//std::cout << scene.to_string() << std::endl;
		return 0;
	}