#include "Window.hpp"
#include <vector>
#include <algorithm>
#include <GL/glew.h>

std::vector<Window*> Window::list;

Window::Window(int width, int height, std::string title) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS);
	context = SDL_GL_CreateContext(window);
	
	//Image icon("icon.png");
	//SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(icon.data, 32, 32, 32, 128, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	//SDL_SetWindowIcon(window, surface);
	//SDL_FreeSurface(surface);
	
	/* Update the list of windows the poller has to check */
	list.push_back(this);

	closed = hidden = maximized = false;
	update();
}

Window::~Window() {
	SDL_DestroyWindow(window);
	list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

/* Grab list of all events, then update each window individually */
void Window::update() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		int id = e.window.windowID;
		Window* W = NULL;
		for (Window* w : list)
			if (SDL_GetWindowID(w->window) == id) {
				W = w;
				break;
			}
		if (e.type == SDL_QUIT) {
			for (Window* w : list)
				w->closed = true;
		}
		else if (W)
			W->events.push_back(e);
	}
	for (Window* w : list)
		w->update_local();
	SDL_Delay(20);
}

void Window::update_local() {
	keymouse.mouse.xrel = keymouse.mouse.yrel = 0;
	for (SDL_Event e : events)
		switch (e.type) {
			case SDL_KEYDOWN:
				keymouse.keys[e.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				keymouse.keys[e.key.keysym.scancode] = false;
				break;
			case SDL_MOUSEMOTION:
				keymouse.mouse.x = e.motion.x;
				keymouse.mouse.xrel = e.motion.xrel;
				keymouse.mouse.y = e.motion.y;
				keymouse.mouse.yrel = e.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				keymouse.mouse.buttons[e.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				keymouse.mouse.buttons[e.button.button] = false;
				break;
			case SDL_WINDOWEVENT:
				switch (e.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					break;
				case SDL_WINDOWEVENT_EXPOSED:
					break;
				case SDL_WINDOWEVENT_MOVED:
					break;
				case SDL_WINDOWEVENT_RESIZED:
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					current();
					glViewport(0, 0, (GLsizei)e.window.data1, (GLsizei)e.window.data2);
					glClear(GL_COLOR_BUFFER_BIT);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;
				case SDL_WINDOWEVENT_RESTORED:
					break;
				case SDL_WINDOWEVENT_ENTER:
					break;
				case SDL_WINDOWEVENT_LEAVE:
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;
				case SDL_WINDOWEVENT_CLOSE:
					closed = true;
					SDL_DestroyWindow(window);
					list.erase(std::remove(list.begin(), list.end(), this), list.end());
					window = NULL;
					break;
				case SDL_WINDOWEVENT_TAKE_FOCUS:
					break;
				case SDL_WINDOWEVENT_HIT_TEST:
					break;
				default:
					SDL_Log("Window %d got unknown event %d", e.window.windowID, e.window.event);
					break;
			}
		}
	events.empty();
}

void Window::clear() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap() {
	SDL_GL_SwapWindow(window);
}

void Window::current() {
	SDL_GL_MakeCurrent(window, context);
}

int Window::width() {
	int w;
	SDL_GetWindowSize(window, &w, NULL);
	return w;
}

int Window::height() {
	int h;
	SDL_GetWindowSize(window, NULL, &h);
	return h;
}

void Window::close() {
	SDL_DestroyWindow(window);
	closed = true;
}

void Window::minimize() {
	SDL_MinimizeWindow(window);
	hidden = true;
}

void Window::show() {
	SDL_RestoreWindow(window);
	hidden = false;
}

void Window::unmaximize() {
	SDL_RestoreWindow(window);
	maximized = false;
}

void Window::maximize() {
	SDL_MaximizeWindow(window);
	maximized = true;
}

void Window::resize(int w, int h) {
	SDL_SetWindowSize(window, w, h);
	maximized = false;
}

bool Window::getKey(int code) {
	return (code < 0 || code >= SDL_NUM_SCANCODES) ? false : keymouse.keys[code];
}

int Window::getX() {
	return keymouse.mouse.x;
}

int Window::getY() {
	return keymouse.mouse.y;
}

int Window::getXrel() {
	return keymouse.mouse.xrel;
}

int Window::getYrel() {
	return keymouse.mouse.yrel;
}

bool Window::getButton(int code) {
	return (code < 0 || code >= 32) ? false : keymouse.mouse.buttons[code];
}