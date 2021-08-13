#version 130

in vec4 position;
in vec2 texture;
uniform mat4 screen;
out vec2 T;

void main() {
	T = texture;
	gl_Position = screen * position;
}
