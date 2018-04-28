#version 300 es
precision mediump float;

uniform sampler2D uTexture;
uniform sampler2D uBloomTexture;

in vec2 uv;

out vec4 finalColor;

const float luminocity = 2.2f;

void main() {
    finalColor = texture(uTexture, uv) + texture(uBloomTexture, uv) * luminocity;
}