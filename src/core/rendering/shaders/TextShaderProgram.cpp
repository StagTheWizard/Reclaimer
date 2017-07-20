//
// Created by montgomery anderson on 30/06/17.
//

#include "TextShaderProgram.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Constants.h"


TextShaderProgram::TextShaderProgram() : ShaderProgram() {}


TextShaderProgram::~TextShaderProgram() {}


void TextShaderProgram::initialiseShaders() {
    vertShader = loadShader(GL_VERTEX_SHADER, "shaders/Text.vert");
    fragShader = loadShader(GL_FRAGMENT_SHADER, "shaders/Text.frag");
}


void TextShaderProgram::bindLocations() {
    glBindAttribLocation(program, 0, "pos");
    glBindAttribLocation(program, 1, "UVin");
}


void TextShaderProgram::bindUniforms() {
    GLint inputColorLoc = glGetUniformLocation(program, "inputColor");
    uniformInputColor = (GLuint) inputColorLoc;

    GLint textureMapLoc = glGetUniformLocation(program, "textureMap");
    uniformTextureMap = (GLuint) textureMapLoc;

    GLint projectionLoc = glGetUniformLocation(program, "projection");
    uniformProjection = (GLuint) projectionLoc;

    projection = glm::ortho(0.0f, (float) constants::WINDOW_WIDTH, 0.0f, (float) constants::WINDOW_HEIGHT);

    uniformsBound = true;
}


void TextShaderProgram::updateUniforms(glm::vec3 color) {
    glUseProgram(program);
    glUniform3fv(uniformInputColor, 1, &color[0]);
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(uniformTextureMap, 0);
}