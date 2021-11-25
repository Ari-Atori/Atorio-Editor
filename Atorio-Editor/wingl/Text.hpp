#ifndef ATORIO_WINGL_TEXT
#define ATORIO_WINGL_TEXT

#include <string>
#include <GL/glew.h>
#include "Style.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H 

class Text {
public:
	Text(bool local, std::string filename, int size, std::string text);
	virtual ~Text();

	float getFontSize() { return fontsize; }
	void setFontSize(int fs);
	std::string getText() { return text; }
	void setText(std::string t);

	void bind();

	static FT_Library ft;
private:
	void render();
	std::string text;
	int fontsize;
	GLuint m_texture = 0;
	FT_Face face;
};

class TextBuilder {
public:
	TextBuilder(int top, int bottom, int width);
	virtual ~TextBuilder();

	void add(FT_GlyphSlot g);
	uint32_t& p(size_t wi, size_t pos) { return image[wi + (t - pos) * w]; }

	int width() { return w; }
	int height() { return t - b; }
	uint32_t *picture() { return image; }
private:
	uint32_t* image;
	int w, t, b;
};

#endif
