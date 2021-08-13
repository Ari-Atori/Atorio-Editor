#version 130

in vec2 T;

uniform sampler2D diffuse;
uniform vec3 tempColor;

const vec3 Y= vec3(.2126, 0.7152, 0.0722);

//values for luminous preservation


vec3 colluma(vec3 c, float y) {
    float e = 1.0e-16;
    float cy = dot(c, Y);
    vec3 top = (vec3(1.0) - c) / (1.0 - cy + e);
    vec3 bottom = c / (cy + e);
    vec3 slope = mix(bottom, top, float(y >= cy));
    vec3 base = c - slope * cy;
    return clamp(slope * y + base, vec3(0), vec3(1));
}


void main() {
	vec4 color = texture2D(diffuse, T);
	float lumin = dot(color.rgb, Y);
	color.rgb *= tempColor;
	color.z = lumin;
	color.rgb=colluma(color.rgb, lumin);
	gl_FragColor = vec4(color.rgb , color.a);
}

