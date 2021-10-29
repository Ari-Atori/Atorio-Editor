#ifndef ATORIO_COMP_GLPANEL
#define ATORIO_COMP_GLPANEL

#include <SDL2/SDL.h>
#include <vector>
#include "Component.hpp"
#include "../GLRectangle.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../../math/Matrix.hpp"

class GLPanel : public Component {
public:
	GLPanel(int W, int H, int x, int y, int w, int h, std::string filename, uint32_t color);
	GLPanel(int W, int H, int w, int h, std::string filename, uint32_t color);
	virtual ~GLPanel();

	bool draw(uint32_t* window, int width, int height);
private:
	GLRectangle *openglrect;
	Shader* shader;
	Texture* texture;
	mat4 screen, texuni;
	void (*first_draw)(int width, int height, uint32_t *pixels) = NULL;
};

#endif
