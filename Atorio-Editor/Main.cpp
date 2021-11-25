#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "wingl/GLRectangle.hpp"
#include "wingl/Shader.hpp"
#include "System.hpp"
#include "wingl/Window.hpp"
#include "wingl/Text.hpp"

#include <iostream>
#include <vector>
#include <thread>

Component* right_side() {
	Component* c = new Component();
	c->style.position.left = 72;
	c->style.position.right = 0;
	c->style.position.uright = true;
	c->style.dimension.height = 1.0;
	c->style.dimension.pheight = true;
	c->style.background.color = { 40 / 256.0, 40 / 256.0, 40 / 256.0, 1 };
	return c;
}

void do_view1(Component *view) {
	Component *panel = new Component();
	panel->style.background.color = { 0, 0, 0, 0 };
	panel->style.position.uleft = false;
	panel->style.dimension.width = 544;
	panel->style.position.top = 16;
	panel->style.dimension.height = 128;
	panel->style.relative = true;
	view->addc(panel);
	Component* button = new Component();
	button->style.position.left = 0;
	button->style.position.top = 0;
	button->style.dimension = { 48, 48, false, false };
	button->style.background.image = new Texture(System::parpexec() + "icons/buttons/create_project.png");
	button->style.border = { 12, 12, false, false };
	panel->addc(button);
	Component *text1 = new Component();
	Component* text2 = new Component();
	text1->style.position.left = 60;
	text2->style.position.left = 0;
	text1->style.position.top = 0;
	text2->style.position.top = 60;
	text1->style.background.color = { 0, 0, 0, 1 };
	text2->style.background.color = { 0, 0, 0, 1 };
	text1->style.dimension.width = 240;
	text2->style.dimension.width = 300;
	text1->style.dimension.height = 24;
	text2->style.dimension.height = 24;
	panel->addc(text1);
	panel->addc(text2);
	Component* config = new Component();
	config->style.position.left = 312;
	config->style.position.top = 0;
	config->style.dimension = { 232, 128, false, false };
	config->style.border = { 0, 0, 0, 1 };
	panel->addc(config);
	
	Component* hr = new Component();
	hr->style.position.left = 16;
	hr->style.position.right = 16;
	hr->style.position.uright = true;
	hr->style.position.top = 160;
	hr->style.dimension.height = 1;
	hr->style.background.color = { 1, 1, 1, 1 };
	hr->style.relative = true;
	view->addc(hr);
}

void do_view4(Component* view) {
	Component* frame = new Component();
	frame->style.position.right = 16;
	frame->style.position.uright = true;
	frame->style.position.uleft = false;
	frame->style.position.top = 16;
	frame->style.dimension = { 240, 135, false, false };
	frame->style.background.image = new Texture(System::parpexec() + "toframe.png");
	view->addc(frame);
	
	Component* controls = new Component();
	controls->style.background.color = { 0,0,0,1 };
	controls->style.position.left = { 16 };
	controls->style.position.top = 16;
	controls->style.dimension = {128, 128, false, false};
	controls->style.relative = true;
	view->addc(controls);

	Component* nodetree = new Component();
	nodetree->style.background.color = { 0,0,0,1 };
	nodetree->style.position.left = 16;
	nodetree->style.position.bottom = 16;
	nodetree->style.position.ubottom = true;
	nodetree->style.position.utop = false;

	nodetree->style.dimension = { 128, 128, false, false };
	nodetree->style.relative = true;
	view->addc(nodetree);

	Component* scope = new Component();
	scope->style.position.right = 16;
	scope->style.position.uright = true;
	scope->style.position.uleft = false;
	scope->style.position.bottom = 16;
	scope->style.position.ubottom = true;
	scope->style.position.utop = false;
	scope->style.dimension = { 128, 128, false, false };
	scope->style.background.image = new Texture(System::parpexec() + "icons/vector_scope.png");

	view->addc(scope);
}

void do_view3(Component* view) {
	Component* frame = new Component();
	frame->style.position.uright = false;
	frame->style.position.uleft = false;
	frame->style.position.top = 16;
	frame->style.dimension = { 480, 270, false, false };
	frame->style.background.image = new Texture(System::parpexec() + "toframe.png");
	view->addc(frame);

	Component* controls = new Component();
	controls->style.position.uright = false;
	controls->style.position.uleft = false;
	controls->style.background.color = { 0,0,0,1 };
	controls->style.position.left = { 16 };
	controls->style.position.top = 286;
	controls->style.dimension = { 120, 24, false, false };
	controls->style.relative = true;
	view->addc(controls);

	Component* timeline = new Component();
	timeline->style.position.left = 16;
	timeline->style.position.right = 16;
	timeline->style.position.uright = true;
	timeline->style.background.color = { 0,0,0,1 };
	timeline->style.position.top = 326;
	timeline->style.position.bottom = 16;
	timeline->style.position.ubottom = true;
	view->addc(timeline);
}

int main(char *c, char** v) {
	System::init();
	Window *window = new Window(960, 540, "Atorio Editor");
	window->setSizeLimits(648, 432, GLFW_DONT_CARE, GLFW_DONT_CARE);
	System::glew();
	
	Component* comp = new Component();
	comp->style.position.left = 0;
	comp->style.dimension = { 72, 1, false, true };
	comp->style.background.color = { 20/256.0, 20 / 256.0, 20 / 256.0, 1 };

	Component* button = new Component();
	button->style.position.left = 12;
	button->style.position.top = 12;
	button->style.dimension = { 48, 48, false, false };
	button->style.background.image = new Texture(System::parpexec() + "icons/buttons/new_project.png");
	button->style.border = { 12, 12, false, false };

	Component* button2 = new Component();
	button2->style.position.left = 12;
	button2->style.position.top = 72;
	button2->style.dimension = { 48, 48, false, false };
	button2->style.background.image = new Texture(System::parpexec() + "icons/buttons/media_bins.png");
	button2->style.border = { 12, 12, false, false };

	Component* button3 = new Component();
	button3->style.position.left = 12;
	button3->style.position.top = 132;
	button3->style.dimension = { 48, 48, false, false };
	button3->style.background.image = new Texture(System::parpexec() + "icons/buttons/timelines.png");
	button3->style.border = { 12, 12, false, false };

	Component* button4 = new Component();
	button4->style.position.left = 12;
	button4->style.position.top = 192;
	button4->style.dimension = { 48, 48, false, false };
	button4->style.background.image = new Texture(System::parpexec() + "icons/buttons/filters.png");
	button4->style.border = { 12, 12, false, false };

	Component* button5 = new Component();
	button5->style.position.left = 12;
	button5->style.position.top = 252;
	button5->style.dimension = { 48, 48, false, false };
	button5->style.background.image = new Texture(System::parpexec() + "icons/buttons/export.png");
	button5->style.border = { 12, 12, false, false };

	Component* button6 = new Component();
	button6->style.position.left = 12;
	button6->style.position.bottom = 12;
	button6->style.position.ubottom = true;
	button6->style.position.utop = false;
	button6->style.dimension = { 48, 48, false, false };
	button6->style.background.image = new Texture(System::parpexec() + "icons/buttons/settings.png");
	button6->style.border = { 12, 12, false, false };

	comp->addc(button);
	comp->addc(button2);
	comp->addc(button3);
	comp->addc(button4);
	comp->addc(button5);
	comp->addc(button6);

	Component* view1 = right_side();
	do_view3(view1);

	//Component* view2 = right_side();
	// view2->style.background.color = { 100 / 256.0, 60 / 256.0, 60 / 256.0, 1 };
	// view2->style.display = false;


	window->addc(comp);
	window->addc(view1);
	//window->addc(view2);

	//Text test1(false, "arial.ttf", 48, "I need me a thiccc mama.");
	//Shader defaul(System::parpexec() + "shaders/default", std::vector<std::string> {"position", "texture"});

	while (!glfwWindowShouldClose(window->win())) { 
		glClear(GL_COLOR_BUFFER_BIT);
	   
		window->drawUI();

		//defaul.bind();
		//test1.bind();
		Window::rect->draw();

		glfwSwapBuffers(window->win());
		glfwPollEvents();
	}
	
	delete window;
   
	return System::exit(0);
}