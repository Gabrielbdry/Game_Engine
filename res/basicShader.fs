#version 150

varying vec3 position0;
varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D matTex;

struct BaseLight {
	vec3 color;
	float intensity;
};

struct PointLight {
	BaseLight baseLight;
	float radius;
	vec3 position;
};

uniform PointLight pointLight;

uniform BaseLight baseLight;

void main() {
	vec4 finalColor = vec4(baseLight.color, 1.0) * 								texture2D(matTex, texCoord0);
	float distance = distance(pointLight.position, position0);
	if (distance <= pointLight.radius)
		finalColor *= vec4(pointLight.baseLight.color * 2, 				1.0);
	gl_FragColor = finalColor;
}