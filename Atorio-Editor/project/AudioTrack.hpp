#ifndef ATORIO_PROJECT_AUDIOTRACKER
#define ATORIO_PROJECT_AUDIOTRACKER

#include "../io/AudioSource.hpp"

class AudioTrack {
public:
	AudioTrack(std::string filename);
	virtual ~AudioTrack();

	void play();
	void play(float sec);
	void pause();
	void setRepeat(bool state);
	static void audio44100(void* userdata, uint8_t* stream, int len) { audio(44100, (int16_t*)stream, len >> 1); }
	static void audio48000(void* userdata, uint8_t* stream, int len) { audio(48000, (int16_t*)stream, len >> 1); }

	static void audio(int hz, int16_t* stream, int len);
private:
	static std::vector<AudioTrack*> tracks;
	bool playing;
	size_t offset;
	AudioSource* source;
};

#endif
