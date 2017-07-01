//
// Created by montgomery anderson on 30/06/17.
//

#include "TextShaderProgram.h"

#include <SFML/OpenGL.hpp>


TextShaderProgram::TextShaderProgram() : ShaderProgram() {}


TextShaderProgram::~TextShaderProgram() {}


void TextShaderProgram::initialiseShaders() {
    vertShader = loadShader(GL_VERTEX_SHADER, "shaders/Text.vert");
    fragShader = loadShader(GL_FRAGMENT_SHADER, "shaders/Text.frag");
}


void TextShaderProgram::bindUniforms() {
    uniformInputColor = glGetUniformLocation(program, "inputColor");
    uniformTextureMap = glGetUniformLocation(program, "textureMap");

    uniformsBound = true;
}


void TextShaderProgram::updateUniforms(glm::vec3 color) {
    glUniform3fv(uniformInputColor, 1, &color[0]);
}