#include "Packet.hpp"
#include <SDL2/SDL.h>

Packet null = { "", 0, 0, {0} };

Packet& Packet::operator[](const char* name) {
	Packet* list = (Packet*)value.v;
	for (uint32_t i = 0; i < count; ++i)
		if (!strcmp(name, list[i].name))
			return list[i];
	return null;
}

static int get_type(std::string type) {
	if (type == "float") return PACKET_FLOAT;
	if (type == "vec2") return PACKET_VEC2;
	if (type == "vec3") return PACKET_VEC3;
	if (type == "vec4") return PACKET_VEC4;
	if (type == "mat4") return PACKET_MAT4;
	if (type == "int") return PACKET_INT32;
	if (type == "long") return PACKET_INT64;
	if (type == "text") return PACKET_STRING;
	else return PACKET_PACKET;
}

Packet* Packet::json(JSON json) {
	Packet* root = new Packet;
	strcpy_s(root->name, 32, "/");
	root->type = PACKET_PACKET;
	root->count = 3;
	Packet* children = new Packet[3];
	root->value.v = children;
	
	//TODO create interface material here
	strcpy_s(children[0].name, 32, "content");
	children[0].type = PACKET_PACKET;
	children[0].count = 0;
	

	/* List of inputs */
	strcpy_s(children[1].name, 32, "in");
	children[1].type = PACKET_PACKET;
	children[1].count = json["inputs"].size();
	Packet* inputs = new Packet[children[1].count];
	children[1].value.v = inputs;

	

	for (int i = 0; i < children[1].count; ++i) {
		std::string name = json["inputs"][i]["name"];
		strcpy_s(inputs[i].name, 32, name.c_str());
		inputs[i].count = 1;
		inputs[i].type = get_type(json["inputs"][i]["type"]);
		inputs[i].value.f = 0;
		
	}

	/* List of outputs */
	strcpy_s(children[2].name, 32, "out");
	children[2].type = PACKET_PACKET;
	children[2].count = json["shaders"][0]["outputs"].size();
	Packet* outputs = new Packet[children[2].count];
	children[2].value.v = outputs;

	

	for (int i = 0; i < children[2].count; ++i) {
		std::string name = json["shaders"][0]["outputs"][i]["name"];
		strcpy_s(outputs[i].name, 32, name.c_str());
		outputs[i].count = 1;
		outputs[i].type = get_type(json["shaders"][0]["outputs"][i]["type"]);
		outputs[i].value.f = 0;
		
	}

	return root;
}

static void recurse_copy(Packet* dest, Packet* src) {
	strcpy_s(dest->name, 32, src->name);
	dest->count = src->count;
	dest->type = src->type;
	if (dest->type == PACKET_PACKET) {
		Packet* pot = new Packet[dest->count];
		Packet* pin = (Packet*)src->value.v;
		dest->value.v = pot;
		for (int i = 0; i < dest->count; ++i)
			recurse_copy(&pot[i], &pin[i]);
	}
	//TODO have the code deal with arrays
}

//Does not copy values, as the thing copied would be the template
Packet* Packet::copy(Packet* src) {
	Packet* root = new Packet;
	recurse_copy(root, src);
	return root;
}

void Packet::clean(Packet* pck) {
	if (pck->type != PACKET_PACKET)
		return;
	Packet* pcks = (Packet*)pck->value.v;
	for (int i = 0; i < pck->count; ++i)
		clean(&pck[i]);
	delete pck->value.v;
	//TODO have the code deal with arrays
}