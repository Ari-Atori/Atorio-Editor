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
#include <SDL2/SDL.h>
#include <windows.h>
#include "project/AudioTrack.hpp"
#include "wingl/comp/GLPanel.hpp"


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
	Window window(1080, 720, "Atorio Editor");
	System::glew();

	GLPanel* panel = new GLPanel(1080, 720, 0, 0, 540, 360, System::parpexec() + "shaders/default", 0xFF808080);
	Button* button1 = new Button(32, 32, 0, 0, 24, 24, System::parpexec() + "icons/buttons/new.png");
	Button* button2 = new Button(122, 32, 0, 0, 24, 24, System::parpexec() + "icons/buttons/save.png");

	window.addComponent(panel);
	panel->addComponent(button1);
	panel->addComponent(button2);
	//GLRectangle rect;
	//rect.bind();

	//std::vector<std::string> res = pfd::open_file::open_file("Open Image", System::home(), { "Image Files", "*.png *.jpg *.jpeg *.bmp" }).result();
	//std::vector<std::string> music = pfd::open_file::open_file("Open Music File", System::home(), { "Music Files", "*.mp3 *.wav *.ogg *.wma" }).result();
	//std::vector<std::string> song = pfd::open_file::open_file("Open Music File", System::home(), { "Music Files", "*.mp3 *.wav *.ogg *.wma" }).result();

	//Texture image(res[0]);
	//image.Bind();

	//AudioTrack a(music[0]);
	//a.play();
	//AudioTrack b(song[0]);
	//b.play();

	//SDL_PauseAudioDevice(System::dev44100, 0);

	//FilterDLL dll("Atorio-Filters");

	//Filter* filter = dll.get("video-transform");

	//if (!filter)
		//SDL_Log("Filter could not be loaded...\n");

	//Packet* packet = filter->copy();

	Core::running = true;
	std::thread t1(Core::tick);
	std::thread t2(Core::opengl);

	while (Window::windows() > 0) {
		window.current();
		window.draw();
		/*
		filter->bind(); image.Bind();

		(*packet)["in"]["sx"].value.f = 1.0;
		(*packet)["in"]["sy"].value.f = 1.0;
		(*packet)["in"]["kx"].value.f = 0.0;
		(*packet)["in"]["ky"].value.f = 0.0;
		(*packet)["in"]["r"].value.f  = 90.0;
		(*packet)["in"]["tx"].value.f = 0.0;
		(*packet)["in"]["ty"].value.f = 0.0;

		filter->compute(packet);
		*/
		//rect.draw();
		window.swap();
		Window::update();
	}
	Core::running = false;
	t1.join();
	t2.join();
	//delete packet;
	return System::exit(0);
}
