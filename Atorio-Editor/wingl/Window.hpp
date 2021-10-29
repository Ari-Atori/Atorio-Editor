#ifndef ATORIO_WINDOW
#define ATORIO_WINDOW

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "comp/Component.hpp"

/* Here is the wrapper class for SDL Window with OpenGL context
 * While incomplete as of now, functionalities will be slowly put in.
 */


class KeyboardMouse {
public:
	KeyboardMouse() {
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i) keys[i] = false;
		for (int i = 0; i < 32; ++i) mouse.buttons[i] = false;
	}

	bool keys[SDL_NUM_SCANCODES];
	struct { int x, y, xrel, yrel; bool buttons[32]; } mouse;
};

class Window {
public:
	Window(int, int, std::string);
	virtual ~Window();
	
	static int windows() { return (int) list.size(); }
	static void update();
	
	void clear();
	void addComponent(Component* comp);
	void draw();
	void update_local();
	void swap();
	void current();

	int width();
	int height();

	bool isClosed() { return closed; }
	bool isHidden() { return hidden; }
	bool isMaximized() { return maximized; }

	void close();
	void minimize();
	void show();
	void maximize();
	void unmaximize();
	void resize(int, int);

	bool getKey(int code);
	int getX();
	int getY();
	int getXrel();
	int getYrel();
	bool getButton(int code);
private:
	KeyboardMouse keymouse;
	bool closed, hidden, maximized;
	SDL_Window* window;
	SDL_GLContext context;
	std::vector<SDL_Event> events;
	std::vector<Component*> comps;
	static std::vector<Window*> list;
};

#endif