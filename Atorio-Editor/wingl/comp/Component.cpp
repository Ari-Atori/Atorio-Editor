#include "Component.hpp"

#define COMP_POS_START	0
#define COMP_POS_CENTER 1
#define COMP_POS_END	2

Component::Component(int x, int y, int rx, int ry, int w, int h) {
	rect = { x, y, w, h };
	pixels = new uint32_t[w * h];
	changed = false;
}

Component::~Component() {
	if (pixels) delete[] pixels;
	for (Component* c : comps)
		delete c;
}

void Component::copy(uint32_t* src, uint32_t* dest, int W, int H, SDL_Rect r) {
	int x0 = r.x < 0 ? 0 : r.x, y0 = r.y < 0 ? 0 : r.y;
	int x1 = (r.x + r.w) > W ? W : (r.x + r.w), y1 = (r.y + r.h) > H ? H : (r.y + r.h);
	int width = x1 - x0, height = y1 - y0;

	SDL_Log("(%d %d) - (%d %d) = (%d %d)\n", x1, y1, x0, y0, width, height);

	if (width < 0)
		return;
	for (int y = 0; y < height; y++)
		memcpy(&dest[(y + y0) * W + x0], &src[y * r.w + (x0 - r.x)], sizeof(uint32_t) * width);
}

bool Component::draw(uint32_t* window, int w, int h) {
	for (Component *c : comps)
		c->draw(pixels, rect.w, rect.h);
	if (window)
		copy(pixels, window, w, h, rect);
	return false;
}