//
// Created by montgomery anderson on 30/06/17.
//

#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>


ShaderProgram::ShaderProgram() {}


void ShaderProgram::initialise() {
    std::cout << "[ShaderProgram] Initialising.." << std::endl;
    program = glCreateProgram();

    this->initialiseShaders();
    this->assembleProgram();
    std::cout << "[ShaderProgram] Initialisation successful, program=" << program << "." << std::endl;
}


void ShaderProgram::assembleProgram() {
    // Attach and link shaders to program
    if (vertShader) glAttachShader(program, vertShader);
    if (tessCtrlShader) glAttachShader(program, tessCtrlShader);
    if (tessEvalShader) glAttachShader(program, tessEvalShader);
    if (geomShader) glAttachShader(program, geomShader);
    if (fragShader) glAttachShader(program, fragShader);

    // virtual method enforcing child classes to bind their uniforms in prior to linking
    bindLocations();
    glLinkProgram(program);

    // Affirm outcome of linking
    GLint status;
    std::cout << "Linking shaders" << std::endl;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    std::cout << "Linker success" << std::endl;
}


void ShaderProgram::activate() {
//    std::cout << "[ShaderProgram] Activating." << std::endl;
    this->bindUniforms();
    if (uniformsBound) glUseProgram(program);
    else std::cerr << "[ShaderProgram] Uniform Variables not bound, failed to activate." << std::endl;
//    std::cout << "[ShaderProgram] Activation complete." << std::endl;
}


GLuint ShaderProgram::loadShader(GLenum shaderType, std::string filename) {
    std::ifstream shaderFile(filename.c_str());
    if (!shaderFile.good()) std::cout << "Error opening shader file." << std::endl;

    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    std::string shaderStr = shaderData.str();
    const char *shaderTxt = shaderStr.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderTxt, NULL);

    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        const char *strShaderType = NULL;
        std::cerr << "Compile failure in shader '" << filename.c_str() << "': " << strInfoLog << std::endl;
        delete[] strInfoLog;
    } else {
        std::cout << "Compile success in shader '" << filename.c_str() << "'" << std::endl;
    }
    return shader;
}