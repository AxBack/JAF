#version 300 es
precision mediump float;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform float uIntensity;

in vec2 uv;

out vec4 finalColor;

const float luminocity = 1.2f;

void main() {
    finalColor = (texture(uTexture0, uv) + texture(uTexture1, uv) * luminocity) * uIntensity;
}