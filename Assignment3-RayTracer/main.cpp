#include "Scene.h"
#include "InputReader.h"

int main()
{
	InputReader* input = new InputReader("scene7.txt");
	Scene scene = input->scene;
	std::cout << scene.to_string() << std::endl;
	return 0;
}