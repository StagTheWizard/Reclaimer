//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_TEXTSHADERPROGRAM_H
#define RECLAIMER_TEXTSHADERPROGRAM_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"


class TextShaderProgram : public ShaderProgram {
public:
    GLuint uniformInputColor;
    GLuint uniformTextureMap;
    GLuint uniformProjection;

    glm::mat4 projection;

    TextShaderProgram();
    ~TextShaderProgram();

    void updateUniforms(glm::vec3 color);
protected:
    virtual void initialiseShaders() override;
    virtual void bindLocations() override;
    virtual void bindUniforms() override;
private:
};


#endif //RECLAIMER_TEXTSHADERPROGRAM_H
