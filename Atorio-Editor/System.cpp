
#include "System.hpp"
#include <iostream>
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <windows.h>
#include <userenv.h>
#include <libloaderapi.h>
#include "wingl/Window.hpp"
#include "wingl/Text.hpp"

Shader *Window::ui;
GLRectangle* Window::rect;
FT_Library Text::ft;


/* Initialize SDL and other basic elements */
void System::init() {
	if (!glfwInit()) {
		std::cout << "GLFW FAILED\n";
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(System::error);
	FT_Init_FreeType(&Text::ft);
}

/* GLFW error callback handler */
void System::error(int code, const char* description) {
	std::cout << "Error " << code << ": " << description << "\n";
}

/* Initialize GLEW */
void System::glew() {
	GLenum status = glewInit();
	if (status != GLEW_OK) exit(-1);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Window::ui = new Shader(System::parpexec() + "shaders/ui", std::vector<std::string> {"position", "texture"});
	Window::ui->bindUniform("p2Gm", UNIFORM_VEC2F, 1);
	Window::ui->bindUniform("p2Gb", UNIFORM_VEC2F, 1);
	Window::ui->bindUniform("bgcolor", UNIFORM_VEC4F, 1);
	Window::ui->bindUniform("center", UNIFORM_VEC2F, 1);
	Window::ui->bindUniform("border_radius", UNIFORM_VEC2F, 1);
	Window::ui->bindUniform("upperright", UNIFORM_VEC2F, 1);
	Window::ui->bindUniform("usestexture", UNIFORM_FLOAT, 1);

	Window::rect = new GLRectangle();
}

/* Call this to quit and release all resources properly */
int System::exit(int status) {
	delete Window::ui;
	delete Window::rect;
	glfwTerminate();
	FT_Done_Library(Text::ft);
	return status;
}

/* Grab pathname of this very executable */
std::string System::pexec() {
	char path[4097];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	return std::string(path);
}

std::string System::parpexec() {
	std::string str = pexec();
	return str.substr(0, str.find_last_of("/\\")) + "\\";
}

/* Change directory */
bool System::chdir(std::string str) {
	return SetCurrentDirectoryA(str.c_str());
}

/* Print working directory */
std::string System::pwd() {
	char path[4097];
	GetCurrentDirectoryA(4097, path);
	return std::string(path);
}

/* Retrieve architecture */
std::string System::arch() {
	return "x86-64";
}

/* Get username */
std::string System::user() {
	char name[256];
	DWORD size = 256;
	GetUserNameA(name, &size);
	return std::string(name, size - 1);
}

/* Get home directory */
std::string System::home() {
	return std::string("C:/Users/") + user() + "/";
}

/* Get Operating System */
std::string System::os() {
	return "Windows";
}
