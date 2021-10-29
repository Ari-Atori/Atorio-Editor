#ifndef ATORIO_SYSTEM
#define ATORIO_SYSTEM

#include <SDL2/SDL.h>
#include <string>

/* This class handles all of the basic functionalities that are
 * essential for starting the application up. Formatted in a way
 * where different operating system support in the future
 * would not be as obtuse.
 */

class System {
public:
	static void init();
	static void glew();
	static int exit(int status);

	static std::string pexec();
	static std::string parpexec();
	static bool chdir(std::string);
	static std::string pwd();
	static std::string arch();
	static std::string user();
	static std::string home();
	static std::string os();
	static SDL_AudioDeviceID dev44100, dev48000;
	static SDL_AudioSpec want, have44100, have48000;
};

#endif
