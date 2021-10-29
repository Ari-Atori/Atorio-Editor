
#include "System.hpp"
#include "project/AudioTrack.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <windows.h>
#include <userenv.h>
#include <libloaderapi.h>

SDL_AudioSpec System::want, System::have44100, System::have48000;
SDL_AudioDeviceID System::dev44100, System::dev48000;

/* Initialize SDL and other basic elements */
void System::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	want.freq = 44100;
	want.format = AUDIO_S16;
	want.channels = 2;
	want.samples = 4096;
	want.callback = AudioTrack::audio44100;
	dev44100 = SDL_OpenAudioDevice(NULL, 0, &want, &have44100, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
	want.freq = 48000;
	want.callback = AudioTrack::audio48000;
	dev48000 = SDL_OpenAudioDevice(NULL, 0, &want, &have48000, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
}

/* Initialize GLEW */
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

/* Call this to quit all resources properly */
int System::exit(int status) {
	SDL_CloseAudioDevice(dev44100);
	SDL_CloseAudioDevice(dev48000);
	SDL_Quit();
	return status;
}

/* Grab pathname of this very executable */
std::string System::pexec() {
	char path[4097];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	return std::string(path);
}

std::string System::parpexec() {
	std::string str = pexec();
	return str.substr(0, str.find_last_of("/\\")) + "\\";
}

/* Change directory */
bool System::chdir(std::string str) {
	return SetCurrentDirectoryA(str.c_str());
}

/* Print working directory */
std::string System::pwd() {
	char path[4097];
	GetCurrentDirectoryA(4097, path);
	return std::string(path);
}

/* Retrieve architecture */
std::string System::arch() {
	return "x86-64";
}

/* Get username */
std::string System::user() {
	char name[256];
	DWORD size = 256;
	GetUserNameA(name, &size);
	return std::string(name, size - 1);
}

/* Get home directory */
std::string System::home() {
	return std::string("C:/Users/") + user() + "/";
}

/* Get Operating System */
std::string System::os() {
	return "Windows";
}
