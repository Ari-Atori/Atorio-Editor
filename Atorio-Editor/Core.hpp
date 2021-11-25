#ifndef ATORIO_CORE
#define ATORIO_CORE

#include "wingl/Window.hpp"
#include "wingl/GLWindow.hpp"

/* Here will be the core functions for this app. One will deal
 * with everyday operations, and one thread specifically for
 * OpenGL, and that's because OpenGL really likes to only operate
 * on one thread. There are actually three threads, the third being
 * for the event polling loop so it does not block other threads.
 */

class Core {
	public:
	static void tick();
	static void opengl();

	static volatile bool running;
	static volatile bool init;

	static Window *windowm, *windows;
	static GLWindow *renderer, *exporter;
};

#endif
