#version 330 core


in vec2 UV;

out vec4 color;

uniform sampler2D textureMap;
uniform vec3 inputColor;


void main() {
    vec4 sampledColor = vec4(1.0, 1.0, 1.0, texture(textureMap, UV).r);
    color = vec4(inputColor, 1.0) * sampledColor;
//    color = vec4(inputColor, 1.0);
}
