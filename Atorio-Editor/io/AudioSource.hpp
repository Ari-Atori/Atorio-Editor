#ifndef ATORIO_IO_AUDIOSOURCE
#define ATORIO_IO_AUDIOSOURCE

#include <string>
#include <vector>
#include <stdint.h>

class AudioSource {
public:
	AudioSource(std::string filename);
	virtual ~AudioSource();

	int16_t *stream = NULL;
	size_t sps = 44100;
	size_t samples = 0;
	int channels = 2;
};

#endif
