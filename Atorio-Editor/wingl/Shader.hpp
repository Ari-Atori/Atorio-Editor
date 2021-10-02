
#ifndef ATORIO_SHADER
#define ATORIO_SHADER

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>

/* Shader is the class which loads the shader file, compiles it, initializes the
 * main attributes, creates the uniforms, assigns them values, and binds the shader.
 */

/* TODO: Rely strictly on macros defined in Packet.hpp instead */
#define UNIFORM_FLOAT 1
#define UNIFORM_VEC2F 2
#define UNIFORM_VEC3F 3
#define UNIFORM_VEC4F 4
#define UNIFORM_MAT4F 5

/* Uniform class is an object of Shader which nicely wraps up uniform data processing. */
class Uniform {
public:
	Uniform();
	Uniform(GLuint p, std::string n, int t, int c);
	Uniform(const Uniform& u);
	Uniform operator=(const Uniform& u);
	virtual ~Uniform();

	void set(void* D);

	std::string name;
	int type;
	int count;
	GLint location;
private:
	size_t size;
};

class Shader {
public:
	Shader(std::string, std::vector<std::string>);
	virtual ~Shader();

	void bind();

	void bindUniform(std::string, int, int);
	void setUniform(std::string, void*);
private:
	GLuint program;
	GLuint shaders[2];
	std::vector<std::string> attribs;
	std::vector<Uniform> uniforms;
};

#endif