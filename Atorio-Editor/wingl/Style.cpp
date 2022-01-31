#include "Style.hpp"
#include <iostream>
#include <map>

static vec4 srgb2lrgb(vec4 c) {
	c.x = (c.x <= 0.04045F) ? c.x * 0.0773993808F : (float)pow((c.x + 0.055) * 0.94786729857, 2.4);
	c.y = (c.y <= 0.04045F) ? c.y * 0.0773993808F : (float)pow((c.y + 0.055) * 0.94786729857, 2.4);
	c.z = (c.z <= 0.04045F) ? c.z * 0.0773993808F : (float)pow((c.z + 0.055) * 0.94786729857, 2.4);
	return c;
}


void Style::calculateDimensions(const Box& window, const Box& parent, Box *B) const {
	const Box* P = (relative) ? &parent : &window; //select the respected parent; the other is ignored, as this code rejects piety
	
	//convert to pixels, even if these are zero or undefined
	float left = P->x + ((position.pleft) ? (int)(P->w * position.left) : (int)position.left);
	float right = P->x + P->w - ((position.pright) ? (int)(P->w * position.right) : (int)position.right);
	float top = P->y + ((position.ptop) ? (int)(P->h * position.top) : (int)position.top);
	float bottom = P->y + P->h - ((position.pbottom) ? (int)(P->h * position.bottom) : (int)position.bottom);
	float width = (dimension.pwidth) ? (int)(P->w * dimension.width) : (int)dimension.width;
	float height = (dimension.pheight) ? (int)(P->h * dimension.height) : (int)dimension.height;
	float ratio = dimension.ratio;
	
	if (position.uleft) {
		B->x = (int) left;
		if (position.uright) // Calculate width for the left and right coordinates
			B->w = (int)(right - left);
		else if (dimension.uwidth) // width is explicitly defined
			B->w = (int)width;
		else {
			float _h = (position.utop) ? ((position.ubottom) ? bottom - top : height) : height;
			B->w = (int)(_h * ratio); // width is defined by height and aspect ratio
		}
	} else {
		float _h = (position.utop) ? ((position.ubottom) ? bottom - top : height) : height;
		B->w = (dimension.uwidth) ? (int)width : (int)(_h * ratio); //height and ratio must be defined
		B->x = (position.uright) ? (int)(right - B->w) : ((P->w - B->w) >> 1) + P->x;
	}

	if (position.utop) {
		B->y = (int)top;
		if (position.ubottom)
			B->h = (int)(bottom - top);
		else if (dimension.height)
			B->h = height;
		else {
			float _w = (position.uleft) ? ((position.uright) ? right - left : width) : width;
			B->h = (int)(_w / ratio); // width is defined by height and aspect ratio
		}
	} else {
		float _w = (position.uleft) ? ((position.uright) ? right - left : width) : width;
		B->h = (dimension.uheight) ? (int)height : (int)(_w / ratio);
		B->y = (position.ubottom) ? (int) (bottom - B->h) : ((P->h - B->h) >> 1) + P->y;
	}

	std::cout << "BOX DIMENSIONS: (" << B->x << "," << B->y << ") " << B->w << "x" << B->h << "\n";
}

//Get border radius
vec2 Style::calculateBorders(const Box& window, Box* B, int n) const {
	vec2 p2Gm = { 2.0F / window.w, 2.0F / window.h }; //converts pixels into opengl units

	float xr = (border[n].pr) ? border[n].r * B->w : border[n].r;
	float yr = (border[n].pr) ? border[n].r * B->h : border[n].r;
	vec2 br = { xr, yr };
	return br * p2Gm;
}

Style::Style() {
	display = true;
	relative = true;
	position = { 0, 0, 0, 0, false, false, false, false, false, false, false, false };
	dimension = { 0, 0, false, false, false, false, 1.0 };
	z_order = 0;
	background = { NULL, false, {0, 0, 0, 0} };
	for (int i = 0; i < 4; ++i)
		border[i] = { 0, false };
}

static void decipher(std::string value, float *fvalue, bool *pvalue) {
	char pasta[256];
	strcpy_s(pasta, 256, value.c_str());
	size_t len = value.size();

	if (pasta[len - 1] == '%') {
		pasta[len - 1] = '\0';
		*fvalue = atof(pasta) * 0.01;
		*pvalue = true;
		std::cout << "DEBUG:: FVALUE " << *fvalue << " | PVALUE " << *pvalue << std::endl;
	}
	else if (!strncmp(&pasta[len - 2], "px", 2)) {
		pasta[len - 2] = '\0';
		*fvalue = atof(pasta);
		*pvalue = false;
		std::cout << "DEBUG:: FVALUE " << *fvalue << " | PVALUE " << *pvalue << std::endl;
	}

}

static std::map<std::string, vec4> colors = {
	{"empty", {0,0,0,0}},
	{"black", {0,0,0,1}},
	{"white", {1,1,0,1}},
	{"red", {1,0,0,1}},
	{"yellow", {1,1,0,1}},
	{"green",{0,1,0,1}},
	{"cyan",{0,1,1,0}},
	{"blue",{0,0,1,0}},
	{"magenta",{1,1,1,1}}
};

static float channel(const char *cvalue, int n) {
	int tn = (n << 1) | 1, to = tn + 1;
	float ret = 0;
	if (cvalue[tn] >= '0' && cvalue[tn] <= '9')
		ret += (cvalue[tn] - '0') * 16;
	else if (cvalue[tn] >= 'A' && cvalue[tn] <= 'F')
		ret += (cvalue[tn] - 'A' + 10) * 16;
	if (cvalue[to] >= '0' && cvalue[to] <= '9')
		ret += (cvalue[to] - '0');
	else if (cvalue[to] >= 'A' && cvalue[to] <= 'F')
		ret += (cvalue[to] - 'A' + 10);
	return ret * 0.00392156862F;
}

static vec4 decipher_color(std::string value) {
	const char* cvalue = value.c_str();
	if (cvalue[0] == '#')
		return { channel(cvalue, 0), channel(cvalue, 1), channel(cvalue, 2), channel(cvalue, 3) };
	else
		return colors[value];
}

void Style::set(enum Stylename property, std::string value) {
	std::cout << "PROPERTY REQUEST: " << property << " with value " << value << std::endl;
	switch (property) {
	case SN_DISPLAY:
		display = (value == "true");
		break;
	case SN_RELATIVE:
		relative = (value == "true");
		break;
	case SN_POSITION_LEFT:
		decipher(value, &position.left, &position.pleft);
		position.uleft = true;
		break;
	case SN_POSITION_RIGHT:
		decipher(value, &position.right, &position.pright);
		position.uright = true;
		break;
	case SN_POSITION_TOP:
		decipher(value, &position.top, &position.ptop);
		position.utop = true;
		break;
	case SN_POSITION_BOTTOM:
		decipher(value, &position.bottom, &position.pbottom);
		position.ubottom = true;
		break;
	case SN_WIDTH:
		decipher(value, &dimension.width, &dimension.pwidth);
		dimension.uwidth = true;
		break;
	case SN_HEIGHT:
		decipher(value, &dimension.height, &dimension.pheight);
		dimension.uheight = true;
		break;
	case SN_ASPECT_RATIO:
		dimension.ratio = atof(value.c_str());
		break;
	case SN_PADDING:
	case SN_PADDING_LEFT:
	case SN_PADDING_RIGHT:
	case SN_PADDING_TOP:
	case SN_PADDING_BOTTOM:
		break;
	case SN_BORDER_RADIUS:
		decipher(value, &border[0].r, &border[0].pr);
		for (int i = 1; i < 4; ++i)
			border[i].r = border[0].r, border[i].pr = border[0].pr;
		break;
	case SN_BORDER_RADIUS_UPPERLEFT:
		decipher(value, &border[2].r, &border[2].pr);
		break;
	case SN_BORDER_RADIUS_UPPERRIGHT:
		decipher(value, &border[3].r, &border[3].pr);
		break;
	case SN_BORDER_RADIUS_LOWERLEFT:
		decipher(value, &border[0].r, &border[0].pr);
		break;
	case SN_BORDER_RADIUS_LOWERRIGHT:
		decipher(value, &border[1].r, &border[1].pr);
		break;
	case SN_BACKGROUND_IMAGE:
		background.image = new Texture(value);
		break;
	case SN_BACKGROUND_COLOR:
		background.color = decipher_color(value);
		break;
	case SN_FONT_TEXT:
	case SN_FONT_COLOR:
	case SN_FONT_FAMILY:
	case SN_FONT_SIZE:
	case SN_FONT_DECORATIONS:
	case SN_SCROLL_HORIZONTAL:
	case SN_SCROLL_VERTICAL:
		break;
	default:
		break;
	}
}

//TODO: calculate boundaries for scrolling and to prevent overflowing
bool Style::bound(Box& window, Box& parent) {
	Box box;
	calculateDimensions(window, parent, &box);
	return true;
}

void StyleUniform::compute(Box *box, const Box& window, const Box& parent, const Style& s) {
	s.calculateDimensions(window, parent, box);

	p2Gm = { (float)box->w / window.w, (float)box->h / window.h };
	p2Gb = { 2.0F * (0.5F * box->w + box->x) / window.w - 1.0F, -(2.0F * (0.5F * box->h + box->y) / window.h - 1.0F) };

	background = srgb2lrgb(s.background.color);
	for (int i = 0; i < 4; ++i)
		border_radius[i] = s.calculateBorders(window, box, i);
	center = { (float)(2 * box->x + box->w) / window.w - 1.0F, (float)(2 * box->y + box->h) / -window.h + 1.0F };
	upperright = { 2.0F * (box->x + box->w) / window.w - 1.0F, 2.0F * (box->y) / -window.h + 1.0F };
	sampling = !!s.background.image;
}