#version 130

in vec4 color; 

vec3 vmax(vec3 v) {
	float m = max(max(v.x, v.y), v.z);
	vec3 ret;
	ret.x = float(m == v.x); ret.y = float(m == v.y) * (1.0 - ret.x); ret.z = float(m == v.z) * (1.0 - ret.x - ret.y);
	return ret;
}

vec3 rgb2hsl(vec3 c) {
	float e = 1.0e-16;
	float V = max(max(c.r, c.g), c.b), V_ = min(min(c.r, c.g), c.b), L = 0.5 * (V + V_), C = V - V_;
	vec3 h = 60.0 * vec3(mod((c.g-c.b)/(C+e),6.0), 2.0 + (c.b-c.r)/(C+e), 4.0 + (c.r-c.g)/(C+e));
	return vec3(dot(h, vmax(c)), (V-L)/(e+min(L,1.0-L)), L);
}

void main() {
	vec3 hsl = rgb2hsl(color);
	vec2 xy = vec2(cos(radians(hsl.x), sin(radians(hsl.x))) * hsl.y * 0.937;
	gl_Position = vec4(xy.xy, 0, 1);
}