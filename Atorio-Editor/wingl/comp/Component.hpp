#ifndef ATORIO_WINGL_COMP_COMPONENT
#define ATORIO_WINGL_COMP_COMPONENT

#include "../Style.hpp"
#include <vector>

class Component {
public:
	Component() {}
	virtual ~Component();
	void addc(Component *c);
	void remc(Component *c);
	void draw(Box& window, Box& parent);
	Style style;
	StyleUniform uni;
protected:
	std::vector<Component*> components;
	Box box;
};

#endif