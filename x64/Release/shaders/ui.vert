#version 130

in vec4 position;
in vec2 texture;

uniform vec2 p2Gm, p2Gb;
//uniform mat4 posCrop;
//uniform mat4 texMod;

out vec2 T;
out vec2 P;

void main() {
	T = texture;//(texMod * vec4(texture, 0, 1)).xy;
	P = position.xy * p2Gm + p2Gb;
	gl_Position = vec4(position.xy * p2Gm + p2Gb, 0, 1);
}
