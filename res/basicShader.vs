#version 150

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec3 position0;
varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;
uniform mat4 camView;

void main() {
	gl_Position = camView * transform * vec4(position, 1.0);
	position0 = (transform * vec4(position, 1.0)).xyz;
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}
