#include "Component.hpp"
#include "../Window.hpp"
#include <iostream>

Component::~Component() {
	for (Component *c : components) delete c;
}

void Component::addc(Component* c) {
	components.push_back(c);
}

void Component::remc(Component* c) {
	components.erase(std::remove(components.begin(), components.end(), c), components.end());
}

void Component::draw(Box& window, Box& parent) {
	if (!style.display)
		return;

	uni.compute(&box, window, parent, style);

	vec4 transparent = { 0, 0, 0, 0 };
	if (style.background.image || style.background.color != transparent) {
		if (style.background.image) style.background.image->Bind();
		Window::ui->setUniform("p2Gm", &uni.p2Gm);
		Window::ui->setUniform("p2Gb", &uni.p2Gb);
		Window::ui->setUniform("bgcolor", &uni.background);
		Window::ui->setUniform("center", &uni.center);
		Window::ui->setUniform("upperright", &uni.upperright);
		Window::ui->setUniform("border_radius", &uni.border_radius);
		Window::ui->setUniform("usestexture", &uni.sampling);
		Window::rect->draw();
	}
	for (Component* c : components)
		c->draw(window, box);

}