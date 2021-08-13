
#ifndef ATORIO_SHADER
#define ATORIO_SHADER

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>

//These must comply with Packet.hpp macros; TODO change to one set of tools
#define UNIFORM_VEC1F 1
#define UNIFORM_VEC2F 2
#define UNIFORM_VEC3F 3
#define UNIFORM_VEC4F 4
#define UNIFORM_MAT2F 0x22
#define UNIFORM_MAT3F 0x23
#define UNIFORM_MAT4F 5

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