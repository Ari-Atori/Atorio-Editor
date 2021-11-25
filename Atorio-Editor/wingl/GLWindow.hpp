#ifndef ATORIO_GLWINDOW
#define ATORIO_GLWINDOW

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
	void current() { }

private:
	int w, h;
};

#endif