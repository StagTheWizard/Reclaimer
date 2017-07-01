//
// Created by montgomery anderson on 19/12/16.
//

#ifndef RECLAIMER_SHADERPROGRAM_H
#define RECLAIMER_SHADERPROGRAM_H


#include <string>
#include <OpenGL/OpenGL.h>


class ShaderProgram {
public:
    ShaderProgram();

    void initialise();
    void activate();
protected:
    GLuint program;

    GLuint vertShader;
    GLuint tessCtrlShader;
    GLuint tessEvalShader;
    GLuint geomShader;
    GLuint fragShader;

    bool uniformsBound = false;

    virtual void initialiseShaders() = 0;
    void assembleProgram();

    GLuint loadShader(GLenum shaderType, std::string filename);


};


#endif //RECLAIMER_SHADERPROGRAM_H