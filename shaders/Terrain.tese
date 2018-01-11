#version 330

const int CHUNK_SIZE = 32;

struct Tile {
    int typeId;
    int x;
    int z;
    float y;
};

layout(triangles, equal_spacing, ccw) in;

uniform mat4 mvpMatrix;
uniform Tile tiles[CHUNK_SIZE * CHUNK_SIZE];

in vec3 patchNormal [];

out vec4 fragPosition;
out vec3 fragNormal;


void main() {
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.z;
    vec4 position = gl_TessCoord.x * gl_in[0].gl_Position
                  + gl_TessCoord.y * gl_in[1].gl_Position
                  + gl_TessCoord.z * gl_in[2].gl_Position;

    // pass through position to fragment shader
    fragPosition = position;
    // interpolate normals
    vec3 interpolatedNormal =
        gl_TessCoord.x * patchNormal[0] +
        gl_TessCoord.y * patchNormal[1] +
        gl_TessCoord.z * patchNormal[2];
    fragNormal = normalize(interpolatedNormal);

    gl_Position = mvpMatrix * position;
}