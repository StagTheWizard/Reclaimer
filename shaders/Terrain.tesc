#version 330

layout(vertices = 3) out;

in vec3 tescNormal [];

out vec3 patchNormal [];

void main() {
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    patchNormal[gl_InvocationID] = tescNormal[gl_InvocationID];

    gl_TessLevelOuter[0] = 2;
    gl_TessLevelOuter[1] = 2;
    gl_TessLevelOuter[2] = 2;
    gl_TessLevelInner[0] = 3;
}
