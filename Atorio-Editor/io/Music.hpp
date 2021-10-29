#ifndef ATORIO_PROJECTS_MUSIC
#define ATORIO_PROJECTS_MUSIC

#include <stdint.h>

int16_t* wav_open(const char* fn, int channels, size_t* samples, size_t* sps);

#endif
