#version 330


layout (location=0) in vec2 pos;
layout (location=1) in vec2 UVin;

out vec2 UV;


void main() {
    vec2 homoneousPos = pos.xy - vec2(320, 240);
    homoneousPos /= vec2(320, 240);
    gl_Position = vec4(homoneousPos.xy, 0, 1);
    UV = UVin;
}