#version 150

#define M_PI 3.1415926535897932384626433832795

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

struct SpotLight {
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform SpotLight spotLight;

uniform PointLight pointLight;

uniform BaseLight baseLight;

vec4 CalcLight(BaseLight base) {
	return vec4(base.color, 1.0) * base.intensity;
}

vec4 CalcPointLight(PointLight point) {
	vec3 ld = (point.position - position0);
	float dist = length(ld);
	if (dist <= point.radius) {
		float attenuation = dist * dist;
		return CalcLight(point.baseLight) * pow((1.0 - (dist / point.radius)), 2);
	}
	return vec4(0.0, 0.0 , 0.0 , 0.0);
}

vec4 CalcSpotLight(SpotLight spot) {
	vec3 ld = normalize(position0 - spot.pointLight.position);
	vec3 sd = normalize(spot.direction);
	float spotFactor = dot(ld, sd);

	if (spotFactor > spot.cutoff) {
		return CalcPointLight(spot.pointLight) * (1.0 - ((1.0 - spotFactor) / (1.0 - spot.cutoff)));
	}
	else {
		return vec4(0.0, 0.0, 0.0, 0.0);
	}
}

void main() {
	vec4 finalColor = CalcSpotLight(spotLight) + CalcLight(baseLight);
	//vec4 finalColor = CalcPointLight(pointLight) + CalcLight(baseLight);
	finalColor *= texture2D(matTex, texCoord0);
	gl_FragColor = finalColor;
}
