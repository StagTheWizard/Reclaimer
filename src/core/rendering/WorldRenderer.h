//
// Created by montgomery anderson on 19/07/17.
//

#ifndef RECLAIMER_WORLDRENDERER_H
#define RECLAIMER_WORLDRENDERER_H


#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "core/rendering/shaders/TerrainShaderProgram.h"


class Engine;
class TerrainMesh;


class WorldRenderer {
public:
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    WorldRenderer(Engine* engine);
    ~WorldRenderer();

    int initialise();
    void renderTerrain(TerrainMesh *mesh);
protected:
private:
    Engine *engine;
    TerrainShaderProgram *terrainShader;

    GLuint vao;
    GLuint vertexBuffer;
    GLuint elementBuffer;

    int initialiseShaders();
};


#endif //RECLAIMER_WORLDRENDERER_H
