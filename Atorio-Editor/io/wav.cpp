#ifndef ATORIO_WAV
#define ATORIO_WAV

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Music.hpp"

struct wav_riff {
	char riff[4]; // "RIFF"
	uint32_t size;
	char wave[4]; // "WAVE"
};

struct wav_format {
	char format[4]; // "fmt "
	uint32_t size; // always 16
	uint16_t channel[2]; // [0] = 1 | [1] = 1 for mono, 2 for stereo
	uint32_t sample; // Sample rate
	uint32_t bpsec; // Bytes per second;
	uint16_t bpsamp[2]; // [0] = 1 for 8m, 2 for 8s/16m, 4 for 16s | [1] = bits per sample
};

struct wav_data {
	char data[4]; // "data"
	uint32_t size;
	union { int8_t* b; int16_t* s; };
};

/* TODO Do data vlaidation after basic success */
int16_t *wav_open(const char* fn, int channels, size_t *samples, size_t *sps) {

	wav_riff header;
	wav_format metadata;
	wav_data data;

	FILE* f = fopen(fn, "rb");
	if (!f) return NULL;
	fread(&header, 1, sizeof(wav_riff), f);
	fread(&metadata, 1, sizeof(wav_format), f);
	*sps = metadata.bpsec / 2;

	char name[5]; uint32_t size;
	name[4] = 0;
	while (1) {
		fread(name, 1, 4, f);
		if (strnicmp(name, "data", 4)) break;
		fread(&size, 1, 4, f);
		fseek(f, size, SEEK_CUR);
	} 
	fread(&size, 1, 4, f);
	*samples = size >> 1;
	int16_t* stream = new int16_t[size];
	fread(stream, 1, size, f);
	fclose(f);
	return stream;
}

#endif