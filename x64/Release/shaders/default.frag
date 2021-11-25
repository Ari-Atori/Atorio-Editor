#version 130

in vec2 T;
uniform sampler2D diffuse;

void main() {
	gl_FragColor = texture2D(diffuse, T);
}
