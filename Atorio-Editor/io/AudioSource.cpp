#include "AudioSource.hpp"
#include <math.h>

struct wav_riff {
	char riff[4]; // "RIFF"
	uint32_t size;
	char wave[4]; // "WAVE"
};

struct wav_format {
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

int16_t inter(double d1, double d2, double y1, double y2, double p) {
	double d = y1;
	double c = d1;
	double b = 3*(y2 - y1) - 2*d1 - d2;
	double a = 2*(y1 - y2) + d1 + d2;
	return (int16_t)((((a * p) + b * p) + c * p) + d);
}

/* TODO Do data vlaidation after basic success */
int16_t* wav_open(const char* fn, int channels, size_t* samples, size_t* sps) {

	wav_riff header;
	wav_format metadata;
	wav_data data;

	FILE* f;
	fopen_s(&f, fn, "rb");
	if (!f) return NULL;
	fread(&header, 1, sizeof(wav_riff), f);

	//fread(&metadata, 1, sizeof(wav_format), f);
	//*sps = metadata.bpsec / 2;

	char name[5]; uint32_t size;
	name[4] = 0;
	while (1) {
		fread(name, 1, 4, f);
		if (!strncmp(name, "data", 4)) break;
		fread(&size, 1, 4, f);
		//SDL_Log("%s %u\n", name, size);
		if (!strncmp(name, "fmt ", 4)) {
			fread(&metadata, 1, sizeof(wav_format), f);
			SDL_Log("%hu %u %u %hu %hu", metadata.channel[1], metadata.sample, metadata.bpsec, metadata.bpsamp[0], metadata.bpsamp[1]);
		}
		else fseek(f, size, SEEK_CUR);
	}
	*sps = metadata.sample;
	fread(&size, 1, 4, f);
	SDL_Log("%s %u\n", name, size);
	*samples = size >> 1;
	int16_t* stream = new int16_t[size];
	fread(stream, 1, size, f);
	fclose(f);
	return stream;
}

AudioSource::AudioSource(std::string filename) {
    channels = 2;
    stream = wav_open(filename.c_str(), 2, &samples, &sps);
}

AudioSource::~AudioSource() {
    delete stream;
}