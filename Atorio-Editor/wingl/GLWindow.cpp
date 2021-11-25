#include "GLWindow.hpp"
#include <GL/glew.h>
#include <iostream>
#include <chrono>

GLWindow::GLWindow(int width, int height, std::string title) {
	
	w = width; h = height;
}

GLWindow::~GLWindow() {
	
}

void GLWindow::clear() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::swap() {

}