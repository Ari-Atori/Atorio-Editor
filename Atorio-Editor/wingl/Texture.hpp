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

	void Bind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture = 0;
};

#endif