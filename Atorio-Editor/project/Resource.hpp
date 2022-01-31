#ifndef ATORIO_PROJECT_RESOURCE
#define ATORIO_PROJECT_RESOURCE

#include <stdio.h>
#include <string>

class Resource {
public:
	Resource(std::string filename);
	virtual ~Resource();

	void getFrame(int vtrack, float stime, float duration, void **images);
	void getAudio(int atrack, float stime, float duration, float *audio);

	void frame(int vtrack, int sframe, int frames, void** images);
	void audio(int atrack, int start, int samples, void* sound);
private:
	FILE* file;
	struct video_props {
		float speed;
		int width, height;
		float fps;
		int format;
		int colorspace;
		float aspect;
	} *v_configs;
	struct audio_props {
		float hertz;
		int format;
	} *a_configs;
};

#endif