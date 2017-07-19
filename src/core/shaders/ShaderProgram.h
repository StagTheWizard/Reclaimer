//
// Created by montgomery anderson on 19/12/16.
//

#ifndef RECLAIMER_SHADERPROGRAM_H
#define RECLAIMER_SHADERPROGRAM_H


#include <string>
#include <glad/glad.h>


class ShaderProgram {
public:
    ShaderProgram();

    void initialise();
    void activate();
protected:
    GLuint program;

    GLuint vertShader = 0;
    GLuint tessCtrlShader = 0;
    GLuint tessEvalShader = 0;
    GLuint geomShader = 0;
    GLuint fragShader = 0;

    bool uniformsBound = false;

    virtual void initialiseShaders() = 0;
    void assembleProgram();
    virtual void bindLocations() = 0;

    GLuint loadShader(GLenum shaderType, std::string filename);


};


#endif //RECLAIMER_SHADERPROGRAM_H