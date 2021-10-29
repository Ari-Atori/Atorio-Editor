#ifndef ATORIO_WINGL_COMP_COMPONENT
#define ATORIO_WINGL_COMP_COMPONENT

#include <SDL2/SDL.h>
#include <vector>

class Component {
public:
	Component() { pixels = NULL; relx = rely = 0; rect = { 0, 0, 0, 0 }; changed = false; }
	Component(int x, int y, int rx, int ry, int w, int h);
	virtual ~Component();

	void addComponent(Component* comp) { comps.push_back(comp); }
	virtual bool draw(uint32_t* window, int width, int height);
	static void copy(uint32_t* src, uint32_t* dest, int W, int H, SDL_Rect r);
protected:
	SDL_Rect rect;
	uint32_t *pixels;
	bool changed;
	std::vector<Component*> comps;
	int relx, rely;
};

#include "GLPanel.hpp"
#include "Button.hpp"

#endif
