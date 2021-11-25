#include "Style.hpp"
#include <iostream>

static vec4 srgb2lrgb(vec4 c) {
	c.x = (c.x <= 0.04045F) ? c.x * 0.0773993808F : (float)pow((c.x + 0.055) * 0.94786729857, 2.4);
	c.y = (c.y <= 0.04045F) ? c.y * 0.0773993808F : (float)pow((c.y + 0.055) * 0.94786729857, 2.4);
	c.z = (c.z <= 0.04045F) ? c.z * 0.0773993808F : (float)pow((c.z + 0.055) * 0.94786729857, 2.4);
	return c;
}


static void get_dimensions(const Box& W, const Box& p, const Style& s, int* x, int* y, int* w, int* h) {
	const Box* P = (s.relative) ? &p : &W; //respected parent, the other is ignored, as this code rejects piety
	
	//If the left coordinate is defined
	if (s.position.uleft) {
		*x = P->x + ((s.position.pleft) ? (int)(P->w * s.position.left) : (int)s.position.left);
		// If the right coordinate is defined, we can calculate the width
		if (s.position.uright)
			*w = P->x + P->w - ((s.position.pright) ? (int)(P->w * s.position.right) : (int)s.position.right) - *x;
		else //Otherwise the width must be defined
			*w = (s.dimension.pwidth) ? (int)(P->w * s.dimension.width) : (int)s.dimension.width;
	} else {
		//If the left isn't defined, the right and width attributes must be defined
		*w = (s.dimension.pwidth) ? (int)(P->w * s.dimension.width) : (int)s.dimension.width;
		if (s.position.uright)
			*x = P->x + P->w - ((s.position.pright) ? (int)(P->w * s.position.right) : (int)s.position.right) - *w;
		else
			*x = ((P->w - *w) >> 1) + P->x;
	}

	//If the top coordinate is defined
	if (s.position.utop) {
		*y = P->y + ((s.position.ptop) ? (int)(P->h * s.position.top) : (int)s.position.top);
		// If the bottom coordinate is defined, we can calculate the height
		if (s.position.ubottom)
			*h = P->y + P->h - ((s.position.pbottom) ? (int)(P->h * s.position.bottom) : (int)s.position.bottom) - *y;
		else //Otherwise the height must be defined
			*h = (s.dimension.pheight) ? (int)(P->h * s.dimension.height) : (int)s.dimension.height;
	}
	else {
		//If the top isn't defined, the bottom and height attributes must be defined
		*h = (s.dimension.pheight) ? (int)(P->h * s.dimension.height) : (int)s.dimension.height;
		if (s.position.ubottom)
			*y = P->y + P->h - ((s.position.pbottom) ? (int)(P->h * s.position.bottom) : (int)s.position.bottom) - *h;
		else
			*y = ((P->h - *h) >> 1) + P->y;
	}

	std::cout << "PARENT DIM BOIS: (" << P->x << "," << P->y << ") (" << P->w << "x" << P->h << ")" << std::endl;
	std::cout << "DIMENSIONS BOIS: (" << *x << "," << *y << ") (" << *w << "x" << *h << ")\n" << std::endl;
}

//Get border radius
static vec2 border_r(const Style& s, const Box& window, Box *b) {
	vec2 p2Gm = { 2.0F / window.w, 2.0F / window.h };
	vec2 B = { (s.border.px) ? (int)(b->w * s.border.xr) : (int)s.border.xr, (s.border.py) ? (int)(b->h * s.border.yr) : (int)s.border.yr };
	return B * p2Gm;
}

Style::Style() {
	display = true;
	relative = true;
	position = { 0, 0, 0, 0, false, false, false, false, true, true, false, false };
	dimension = { 0, 0, false, false };
	z_order = 0;
	background = { NULL, false, {0, 0, 0, 1} };
	border = { 0, 0, false, false };
}

bool Style::bound(Box& window, Box& parent) {
	Box box;
	get_dimensions(window, parent, *this, &box.x, &box.y, &box.w, &box.h);
	return true;
}

void StyleUniform::compute(Box *box, const Box& window, const Box& parent, const Style& s) {
	get_dimensions(window, parent, s, &box->x, &box->y, &box->w, &box->h);
	p2Gm = { (float)box->w / window.w, (float)box->h / window.h };
	p2Gb = { 2.0F * (0.5F * box->w + box->x) / window.w - 1.0F, -(2.0F * (0.5F * box->h + box->y) / window.h - 1.0F) };
	background = srgb2lrgb(s.background.color);
	border_radius = border_r(s, window, box);
	center = { (float)(2 * box->x + box->w) / window.w - 1.0F, (float)(2 * box->y + box->h) / -window.h + 1.0F };
	upperright = { 2.0F * (box->x + box->w) / window.w - 1.0F, 2.0F * (box->y) / -window.h + 1.0F };
	sampling = !!s.background.image;
}