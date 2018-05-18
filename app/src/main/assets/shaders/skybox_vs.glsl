#version 300 es
precision mediump float;

uniform vec3 cameraNormal;
uniform vec3 cameraRight;
uniform vec3 cameraUp;

layout (location = 0) in vec4 inPosition;

out vec3 normal;

void main() {
    normal = normalize(
        cameraNormal +
        (cameraRight * inPosition.x) +
        (cameraUp * inPosition.y)
        );

    gl_Position = inPosition;
}