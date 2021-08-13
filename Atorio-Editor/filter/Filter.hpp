#ifndef ATORIO_FILTER
#define ATORIO_FILTER

#include "../io/JSON_W.hpp"
#include <string>
#include <GL/glew.h>
#include "../Packet.hpp"
#include <stdint.h>
#include "../wingl/Shader.hpp"
#include <windows.h>

#define FILTER_CONFIG	0
#define FILTER_OPENGL	1
#define FILTER_LAYER	2
#define FILTER_INPUT	3
#define FILTER_KEYFRAME	4
#define FILTER_UNIFORM	5

typedef void (__stdcall* function)(size_t, void*);

class Filter {
public:
	std::string name;
	Filter(std::string name, HINSTANCE dll);
	virtual ~Filter();

	Packet* copy() { return Packet::copy(tmplt); }
	void bind();
	void compute(Packet*);
private:
	bool usesgpu = false;
	function fn = NULL;
	function cpufn = NULL;
	Shader* shader = NULL;
	JSON config;
	Packet* tmplt = NULL;
};

class FilterDLL {
public:
	FilterDLL(std::string fname);
	virtual ~FilterDLL();
	Filter* get(std::string name);
	HINSTANCE dll = NULL;
	std::vector<Filter*> filters;
};



#endif
