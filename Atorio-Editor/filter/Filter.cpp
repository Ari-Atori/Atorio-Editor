#include "Filter.hpp"
#include "../System.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

FilterDLL::FilterDLL(std::string fname) {
	std::string path = System::home() + "AppData/Local/Atorio/filters/" + fname + ".dll";
	/* Grab DLL functions */
	dll = LoadLibraryA(path.c_str());
	if (!dll) { SDL_Log("could not load the dynamic library, %s\n", path.c_str());  return; }
	function fn = (function)GetProcAddress(dll, "?get_filters@@YAX_KPEAX@Z");
	if (!fn) {
		SDL_Log("could not load the listing function\n");  return;
	}
	char* c = NULL;
	size_t n = 0;
	while (1) {
		fn(n++, &c);
		if (!c) break;
		filters.push_back(new Filter(c, dll));
	}
}

FilterDLL::~FilterDLL() {
	FreeLibrary(dll);
	for (size_t i = 0; i < filters.size(); ++i)
		delete filters[i];
	filters.clear();
}

Filter* FilterDLL::get(std::string name) {
	for (Filter* f : filters)
		if (f->name == name)
			return f;
	return NULL;
}

Filter::Filter(std::string name, HINSTANCE dll) {
	this->name = name;
	std::string path = System::home() + "AppData/Local/Atorio/filters/" + name + "/";
	SDL_Log("%s\n", path.c_str());
	config = JSON_IO::load(path + "config.json");

	/* TODO: support dynamic listing of shaders
	int n = config["shader"].size();
	for (int i = 0; i < n; ++i) {
		std::string shstr = config["shader"][i]["name"];
	}
	*/

	shader = new Shader(path + "shader", std::vector<std::string> { "position", "texture" });

	std::string str = config["code"];
	fn = (function)GetProcAddress(dll, str.c_str());
	if (!fn) { std::cout << "could not locate the function: " << name << std::endl; return; }
	tmplt = Packet::json(config);

	shader->bind();
	Packet* p = (Packet*) (*tmplt)["out"].value.v;
	for (int i = 0; i < (*tmplt)["out"].count; ++i)
		shader->bindUniform(p[i].name, p[i].type, p[i].count);
}

Filter::~Filter() {
	delete shader;
	Packet::clean(tmplt);
	delete tmplt;
}

void Filter::bind() {
	shader->bind();
}

void Filter::compute(Packet *packet) {
	fn(0, packet);
	Packet* p = (Packet*)(*packet)["out"].value.v;
	for (int i = 0; i < (*packet)["out"].count; ++i) {
		shader->setUniform(p[i].name, &p[i].value.v);
	}
}