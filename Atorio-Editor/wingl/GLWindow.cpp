#include "GLWindow.hpp"
#include <GL/glew.h>
#include <iostream>
#include <chrono>

GLWindow::GLWindow(int width, int height, std::string title) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
	context = SDL_GL_CreateContext(window);
	w = width; h = height;
}

GLWindow::~GLWindow() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void GLWindow::clear() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::swap() {
	SDL_GL_SwapWindow(window);
}