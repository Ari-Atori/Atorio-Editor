#include "Filter.hpp"
#include "../System.hpp"
#include <iostream>
#include <vector>

/* Find the DLL given the file name */
FilterDLL::FilterDLL(std::string fname) {
	std::string path = System::home() + "AppData/Local/Atorio/filters/" + fname + ".dll";
	/* Grab DLL functions */
	dll = LoadLibraryA(path.c_str());
	if (!dll) { return; }
	/* Wacky string in the end helps with the signature of the functions, do not delete, or you will be */
	function fn = (function)GetProcAddress(dll, "?get_filters@@YAX_KPEAX@Z");
	if (!fn) {
		return;
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

/* Define the filter based on a name and the parent DLL */
Filter::Filter(std::string name, HINSTANCE dll) {
	this->name = name;
	std::string path = System::home() + "AppData/Local/Atorio/filters/" + name + "/";
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
	if (!fn) { return; }
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

/* Send input data to be crunched by the DLL */
void Filter::compute(Packet *packet) {
	fn(0, packet);
	Packet* p = (Packet*)(*packet)["out"].value.v;
	for (int i = 0; i < (*packet)["out"].count; ++i) {
		shader->setUniform(p[i].name, &p[i].value.v);
	}
}