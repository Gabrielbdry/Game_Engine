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

vec4 CalcLight(BaseLight base) {
	return vec4(base.color, 1.0) * base.intensity;
}

vec4 CalcPointLight(PointLight point) {
	float dist = length(point.position - position0);
	if (dist <= point.radius) {
		float attenuation = pow(((dist / point.radius) + 										1.0),2);
		//float attenuation = dist * dist + 0.0001;
		return CalcLight(point.baseLight) / attenuation;

	}
	return vec4(0.0, 0.0 , 0.0 , 0.0);
}

void main() {
	vec4 finalColor = CalcPointLight(pointLight);
	if (finalColor.x == 0.0) {
		finalColor = vec4(baseLight.color, 1.0);
	}
	finalColor *= texture2D(matTex, texCoord0);
	gl_FragColor = finalColor;
}