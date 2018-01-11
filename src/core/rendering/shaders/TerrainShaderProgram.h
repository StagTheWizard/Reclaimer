//
// Created by montgomery anderson on 19/07/17.
//

#ifndef RECLAIMER_WORLDSHADER_H
#define RECLAIMER_WORLDSHADER_H


#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>

class Tile;


class TerrainShaderProgram : public ShaderProgram {
public:
    GLuint uniformModelMatrix;
    GLuint uniformViewMatrix;
    GLuint uniformModelViewMatrix;
    GLuint uniformMvpMatrix;
    GLuint uniformNormalMatrix;
    GLuint uniformCameraPosition;
    GLuint uniformLightPosition;
    GLuint uniformTilesArray;

    TerrainShaderProgram();
    ~TerrainShaderProgram();

    void updateUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 modelViewMatrix, glm::mat4 mvpMatrix,
                        glm::mat4 normalMatrix, glm::vec4 cameraPosition, glm::vec4 lightPos, int tiles[]);
protected:
    virtual void initialiseShaders() override;
    virtual void bindLocations() override;
    virtual void bindUniforms() override;
private:


};


#endif //RECLAIMER_WORLDSHADER_H
