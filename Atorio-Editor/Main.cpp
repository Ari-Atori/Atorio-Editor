#include <iostream>
#include <thread>
#include "System.hpp"
#include "wingl/GLWindow.hpp"
#include "wingl/Window.hpp"
#include "wingl/Shader.hpp"
#include "wingl/Texture.hpp"
#include "wingl/GLRectangle.hpp"
#include "Core.hpp"
#include "Packet.hpp"
#include "filter/Filter.hpp"
#include <pfd/pfd.hpp>

/*
M4 ortho(int W, int H, int x, int y, int w, int h) {
	M4 m = M4_IDENTITY;
	m.c[0][0] = (float)w / W;
	m.c[1][1] = (float)h / H;
	m.c[0][3] = 2.0F * (0.5F * w + x) / W - 1.0F;
	m.c[1][3] = -(2.0F * (0.5F * h + y) / H - 1.0F);
	return m;
}
*/

int main(int c, char** v) {
	System::init();
	Window window(960, 640, "Atorio Editor");
	System::glew();
	GLRectangle rect;
	rect.bind();

	std::vector<std::string> res = pfd::open_file::open_file("Open Image", System::home(), { "Image Files", "*.png *.jpg *.jpeg *.bmp" }).result();

	Texture image(res[0]);
	image.Bind();

	FilterDLL dll("Atorio-Filters");
	Filter* filter = dll.get("video-contrast");
	if (!filter)
		SDL_Log("Filter could not be loaded...\n");
	Packet* packet = filter->copy();

	Core::running = true;
	std::thread t1(Core::tick);
	std::thread t2(Core::opengl);

	while (Window::windows() > 0) {
		window.current();
		window.clear();
		filter->bind(); image.Bind();

		(*packet)["in"]["contrast"].value.f = 0.75;
		(*packet)["in"]["pivot"].value.f = 0.5;

		filter->compute(packet);

		rect.draw();
		window.swap();
		Window::update();
	}
	Core::running = false;
	t1.join();
	t2.join();
	delete packet;
	return System::exit(0);
}
