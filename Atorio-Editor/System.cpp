
#include "System.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <windows.h>
#include <userenv.h>
#include <libloaderapi.h>

void System::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	//SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void System::glew() {
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		SDL_Log("glewInit failed to initialize");
		exit(-1);
	}
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int System::exit(int status) {
	SDL_Quit();
	return status;
}

std::string System::pexec() {
	char path[4097];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	return std::string(path);
}

bool System::chdir(std::string str) {
	return SetCurrentDirectoryA(str.c_str());
}

std::string System::pwd() {
	char path[4097];
	GetCurrentDirectoryA(4097, path);
	return std::string(path);
}

std::string System::arch() {
	return "x86-64";
}

std::string System::user() {
	char name[256];
	DWORD size = 256;
	GetUserNameA(name, &size);
	return std::string(name, size - 1);
}

std::string System::home() {
	return std::string("C:/Users/") + user() + "/";
}

std::string System::os() {
	return "Windows";
}
