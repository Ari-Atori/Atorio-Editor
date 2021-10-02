#ifndef ATORIO_BUFFER
#define ATORIO_BUFFER

#include <GL/glew.h>

/* This section is the core of the buffer process. The code requires
 * the texture to be stored in a frame buffer, have the shader write
 * into another frame buffer, and have the final value written to
 * the first buffer. The copying was initially done with the shader
 * drawing to the frame buffer, calling glReadPixels(), and then
 * setting that output as the new texture for the next filter in
 * line. What we realized early is our older method is insanely
 * slow. For a GTX 1060 6GB to 3200 MHz RAM with a 3.7 GHz CPU, it
 * took on average 2500 microseconds from video to main memory. If
 * we want to be real-time in this program, we only have 16666
 * microseconds to complete each frame in a 60 FPS video. Our
 * solution is to use render and frame buffers throughout the whole
 * drawing process, as that will keep all memories in the GPU,
 * minimizing memory transfers and maximizing drawing speeds.
 */

#define BUFFER_SIZE 5

class Buffer {
public:
	Buffer(int buffers);
	virtual ~Buffer();
	
	void bindFrame(int w, int h, void* data);
	void drawFrame(int in, int out);
	void drawBuffer(int in, int out);

private:
	GLuint fbo[BUFFER_SIZE], tex;

};

#endif
