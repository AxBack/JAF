#version 300 es
precision mediump float;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

in vec2 uv;

out vec4 finalColor;

const float magnitude = 2.0f;

void main() {
    finalColor = texture(uTexture0, uv)
               + texture(uTexture1, uv)
               + texture(uTexture2, uv)
               + texture(uTexture3, uv);
               //* magnitude;
}