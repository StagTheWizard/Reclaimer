//
// Created by montgomery anderson on 19/07/17.
//

#include <glm/gtc/type_ptr.hpp>
#include "TerrainShaderProgram.h"


TerrainShaderProgram::TerrainShaderProgram() {

}


TerrainShaderProgram::~TerrainShaderProgram() {

}


void TerrainShaderProgram::initialiseShaders() {
    vertShader = loadShader(GL_VERTEX_SHADER, "shaders/Terrain.vert");
    fragShader = loadShader(GL_FRAGMENT_SHADER, "shaders/Terrain.frag");
}


void TerrainShaderProgram::bindLocations() {
    glBindAttribLocation(program, 0, "pos");
}


void TerrainShaderProgram::bindUniforms() {
    GLint mvpMatrixLoc = glGetUniformLocation(program, "mvpMatrix");
    uniformMvpMatrix = (GLuint) mvpMatrixLoc;

    uniformsBound = true;
}


void TerrainShaderProgram::updateUniforms(glm::mat4 mvpMatrix) {
    glUseProgram(program);
    glUniformMatrix4fv(uniformMvpMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}
