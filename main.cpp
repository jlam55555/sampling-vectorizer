#include <iostream>
#include <image.hpp>

int main() {
	// assuming cwd is "../target/*"
	std::string base_path = "../res/";

	png::image<png::rgb_pixel> image(base_path + "test.png");
	image.write(base_path + "output.png");
}