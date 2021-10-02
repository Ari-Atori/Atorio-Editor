#include "Shader.hpp"

Uniform::Uniform() {
	name = "";
	type = 0;
	size = 0;
	count = 0;
	location = -1;
}

Uniform::Uniform(const Uniform& u) {
	name = u.name;
	type = u.type;
	size = u.size;
	count = u.count;
	location = u.location;
}

Uniform Uniform::operator=(const Uniform& u) {
	this->name = u.name;
	this->type = u.type;
	this->size = u.size;
	this->count = u.count;
	this->location = u.location;
	return (*this);
}

Uniform::Uniform(GLuint p, std::string n, int t, int c) {
	name = n;
	type = t;
	count = c;
	location = glGetUniformLocation(p, name.c_str());
}

Uniform::~Uniform() {}

/* Insert data into repected OpenGL functions given data type */
void Uniform::set(void* D) {
	switch (type) {
	case UNIFORM_FLOAT:
		glUniform1fv(location, count, (const GLfloat*) D);
		break;
	case UNIFORM_VEC2F:
		glUniform2fv(location, count, (const GLfloat*) D);
		break;
	case UNIFORM_VEC3F:
		glUniform3fv(location, count, (const GLfloat*) D);
		break;
	case UNIFORM_VEC4F:
		glUniform4fv(location, count, (const GLfloat*) D);
		break;
	case UNIFORM_MAT4F:
		glUniformMatrix4fv(location, count, GL_TRUE, (const GLfloat*) D); /* Gotta transpose */
		break;
	}
}