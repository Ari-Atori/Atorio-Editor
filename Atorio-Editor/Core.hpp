#ifndef ATORIO_CORE
#define ATORIO_CORE

class Core {
	public:
	static void tick();
	static void opengl();

	static volatile bool running;
};

#endif
