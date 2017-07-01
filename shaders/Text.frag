#version 330


in vec2 UV;

out vec4 color;

uniform sampler2D textureMap;


void main() {
//    color = vec4(1, 1, 1, texture(textureMap, UV).r);
    color = vec4(1, 0, 0, 1);
}