#ifndef ATORIO_PROJECT_RESOURCE
#define ATORIO_PROJECT_RESOURCE

#include <stdio.h>
#include <string>

class Resource {
public:
	Resource(std::string filename);
	virtual ~Resource();

	void get_frame(int vtrack, int frames, void** images);
	void get_audio(int atrack, int frames, float *audio);
private:
	FILE* file;
	struct {
		double spped;
		bool pitch_compensation;
		double duration;
	};
	struct video_props {
		double speed;
		int width, height;
		double fps;
		int format;
		int colorspace;
		int wr, hr;

	} *v_configs;
	struct audio_props {
		double props;
	} *a_configs;
};

#endif