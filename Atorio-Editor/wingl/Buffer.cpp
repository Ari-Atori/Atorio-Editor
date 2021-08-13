#include "Buffer.hpp"

Buffer::Buffer(int buffers) {
	glGenFramebuffers(BUFFER_SIZE, fbo);
	glGenTextures(1, &tex);
}

Buffer::~Buffer() {

}


void Buffer::bindFrame(int w, int h, void* data) {
	glBindTexture(GL_TEXTURE_2D, tex);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);
}

void Buffer::drawFrame(int in, int out) {

}

void Buffer::drawBuffer(int in, int out) {

} 