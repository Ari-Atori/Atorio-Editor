#include "Resource.hpp"

Resource::Resource(std::string filename) {

}

Resource::~Resource() {

}

/* Default return state for invalid frame configurations */
static void black(int frames, void **images) {

}

/* Default return state for invalid sampling congifurations */
static void silence(int frames, void** images) {

}

/* Since libary files only deal with discrete frames, we need this wrapper function */
void Resource::getFrame(int vtrack, float stime, float duration, void** images) {
	int startFrame = (int) (v_configs[vtrack].fps * stime);
	/* to ensure all lingering frames are actually grabbed */
	int durations = (int)(v_configs[vtrack].fps * (stime + duration)) - startFrame + 1;
	frame(vtrack, startFrame, durations, images);
}

/* Since libary files only deal with discrete samples, we need this wrapper function */
void Resource::getAudio(int atrack, float stime, float duration, float* sound) {
	int startSample = (int)(v_configs[atrack].fps * stime);
	/* to ensure all lingering frames are actually grabbed */
	int durations = (int)(v_configs[atrack].fps * (stime + duration)) - startSample + 1;
	audio(atrack, startSample, durations, sound);
}

void Resource::frame(int vtrack, int sframe, int frames, void** images) {

}

void Resource::audio(int atrack, int start, int samples, void* sound) {

}

