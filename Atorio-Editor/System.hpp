#ifndef ATORIO_SYSTEM
#define ATORIO_SYSTEM

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
private:
	static void error(int code, const char* description);
};

#endif
