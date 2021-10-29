#include "Component.hpp"
#include <stb/stb_image.h>

Button::Button(int x, int y, int rx, int ry, int w, int h, std::string filename) : Component(x, y, rx, ry, w, h) {
	int width, height, numComponents;
	unsigned char* data = stbi_load((filename).c_str(), &width, &height, &numComponents, 4);

	//TODO: worry about scaling later
	memcpy(pixels, data, 4 * w * h);
	stbi_image_free(data);
}

Button::~Button() {
	delete[] pixels;
	for (Component* c : comps)
		delete c;
}