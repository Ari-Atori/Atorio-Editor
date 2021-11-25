#include "Window.hpp"
#include <vector>
#include <algorithm>
#include "../System.hpp"
#include <iostream>

std::vector<Window*> Window::windows;

Window::Window(int width, int height, std::string title) {
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	closed = hidden = maximized = false;
	
	glfwSetKeyCallback(window, callbackKey);
	glfwSetCharCallback(window, callbackChar);
	glfwSetCursorPosCallback(window, callbackPos);
	glfwSetCursorEnterCallback(window, callbackEnter);
	glfwSetMouseButtonCallback(window, callbackButton);
	glfwSetScrollCallback(window, callbackScroll);
	glfwSetFramebufferSizeCallback(window, callbackResize);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	this->width = width, this->height = height;
	windows.push_back(this);
}



Window::~Window() {
	windows.erase(std::remove(windows.begin(), windows.end(), this), windows.end());
	glfwDestroyWindow(window);
}

void Window::drawUI() {
	ui->bind();
	rect->bind();
	box = { 0, 0, width, height };
	for (Component *c : components)
		c->draw(box, box);
}

/*******************************************************
 **********  LIST OF ALL CALLBACKS BELOW ***************
 *******************************************************/

void Window::callbackKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Window::callbackChar(GLFWwindow* window, unsigned int unicode) {

}

void Window::callbackPos(GLFWwindow* window, double xpos, double ypos) {

}

void Window::callbackEnter(GLFWwindow* window, int entered) {

}

void Window::callbackButton(GLFWwindow* window, int button, int action, int mods) {

}

void Window::callbackScroll(GLFWwindow* window, double xoffset, double yoffset) {

}


void Window::callbackResize(GLFWwindow* window, int width, int height) {
	Window* w = getWindow(window);
	if (w->width == width && w->height == height) return;
	glViewport(0, 0, width, height);
	w->width = width;
	w->height = height;
	w->drawUI();
	glfwSwapBuffers(w->win());
}
