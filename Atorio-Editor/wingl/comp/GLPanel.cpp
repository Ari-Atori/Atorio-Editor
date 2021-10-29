#include "GLPanel.hpp"
#include "../../math/Matrix.hpp"

static mat4 orthopos(int W, int H, int x, int y, int w, int h) {
	mat4 m = MAT4_IDENTITY;
	m(0, 0) = (float)w / W;
	m(1, 1) = (float)h / H;
	m(3, 0) = 2.0F * (0.5F * w + x) / W - 1.0F;
	m(3, 1) = -(2.0F * (0.5F * h + y) / H - 1.0F);
	return m;
}

GLPanel::GLPanel(int W, int H, int w, int h, std::string filename, uint32_t color) : Component(0, 0, 1, 1, w, h) {
	shader = new Shader(filename, std::vector<std::string> { "position", "texture" });
	shader->bindUniform("screen", UNIFORM_MAT4F, 1);
	texture = new Texture(color);
	openglrect = new GLRectangle();
	screen = orthopos(W, H, x, y, w, h);
}

GLPanel::GLPanel(int W, int H, int x, int y, int w, int h, std::string filename, uint32_t color) : Component(x, y, 0, 0, w, h) {
	shader = new Shader(filename, std::vector<std::string> { "position", "texture" });
	shader->bindUniform("screen", UNIFORM_MAT4F, 1);
	texture = new Texture(color);
	openglrect = new GLRectangle();
	screen = orthopos(W, H, x, y, w, h);
}

GLPanel::~GLPanel() {
	delete[] pixels;
	for (Component* c : comps)
		delete c;
	delete shader;
	delete texture;
	delete openglrect;
}

bool GLPanel::draw(uint32_t* window, int width, int height) {
	shader->bind();
	SDL_Log("Getting here, you fucking noob! %llu\n", comps.size());
	for (int i = 0; i < (rect.w * rect.h); ++i)
		pixels[i] = 0xFF808080;
	for (Component* c : comps)
		c->draw(pixels, rect.w, rect.h);
	texture->update(rect.w, rect.h, pixels);
	texture->Bind();
	openglrect->bind();
	shader->setUniform("screen", &screen);
	openglrect->draw();
	return false;
}