#include "Text.hpp"

#include <stb/stb_image_write.h>
#include <iostream>

Text::Text(bool local, std::string filename, int size, std::string text) {
	if (!local) filename = "C:/Windows/Fonts/" + filename;
	//std::cout << "LOADING FONT: " << filename << std::endl;
	FT_New_Face(ft, filename.c_str(), 0, &face);
	FT_Set_Pixel_Sizes(face, 0, size);
	fontsize = size;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	this->text = text;
	render();
}

Text::~Text() {
	glDeleteTextures(1, &m_texture);
	FT_Done_Face(face);
}

void Text::setFontSize(int fs) {
	fontsize = fs;
	FT_Set_Pixel_Sizes(face, 0, fontsize);
	render();
}

void Text::setText(std::string t) {
	text = t;
	render();
}

void Text::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Text::render() {
	int top = 0, bottom = 0, width = 0;
	const char* c = text.c_str();
	//For each letter in the text
	TextBuilder tx(0,0,0);
	////std::cout << "RENDERING: " << text << std::endl;;
	for (; *c; ++c) {
		////std::cout << "\nREADING GLYPH: " << std::endl;
		if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
			continue;
		////std::cout << "RENDERING GLYPH: " << *c << std::endl;
		tx.add(face->glyph);
	}
	////std::cout << "TEXT RENDER: " << tx.width() << "x" << tx.height() << std::endl;
	stbi_write_png("glyphs.png", tx.width(), tx.height(), 4, tx.picture(), tx.width() * 4);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, tx.width(), tx.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tx.picture());
}


TextBuilder::TextBuilder(int top, int bottom, int W) {
	t = top;
	b = bottom;
	w = W;
	int D = width() * height();
	image = new uint32_t[D];
	for (int i = 0; i < D; ++i) image[i] = 0;
}

TextBuilder::~TextBuilder() {
	if (image)
		delete[] image;
}

void TextBuilder::add(FT_GlyphSlot g) {
	int T = g->bitmap_top, B = T - g->bitmap.rows, W = g->bitmap.width, F = g->advance.x >> 6; // get glyph top, bottom, and width
	int mT = (T > t) ? T : t, mB = (B < b) ? B : b; //Get new top and bottom for image resizing
	F = (W > F) ? W : F;
	int nW = w + F; // get new width
	
	//std::cout << "NEW CHARACTER GLYPH: (" << T << "," << B << ") x " << W  << std::endl;
	//std::cout << "NEW CHARACTER GLYPH: (" << mT << "," << mB << ") x " << nW  << std::endl;
	//std::cout << "NEW CHARACTER GLYPH: (" << W << "," << F << ")" << std::endl;
	
	//std::cout << "CREATING TEXT BUILDER" << std::endl;
	TextBuilder N(mT, mB, nW);
	
	//std::cout << "COPYING ORIGINAL TEXT DATA OVER" << std::endl;
	for (int i = 0; i < w; ++i)
		for (int j = t; j > b; --j)
			N.p(i, j) = p(i, j);
	
	//std::cout << "COPYING NEW GLYPH OVER" << std::endl;
	for (int i = 0; i < W; ++i)
		for (int j = T; j > B; --j)
			N.p(i + w, j) = 0x00FFFFFF | (g->bitmap.buffer[i + (T - j) * W] << 24);
	
	//std::cout << "TRANSFERRING SHIT OVER" << std::endl;
	delete[] image;
	image = N.image;
	N.image = NULL;
	w = nW, t = mT, b = mB;
	//std::cout << "DONE TRANSFERRING SHIT OVER" << std::endl;
	
}