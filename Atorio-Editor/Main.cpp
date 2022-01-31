#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "wingl/GLRectangle.hpp"
#include "wingl/Shader.hpp"
#include "System.hpp"
#include "wingl/Window.hpp"
#include "wingl/Text.hpp"
#include "Hardware.hpp"

#include <iostream>
#include <vector>
#include <thread>

#include "Builtins.hpp"

Component* right_side() {
	Component* c = new Component();
	c->style.set(SN_POSITION_LEFT, "72px");
	c->style.set(SN_POSITION_RIGHT, "0px");
	c->style.set(SN_HEIGHT, "100%");
	c->style.set(SN_BACKGROUND_COLOR, "#282828FF");
	return c;
}

void do_view3(Component* view) {

	Component* view1 = new Component();
	view1->style.set(SN_POSITION_TOP, "0px");
	view1->style.set(SN_HEIGHT, "50%");
	view1->style.set(SN_WIDTH, "100%");
	view->addc(view1);
	Component* view2 = new Component();
	view2->style.set(SN_POSITION_BOTTOM, "0px");
	view2->style.set(SN_HEIGHT, "50%");
	view2->style.set(SN_WIDTH, "100%");
	view->addc(view2);

	Component* frame = new Component();

	frame->style.set(SN_POSITION_TOP, "16px");
	frame->style.set(SN_ASPECT_RATIO, "1.777777777777");
	frame->style.set(SN_POSITION_BOTTOM, "0px");
	frame->style.set(SN_BACKGROUND_IMAGE, System::parpexec() + "toframe.png");

	view1->addc(frame);

	Component* controls = new Component();
	controls->style.set(SN_BACKGROUND_COLOR, "#000000FF");
	controls->style.set(SN_POSITION_TOP, "0px");
	controls->style.set(SN_WIDTH, "120px");
	controls->style.set(SN_HEIGHT, "24px");
	view2->addc(controls);

	Component* timeline = new Component();
	timeline->style.set(SN_POSITION_LEFT, "16px");
	timeline->style.set(SN_POSITION_RIGHT, "16px");
	timeline->style.set(SN_BACKGROUND_COLOR, "#000000FF");
	timeline->style.set(SN_POSITION_TOP, "40px");
	timeline->style.set(SN_POSITION_BOTTOM, "16px");
	view2->addc(timeline);
}

int main(char *c, char** v) {

	union {
		uint8_t b[4]; uint32_t i;
	} color;
	color.i = i420_rgb(240, 128, 128);
	std::cout << (int)color.b[0] << " " << (int)color.b[1] << " " << (int)color.b[2] << " " << (int) color.b[3] << std::endl;

	System::init();
	Window *window = new Window(960, 540, "Atorio Editor");
	window->setSizeLimits(648, 432, GLFW_DONT_CARE, GLFW_DONT_CARE);
	System::glew();
	
	Component* comp = new Component();
	comp->style.set(SN_POSITION_LEFT, "0px");
	comp->style.set(SN_WIDTH, "72px");
	comp->style.set(SN_HEIGHT, "100%");
	comp->style.set(SN_BACKGROUND_COLOR, "#141414FF");

	Component* button = new Component();

	Component* buttons[6];
	std::string files[6] = { "new_project.png", "media_bins.png", "timelines.png", "filters.png", "export.png", "settings.png"};
	for (int i = 0; i < 6; ++i) {
		buttons[i] = new Component();
		buttons[i]->style.set(SN_POSITION_LEFT, "12px");
		if (i < 5)
			buttons[i]->style.set(SN_POSITION_TOP, std::to_string(12 + 60 * i) + "px");
		else
			buttons[i]->style.set(SN_POSITION_BOTTOM, "12px");
		buttons[i]->style.set(SN_WIDTH, "48px");
		buttons[i]->style.set(SN_HEIGHT, "48px");
		buttons[i]->style.set(SN_BACKGROUND_IMAGE, System::parpexec() + "icons/buttons/" + files[i]);
		buttons[i]->style.set(SN_BORDER_RADIUS, "12px");
		comp->addc(buttons[i]);
	}

	Component* view3 = right_side();
	do_view3(view3);

	Hardware::init();

	window->addc(comp);
	window->addc(view3);

	while (!glfwWindowShouldClose(window->win())) { 
		glClear(GL_COLOR_BUFFER_BIT);
	   
		window->drawUI();

		Window::rect->draw();

		glfwSwapBuffers(window->win());
		glfwPollEvents();
	}
	
	delete window;
   
	return System::exit(0);
}