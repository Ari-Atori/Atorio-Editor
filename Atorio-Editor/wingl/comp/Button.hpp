#ifndef ATORIO_WINGL_COMP_BUTTON
#define ATORIO_WINGL_COMP_BUTTON

#include <vector>
#include "Component.hpp"
#include <string>

class Button : public Component {
public:
	Button(int x, int y, int rx, int ry, int w, int h, std::string filename);
	virtual ~Button();
private:
	
};

#endif