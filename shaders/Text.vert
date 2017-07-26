#version 330 core


layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 UVin;

out vec2 UV;

uniform sampler2D textureMap;
uniform mat4 projection;


void main() {
//    vec2 homoneousPos = pos.xy - vec2(320, 240);
//    homoneousPos /= vec2(320, 240);
//    gl_Position = vec4(homoneousPos.xy, 0, 1);
    gl_Position = projection * vec4(pos.xy, 0.0, 1.0);
    UV = UVin;
}
