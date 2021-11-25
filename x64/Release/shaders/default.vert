#version 130

in vec4 position;
in vec2 texture;
out vec2 T;

void main() {
	T = texture;
	gl_Position = position;
}
