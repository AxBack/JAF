#version 300 es
precision mediump float;

uniform samplerCube uTexture;
uniform float alpha;

in vec3 normal;

out vec4 finalColor;

void main() {
    finalColor = texture(uTexture, normal) * alpha;
}