//
// Created by montgomery anderson on 19/07/17.
//

#ifndef RECLAIMER_WORLDSHADER_H
#define RECLAIMER_WORLDSHADER_H


#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>


class TerrainShaderProgram : public ShaderProgram {
public:
    GLuint uniformMvpMatrix;

    TerrainShaderProgram();
    ~TerrainShaderProgram();

    void updateUniforms(glm::mat4 mvpMatrix);
protected:
    virtual void initialiseShaders() override;
    virtual void bindLocations() override;
    virtual void bindUniforms() override;
private:

};


#endif //RECLAIMER_WORLDSHADER_H
