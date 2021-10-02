#include "Core.hpp"
/* volatile keyword must be kept to prevent it being optimized away */
volatile bool Core::running;

void Core::tick() {
	while (running) {
		/* Move ALL basic functions into here */
	}
}

void Core::opengl() {
	while (running) {
		/* Move ALL openGL code into here */
	}
}
