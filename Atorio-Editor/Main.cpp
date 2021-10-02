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


mat4 ortho(int W, int H, int x, int y, int w, int h) {
	mat4 m = MAT4_IDENTITY;
	m(0,0) = (float)w / W;
	m(1,1) = (float)h / H;
	m(3,0) = 2.0F * (0.5F * w + x) / W - 1.0F;
	m(3,1) = -(2.0F * (0.5F * h + y) / H - 1.0F);
	return m;
}


int main(int c, char** v) {
	System::init();
	Window window(863, 393, "Atorio Editor");
	System::glew();
	GLRectangle rect;
	rect.bind();

	std::vector<std::string> res = pfd::open_file::open_file("Open Image", System::home(), { "Image Files", "*.png *.jpg *.jpeg *.bmp" }).result();

	Texture image(res[0]);
	image.Bind();

	FilterDLL dll("Atorio-Filters");
	Filter* filter = dll.get("video-colorblindness");
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

		(*packet)["in"]["severity"].value.f = 1.0;
		(*packet)["in"]["colorblindness"].value.i32 = 1;

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
