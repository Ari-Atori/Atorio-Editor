#ifndef ATORIO_HARDWARE
#define ATORIO_HARDWARE

#include <stdint.h>
#include <string>

class Hardware {
public:
	static void init();
private:
	static std::string cpu_brand, cpu_model;
	static int cores, cpu_mhertz;
	static std::string ram_model;
	static std::string ram_id;
	static int ram_mhertz, ram_mbytes;
	static std::string gpu_brand, gpu_model;
};

#endif