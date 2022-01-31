#ifndef ATORIO_WINGL_STYLE
#define ATORIO_WINGL_STYLE

#include "../math/Matrix.hpp"
#include "Texture.hpp"
#include <string>

class Box {
public:
	int x, y, w, h;
};

enum Stylename {
	SN_DISPLAY,
	SN_RELATIVE,
	SN_POSITION_LEFT,
	SN_POSITION_RIGHT,
	SN_POSITION_TOP,
	SN_POSITION_BOTTOM,
	SN_WIDTH,
	SN_MAX_WIDTH,
	SN_HEIGHT,
	SN_MAX_HEIGHT,
	SN_ASPECT_RATIO,
	SN_PADDING,
	SN_PADDING_LEFT,
	SN_PADDING_RIGHT,
	SN_PADDING_TOP,
	SN_PADDING_BOTTOM,
	SN_BORDER_RADIUS,
	SN_BORDER_RADIUS_UPPERLEFT,
	SN_BORDER_RADIUS_UPPERRIGHT,
	SN_BORDER_RADIUS_LOWERLEFT,
	SN_BORDER_RADIUS_LOWERRIGHT,
	SN_BACKGROUND_IMAGE,
	SN_BACKGROUND_COLOR,
	SN_FONT_TEXT,
	SN_FONT_COLOR,
	SN_FONT_FAMILY,
	SN_FONT_SIZE,
	SN_FONT_DECORATIONS,
	SN_SCROLL_HORIZONTAL,
	SN_SCROLL_VERTICAL,
};

class Style {
public:
	Style();

	void set(enum Stylename property, std::string value);


	virtual ~Style() { if (background.image && !background.reuse) delete background.image; }

	bool bound(Box& window, Box& parent);
	void calculateDimensions(const Box& W, const Box& p, Box* B) const;
	vec2 calculateBorders(const Box& window, Box* b, int n) const;

	void (*onkeypress)(int, bool) = NULL;
	void (*onkeytype)(int) = NULL;

	void (*onmousepress)(int, bool) = NULL;
	void (*onmouseclick)(int) = NULL;

	void (*onhover)(bool) = NULL;
	void (*onfocus)(bool) = NULL;


	friend class StyleUniform;
	friend class Component;
protected:
	struct {
		float left, top, right, bottom; // Coordinates
		bool pleft, ptop, pright, pbottom; //Are these pixels or percentages
		bool uleft, utop, uright, ubottom; //Are these dimensions used
	} position, padding;
	struct {
		float width, height;
		bool pwidth, pheight;
		bool uwidth, uheight;
		float ratio;
	} dimension;
	int z_order; // 0 to 65535
	struct {
		Texture* image;
		bool reuse;
		vec4 color;
	} background;
	struct {
		float r;
		bool pr;
	} border[4];
	
	bool hscroll = true, vscroll = true;
	bool display = true, relative = true;
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
	vec2 border_radius[4];
	vec2 center, upperright;

	void compute(Box *b, const Box& window, const Box& parent, const Style& style);
private:
};

#endif