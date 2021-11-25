#ifndef ATORIO_WINGL_STYLE
#define ATORIO_WINGL_STYLE

#include "../math/Matrix.hpp"
#include "Texture.hpp"
#include <string>

class Box {
public:
	int x, y, w, h;
};

class Style {
public:
	Style();
	virtual ~Style() { if (background.image && !background.reuse) delete background.image; }
	bool display = true; //if false, do not draw; skip this whole object
	bool relative = true; //true for relative, false for absolute
	struct {
		float left, top, right, bottom; // Coordinates
		bool pleft, ptop, pright, pbottom; //Are these pixels or percentages
		bool uleft, utop, uright, ubottom; //Are these dimensions used
	} position;
	struct {
		float width, height;
		bool pwidth, pheight;
	} dimension;
	int z_order; // 0 to 65535
	struct {
		Texture* image;
		bool reuse;
		vec4 color;
	} background;
	struct {
		float xr, yr;
		bool px, py;
	} border;
	//TODO: Iron out scrolling :)

	bool bound(Box& window, Box& parent);

	void (*onkeypress)(int, bool) = NULL;
	void (*onkeytype)(int) = NULL;

	void (*onmousepress)(int, bool) = NULL;
	void (*onmouseclick)(int) = NULL;

	void (*onhover)(bool) = NULL;
	void (*onfocus)(bool) = NULL;
};

class StyleUniform {
public:
	StyleUniform() {}
	virtual ~StyleUniform() {}
	vec2 p2Gm, p2Gb; // pixel to OpenGL slope and base
	vec2 posm, posb; // position cropping slope and base
	vec2 texm, texb; // texture cropping slope and base
	float sampling;
	vec4 background;
	float z_order;
	vec2 border_radius;
	vec2 center, upperright;

	void compute(Box *b, const Box& window, const Box& parent, const Style& style);
};

#endif