#ifndef ATORIO_WINDOW
#define ATORIO_WINDOW

#include <string>
#include <vector>
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "GLRectangle.hpp"
#include "comp/Component.hpp"
#include <vector>


class KeyboardMouse {
public:
	KeyboardMouse() {
		for (int i = 0; i <= GLFW_KEY_LAST; ++i) keys[i] = false; //TODO: FIND NUMBER OF KEY CODES
		for (int i = 0; i < 32; ++i) mouse.buttons[i] = false;
	}

	bool keys[GLFW_KEY_LAST + 1];
	struct { int x, y, xrel, yrel; bool buttons[32]; } mouse;
};

class Window : public Component {
public:
	Window(int, int, std::string);
	virtual ~Window();

	void drawUI();

	void setSizeLimits(int minw, int minh, int maxw, int maxh) { glfwSetWindowSizeLimits(window, minw, minh, maxw, maxh); }

	static void callbackKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void callbackChar(GLFWwindow* window, unsigned int unicode);
	static void callbackPos(GLFWwindow* window, double xpos, double ypos);
	static void callbackEnter(GLFWwindow* window, int entered);
	static void callbackButton(GLFWwindow* window, int button, int action, int mods);
	static void callbackScroll(GLFWwindow* window, double xoffset, double yoffset);
	
	static void callbackResize(GLFWwindow* window, int width, int height);

	GLFWwindow* win() { return window; }
	static Shader* ui;
	static GLRectangle *rect;
private:
	static std::vector<Window*> windows;
	static Window* getWindow(GLFWwindow* W) { for (Window* w : windows) if (w->window == W) return w; return NULL; }
	GLFWwindow* window;
	KeyboardMouse keymouse;
	bool closed = false, hidden = false , maximized = false;
	int width, height;
};

#endif