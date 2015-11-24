#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D matTex;

struct BaseLight {
	vec3 color;
	float intensity;
}; 

uniform BaseLight baseLight;

void main() {
	gl_FragColor = texture2D(matTex, texCoord0);
}