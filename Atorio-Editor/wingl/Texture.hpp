#ifndef ATORIO_TEXTURE
#define ATORIO_TEXTURE

#include <string>
#include <GL/glew.h>

/* Textures represent a way to pass an image
 * to OpenGL for rendering purposes
 */

class Texture {
public:
	Texture(const std::string& fileName);
	Texture(uint32_t color);

	void update(int width, int height, uint32_t *pixels);
	void Bind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture = 0;
};

#endif