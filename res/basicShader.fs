#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform vec3 ambientLight;
uniform sampler2D matTex;

void main() {
	
	vec4 ambient = vec4(ambientLight, 1);
	vec4 finalColor = vec4(0, 0, 0, 0);
	
	finalColor = texture2D(matTex, texCoord0);
	
	gl_FragColor = finalColor * ambient;
}