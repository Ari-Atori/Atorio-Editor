#include "Hardware.hpp"
#include "Builtins.hpp"
#include <Windows.h>
#include <iostream>
#include <GL/glew.h>

std::string Hardware::cpu_brand, Hardware::cpu_model;
int Hardware::cores, Hardware::cpu_mhertz;
std::string Hardware::ram_model;
std::string Hardware::ram_id;
int Hardware::ram_mhertz, Hardware::ram_mbytes;
std::string Hardware::gpu_brand, Hardware::gpu_model;

void Hardware::init() {
    union { uint32_t u[4]; uint8_t b[16]; } u;
    char name[48];
    
    // Get the information associated with each extended ID.

    bi_cpuid(0, 0, u.u);
    u.u[2] ^= u.u[3];
    u.u[3] ^= u.u[2];
    u.u[2] ^= u.u[3];

    cpu_brand = std::string((char*) &u.b[4], 12);

    std::cout << "CPU Brand: " << cpu_brand << std::endl;


    bi_cpuid(0x80000002, 0, &name[ 0]);
    bi_cpuid(0x80000003, 0, &name[16]);
    bi_cpuid(0x80000004, 0, &name[32]);

    cpu_model = std::string(name, 48);

    std::cout << "CPU Model: " << cpu_model << std::endl;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "Number of Cores: " << sysInfo.dwNumberOfProcessors << std::endl;

    char* vendor = (char*) glGetString(GL_VENDOR);
    char* renderer = (char*) glGetString(GL_RENDERER);

    gpu_brand = std::string(vendor);
    gpu_model = std::string(renderer);

    std::cout << "GPU Brand: " << gpu_brand << std::endl;
    std::cout << "GPU Model: " << gpu_model << std::endl;

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    std::cout << "Total System Memory: " << (statex.ullTotalPhys / 1024) / 1024 << "MB" << std::endl;
    std::cout << "Total Available Memory: " << (statex.ullAvailPhys / 1024) / 1024 << "MB" << std::endl;
}