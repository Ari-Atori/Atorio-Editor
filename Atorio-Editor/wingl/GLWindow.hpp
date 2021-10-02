#ifndef ATORIO_GLWINDOW
#define ATORIO_GLWINDOW

#include <SDL2/SDL.h>
#include <string>

/* This will be the hidden window for exporting reasons. */

class GLWindow {
public:
	GLWindow(int, int, std::string);
	virtual ~GLWindow();
	void clear();
	void swap();

	int width() { return w; }
	int height() { return h; }
	void current() { SDL_GL_MakeCurrent(window, context); }

private:
	SDL_Window* window;
	SDL_GLContext context;
	int w, h;
};

#endif