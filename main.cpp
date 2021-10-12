#include <iostream>
#include <image.hpp>

typedef png::rgb_pixel px;
typedef png::basic_rgb_pixel<int> pxi;

// convolves a 3x3 filter with a location in the image array at location y, x
// repeat for all three channels
pxi convolve(const int f[9],
	     px a11, px a12, px a13,
	     px a21, px a22, px a23,
	     px a31, px a32, px a33) {

	return {f[0]*a11.red + f[1]*a12.red + f[2]*a13.red
		+ f[3]*a21.red + f[4]*a22.red + f[5]*a23.red
		+ f[6]*a31.red + f[7]*a32.red + f[6]*a33.red,
		f[0]*a11.green + f[1]*a12.green + f[2]*a13.green
		+ f[3]*a21.green + f[4]*a22.green + f[5]*a23.green
		+ f[6]*a31.green + f[7]*a32.green + f[6]*a33.green,
		f[0]*a11.blue + f[1]*a12.blue + f[2]*a13.blue
		+ f[3]*a21.blue + f[4]*a22.blue + f[5]*a23.blue
		+ f[6]*a31.blue + f[7]*a32.blue + f[6]*a33.blue};
}

pxi abs(pxi pixel) {
	return {abs(pixel.red), abs(pixel.green), abs(pixel.blue)};
}

pxi max(pxi pixel1, pxi pixel2) {
	return {
		std::max(pixel1.red, pixel2.red),
		std::max(pixel1.green, pixel2.green),
		std::max(pixel1.blue, pixel2.blue)
	};
}

px pxi2px(pxi pixel) {
	return {
		static_cast<unsigned char>(pixel.red),
		static_cast<unsigned char>(pixel.green),
		static_cast<unsigned char>(pixel.blue)
	};
}

int main() {
	// assuming cwd is "../target/*"
	std::string base_path = "../res/";

	png::image<px> image(base_path + "fruit.png");
	png::uint_32 x, y;
	int z;

	int sobel_filters[][9] = {
		{-1, -2, -1, 0, 0, 0, 1, 2, 1},
		{-1, 0, 1, -2, 0, 2, -1, 0, 1},
		{2, 1, 0, 1, 0, -1, 0, -1, -2},
		{0, 1, 2, -1, 0, 1, -2, -1, 0},
	};

	// for now, ignore the fringe for simplicity
	for (y = 1; y < image.get_height()-1; ++y) {
		for (x = 1; x < image.get_height()-1; ++x) {

			pxi max_gradient{0, 0, 0};

			for (z = 0; z < 4; ++z) {
				pxi gradient = convolve(sobel_filters[0],
					 image[y-1][x-1], image[y-1][x], image[y-1][x+1],
					 image[y][x-1], image[y][x], image[y][x+1],
					 image[y+1][x-1], image[y+1][x], image[y+1][x+1]);

				max_gradient = max(max_gradient, abs(gradient));
			}

			image[y][x] = pxi2px(max_gradient);
		}
	}

	image.write(base_path + "output.png");
}