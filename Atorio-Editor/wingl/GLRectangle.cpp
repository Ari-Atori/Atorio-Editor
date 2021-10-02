#include "GLRectangle.hpp"
#include "../math/Vector.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>

/* Create a regular rectangle that spans the whole OpenGL plane */
GLRectangle::GLRectangle() {
	vec4 pos[4] = { {-1, 1, 0, 1}, { 1, 1, 0, 1}, { 1,-1, 0, 1}, {-1,-1, 0, 1} };

	vec2 tex[4] = { { 0, 0}, { 1, 0}, { 1, 1}, { 0, 1} };

	unsigned int ind[6] = {0, 1, 2, 0, 2, 3};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec4), pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec2), tex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), ind, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

GLRectangle::~GLRectangle() {
	glDeleteBuffers(3, vbo);
	glDeleteVertexArrays(1, &vao);
}

void GLRectangle::bind() {
	glBindVertexArray(vao);
}

void GLRectangle::draw() {
	glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 0);
}