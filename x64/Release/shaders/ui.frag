#version 130

in vec2 T;
in vec2 P;

uniform sampler2D diffuse;
uniform vec4 bgcolor;
uniform vec2 upperright, border_radius, center;
uniform bool usestexture;

bool in_border() {
	vec2 C = abs(P - center) + center; // position within box - center of box, transformed to always be upper right coordinate
	vec2 ce = upperright - border_radius; // center of ellipse = upper right definition - border radius
	vec2 cd = C - ce; // displacment from current coordiante and center of ellipse
	vec2 br2 = (border_radius * border_radius).yx; //border radius squared
	bool ur = all(greaterThan(C, ce)); //is the texture coordinate with the upper right portion of the epplise's center?
	return !(ur && dot(br2, cd * cd) > br2.x * br2.y); //second part is a rewrite of ellipse equation
}

void main() {
	//vec4 color = texture2D(diffuse, T);
	gl_FragColor = in_border() ? (usestexture ? texture2D(diffuse, T) : bgcolor) : vec4(0);
}

