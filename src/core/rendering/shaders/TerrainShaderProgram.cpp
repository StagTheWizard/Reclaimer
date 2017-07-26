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
    glBindAttribLocation(program, 0, "vertPosition");
    glBindAttribLocation(program, 1, "vertNormal");
}


void TerrainShaderProgram::bindUniforms() {
    GLint modelMatrixLoc = glGetUniformLocation(program, "modelMatrix");
    uniformModelMatrix = (GLuint) modelMatrixLoc;
    GLint viewMatrixLoc = glGetUniformLocation(program, "viewMatrix");
    uniformViewMatrix = (GLuint) viewMatrixLoc;
    GLint modelViewMatrixLoc = glGetUniformLocation(program, "modelViewMatrix");
    uniformModelViewMatrix = (GLuint) modelViewMatrixLoc;
    GLint mvpMatrixLoc = glGetUniformLocation(program, "mvpMatrix");
    uniformMvpMatrix = (GLuint) mvpMatrixLoc;
    GLint normalMatrixLoc = glGetUniformLocation(program, "normalMatrix");
    uniformNormalMatrix = (GLuint) normalMatrixLoc;
    GLint cameraPositionLoc = glGetUniformLocation(program, "cameraPosition");
    uniformCameraPosition = (GLuint) cameraPositionLoc;
    GLint lightPositionLoc = glGetUniformLocation(program, "lightPosition");
    uniformLightPosition = (GLuint) lightPositionLoc;

    uniformsBound = true;
}


void TerrainShaderProgram::updateUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 modelViewMatrix,
                                          glm::mat4 mvpMatrix, glm::mat4 normalMatrix, glm::vec4 cameraPosition,
                                          glm::vec4 lightPos) {
    glUseProgram(program);
    glUniformMatrix4fv(uniformModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(uniformViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(uniformModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(uniformMvpMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniformMatrix4fv(uniformNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform4fv(uniformLightPosition, 1, glm::value_ptr(lightPos));
}
