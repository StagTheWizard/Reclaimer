//
// Created by montgomery anderson on 19/07/17.
//

#include <glm/gtc/type_ptr.hpp>
#include <core/Constants.h>
#include "TerrainShaderProgram.h"


TerrainShaderProgram::TerrainShaderProgram() {

}


TerrainShaderProgram::~TerrainShaderProgram() {

}


void TerrainShaderProgram::initialiseShaders() {
    vertShader = loadShader(GL_VERTEX_SHADER, "shaders/Terrain.vert");
    tessCtrlShader = loadShader(GL_TESS_CONTROL_SHADER, "shaders/Terrain.tesc");
    tessEvalShader = loadShader(GL_TESS_EVALUATION_SHADER, "shaders/Terrain.tese");
    fragShader = loadShader(GL_FRAGMENT_SHADER, "shaders/Terrain.frag");
}


void TerrainShaderProgram::bindLocations() {
    glBindAttribLocation(program, 0, "vertPosition");
    glBindAttribLocation(program, 1, "vertNormal");
}


void TerrainShaderProgram::bindUniforms() {
    uniformModelMatrix = (GLuint) glGetUniformLocation(program, "modelMatrix");
    uniformViewMatrix = (GLuint) glGetUniformLocation(program, "viewMatrix");
    uniformModelViewMatrix = (GLuint) glGetUniformLocation(program, "modelViewMatrix");
    uniformMvpMatrix = (GLuint) glGetUniformLocation(program, "mvpMatrix");
    uniformNormalMatrix = (GLuint) glGetUniformLocation(program, "normalMatrix");
    uniformCameraPosition = (GLuint) glGetUniformLocation(program, "cameraPosition");
    uniformLightPosition = (GLuint) glGetUniformLocation(program, "lightPosition");
    uniformTilesArray = (GLuint) glGetUniformLocation(program, "tiles");

    uniformsBound = true;
}


void TerrainShaderProgram::updateUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 modelViewMatrix,
                                          glm::mat4 mvpMatrix, glm::mat4 normalMatrix, glm::vec4 cameraPosition,
                                          glm::vec4 lightPos, int tiles[]) {
    glUseProgram(program);
    glUniformMatrix4fv(uniformModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(uniformViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(uniformModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(uniformMvpMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniformMatrix4fv(uniformNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform4fv(uniformCameraPosition, 1, glm::value_ptr(cameraPosition));
    glUniform4fv(uniformLightPosition, 1, glm::value_ptr(lightPos));
    glUniform1iv(uniformTilesArray, constants::CHUNK_SIZE * constants::CHUNK_SIZE, &tiles[0]);
}
