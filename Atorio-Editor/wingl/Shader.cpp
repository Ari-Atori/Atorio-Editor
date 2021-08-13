#include "Shader.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

static void check(GLuint shader, GLuint flag, int isProgram, const char* errmsg) {
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isProgram) glGetProgramiv(shader, flag, &success); else glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram) glGetProgramInfoLog(shader, sizeof(error), NULL, error); else glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		printf("%s: '%s'\n", errmsg, error);
	}
}

static std::string load(const std::string& fn) {
	std::ifstream file;
	file.open((fn).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else { std::cerr << "Unable to load shader: " << fn << std::endl; }

	return output;
}

static GLuint compile(std::string filename, GLenum type) {
	std::string text = load(filename);

	GLuint shader = glCreateShader(type);
	const GLchar* shaderSS[1];
	GLint shaderSL[1];
	shaderSS[0] = text.c_str();
	shaderSL[0] = (GLint) text.length();

	glShaderSource(shader, 1, shaderSS, shaderSL);
	glCompileShader(shader);
	check(shader, GL_COMPILE_STATUS, 0, "Error: Shade compiling failed: ");

	return shader;
}

Shader::Shader(std::string fname, std::vector<std::string> attribs) {
	//SDL_Log("Creating program in shader %s\n", fname.c_str());
	program = glCreateProgram();
	std::string VS = fname + ".vert", FS = fname + ".frag";
	shaders[0] = compile(VS, GL_VERTEX_SHADER);
	shaders[1] = compile(FS, GL_FRAGMENT_SHADER);
	//SDL_Log("Compiled shaders %s\n", fname.c_str());
	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);
	//SDL_Log("Attached program to shader %s\n", fname.c_str());
	this->attribs = attribs;
	//SDL_Log("Copied attributes in shader %s\n", fname.c_str());
	for (size_t i = 0; i < attribs.size(); ++i)
		glBindAttribLocation(program, (GLint) i, attribs[i].c_str());
	//SDL_Log("Bound attributes in shader %s\n", fname.c_str());
	glLinkProgram(program);
	check(program, GL_LINK_STATUS, 1, "Error: Program linking failed: ");
	//SDL_Log("Linked program in shader %s\n", fname.c_str());
	glValidateProgram(program);
	check(program, GL_VALIDATE_STATUS, 1, "Error: Program is invalid: ");
	//SDL_Log("Validated attributes in shader %s\n", fname.c_str());
}

Shader::~Shader() {
	for (int i = 0; i < 2; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(program);
}

void Shader::bind() {
	glUseProgram(program);
}

void Shader::bindUniform(std::string name, int type, int count) {
	uniforms.push_back(Uniform(program, name, type, count));
}

void Shader::setUniform(std::string name, void* data) {
	for (size_t i = 0; i < uniforms.size(); ++i)
		if (uniforms[i].name == name) {
			uniforms[i].set(data);
			break;
		}
}